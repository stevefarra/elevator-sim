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
			mutex = new CMutex("mutex1");
			datapool = new CDataPool("datapool1", sizeof(struct elevatorData));
		}
		else if (id == 2) {
			mutex = new CMutex("mutex2");
			datapool = new CDataPool("datapool2", sizeof(struct elevatorData));
		}
		data = (struct elevatorData*)(datapool->LinkDataPool());

		data->dir = 0;
		data->status = 0;
		data->door = 0;
		data->floor = 0;
	}
};