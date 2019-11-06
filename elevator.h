#pragma once
#include "rt.h"
#include "encodings.h"

struct elevatorData {
	int dir;
	int status;
	int door;
	int floor;
};

class Elevator {
	int id;
	CMutex* mutex;
	CDataPool* datapool;
	elevatorData* data;
	CSemaphore* dataReadSemaphore;// ("dataReadSemaphore", 2, 2);
	CSemaphore* dataAvailableSemaphore;// ("dataAvailableSemaphore", 0, 2);

public:
	Elevator(int _id) {
		id = _id;
		if (id == 1) {
			mutex = new CMutex("elevator1Mutex");
			datapool = new CDataPool("elevator1Datapool", sizeof(struct elevatorData));
			dataReadSemaphore = new CSemaphore("elevator1DataReadSemaphore", 0, 2);
			dataAvailableSemaphore = new CSemaphore("elevator1DataAvailableSemaphore", 2, 2);
		}
		else if (id == 2) {
			mutex = new CMutex("elevator2Mutex");
			datapool = new CDataPool("elevator2Datapool", sizeof(struct elevatorData));
			dataReadSemaphore = new CSemaphore("elevator2DataReadSemaphore", 0, 2);
			dataAvailableSemaphore = new CSemaphore("elevator2DataAvailableSemaphore", 2, 2);
		}
		data = (struct elevatorData*)(datapool->LinkDataPool());
		data->dir = IDLE;
		data->status = IN_SERVICE;
		data->door = OPEN;
		data->floor = 1;
	}

	struct elevatorData getData() {
		struct elevatorData dataCopy;

		dataAvailableSemaphore->Wait();
		dataCopy = *data;
		dataReadSemaphore->Signal();

		return dataCopy;
	}
	
	void updateData() {
		/* Wait for Dispatcher and IO to read the last update */
		// dataReadSemaphore.Wait();
		// dataReadSemaphore.Wait();

		/* Write new data to the datapool */

		/* Let Dispatcher and IO know new data is available */
		// dataAvailableSemaphore.Signal();
		// dataAvailableSemaphore.Signal();
		return;
	}
};