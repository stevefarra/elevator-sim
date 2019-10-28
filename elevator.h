#pragma once
#include "rt.h"
#include "encodings.h"

class Elevator {
	int id;
	struct elevatorData {
		int dir;
		int status;
		int door;
		int floor;
	};
	CMutex* mutex;
	CDataPool* datapool;
	elevatorData* data;
public:
	Elevator(int _id) {
		id = _id;
		if (id == 1) {
			mutex = new CMutex("elevatorMutex1");
			datapool = new CDataPool("elevatorDatapool1", sizeof(struct elevatorData));
		}
		else if (id == 2) {
			mutex = new CMutex("elevatorMutex2");
			datapool = new CDataPool("elevatorDatapool2", sizeof(struct elevatorData));
		}
		data = (struct elevatorData*)(datapool->LinkDataPool());

		data->dir = 0;
		data->status = 0;
		data->door = 0;
		data->floor = 0;
	}
	int getElevatorStatus() {
		return 0;
	}
	/* Waits to make sure both Dispatcher and IO have read the last update,
	 * then writes new data to the data pool, then signal to both Dispatcher
	 * and IO that new data is available. Such actions would involve appropriate
	 * reading, signaling and waiting on the appropriate semaphores.*/
	void updateStatus() {
		return;
	}
};