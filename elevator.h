#pragma once
#include "rt.h"
#include "encodings.h"
#include <stdlib.h>

struct elevatorData {
	int dir;
	int status;
	int door;
	int floor;
};

class Elevator {
	int id;
	CDataPool* datapool;
	struct elevatorData* data;
	CSemaphore* dataReadDispatcherSemaphore;
	CSemaphore* dataReadIOSemaphore;
	CSemaphore* dataAvailableDispatcherSemaphore;
	CSemaphore* dataAvailableIOSemaphore;

public:
	Elevator(int _id) {
		id = _id;
		if (id == 1) {
			datapool = new CDataPool("elevator1Datapool", sizeof(struct elevatorData));

			dataReadDispatcherSemaphore = new CSemaphore("elevator1DataReadDispatcherSemaphore", 0, 1);
			dataReadIOSemaphore = new CSemaphore("elevator1DataReadIOSemaphore", 0, 1);
			dataAvailableDispatcherSemaphore = new CSemaphore("elevator1DataAvailableDispatcherSemaphore", 1, 1);
			dataAvailableIOSemaphore = new CSemaphore("elevator1DataAvailableIOSemaphore", 1, 1);
		}
		else if (id == 2) {
			datapool = new CDataPool("elevator2Datapool", sizeof(struct elevatorData));

			dataReadDispatcherSemaphore = new CSemaphore("elevator2DataReadDispatcherSemaphore", 0, 1);
			dataReadIOSemaphore = new CSemaphore("elevator2DataReadIOSemaphore", 0, 1);
			dataAvailableDispatcherSemaphore = new CSemaphore("elevator2DataAvailableDispatcherSemaphore", 1, 1);
			dataAvailableIOSemaphore = new CSemaphore("elevator2DataAvailableIOSemaphore", 1, 1);
		}
		data = (struct elevatorData*)(datapool->LinkDataPool());
		data->dir = IDLE;
		data->status = IN_SERVICE;
		data->door = OPEN;
		data->floor = 0;
	}
	struct elevatorData getData(int caller) {
		struct elevatorData dataCopy;
		if (caller == IO) {
			dataAvailableIOSemaphore->Wait();
			dataCopy = *data;
			dataReadIOSemaphore->Signal();
		}
		else if (caller == DISPATCHER) {
			dataAvailableDispatcherSemaphore->Wait();
			dataCopy = *data;
			dataReadDispatcherSemaphore->Signal();
		}
		return dataCopy;
	}
	void updateData(struct elevatorData newElevatorData) {
		/* Wait for Dispatcher and IO to read the last update */
		dataReadDispatcherSemaphore->Wait();
		dataReadIOSemaphore->Wait();

		/* Write new data to the datapool */
		data->dir = newElevatorData.dir;
		data->status = newElevatorData.status;
		data->door = newElevatorData.door;
		data->floor = newElevatorData.floor;

		/* Let Dispatcher and IO know new data is available */
		dataAvailableDispatcherSemaphore->Signal();
		dataAvailableIOSemaphore->Signal();
		return;
	}
};