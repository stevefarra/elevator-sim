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
	CSemaphore* dataReadDispatcherSemaphore;
	CSemaphore* dataReadIOSemaphore;
	CSemaphore* dataAvailableDispatcherSemaphore;
	CSemaphore* dataAvailableIOSemaphore;

public:
	Elevator(int _id) {
		id = _id;
		if (id == 1) {
			mutex = new CMutex("elevator1Mutex");
			datapool = new CDataPool("elevator1Datapool", sizeof(struct elevatorData));

			dataReadDispatcherSemaphore = new CSemaphore("elevator1DataReadDispatcherSemaphore", 0, 1);
			dataReadIOSemaphore = new CSemaphore("elevator1DataReadIOSemaphore", 0, 1);
			dataAvailableDispatcherSemaphore = new CSemaphore("elevator1DataAvailableDispatcherSemaphore", 1, 1);
			dataAvailableIOSemaphore = new CSemaphore("elevator1DataAvailableIOSemaphore", 1, 1);
		}
		else if (id == 2) {
			mutex = new CMutex("elevator2Mutex");
			datapool = new CDataPool("elevator2Datapool", sizeof(struct elevatorData));

			dataReadDispatcherSemaphore = new CSemaphore("elevator2DataReadSemaphore", 0, 1);
			dataReadIOSemaphore = new CSemaphore("elevator2DataReadIOSemaphore", 0, 1);
			dataAvailableDispatcherSemaphore = new CSemaphore("elevator2DataAvailableDispatcherSemaphore", 1, 1);
			dataAvailableIOSemaphore = new CSemaphore("elevator2DataAvailableDispatcherSemaphore", 1, 1);
		}
		data = (struct elevatorData*)(datapool->LinkDataPool());
		data->dir = IDLE;
		data->status = IN_SERVICE;
		data->door = OPEN;
		data->floor = 0;
	}
	struct elevatorData getDataDispatcher() {
		struct elevatorData dataCopy;

		dataAvailableDispatcherSemaphore->Wait();
		dataCopy = *data;
		dataReadDispatcherSemaphore->Signal();

		return dataCopy;
	}
	struct elevatorData getDataIO() {
		struct elevatorData dataCopy;

		dataAvailableIOSemaphore->Wait();
		dataCopy = *data;
		dataReadIOSemaphore->Signal();

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