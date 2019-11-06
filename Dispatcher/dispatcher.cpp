/* Dispatcher process has three threads and uses status of elevators so that
 * it can decide which elevator is in the best position to deal with an 
 * incoming up/down request
 */
#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"
#include "..\\elevatorUI.h"

/* Typed Pipeline between IO and Dispatcher allows incoming commands that have been
 * validated by the IO process to be given to the Dispatcher, where upon the Dispatcher
 * decides which elevator to delegate the command to e.g. floor or up/down request
 */
CTypedPipe<int> ioToDispatcherPipeline("ioToDispatcherPipeline", 100);
int req;

Elevator elevator1(1);
Elevator elevator2(2);
CDataPool elevator1Datapool("elevator1Datapool", sizeof(struct elevatorData));
CDataPool elevator2Datapool("elevator2Datapool", sizeof(struct elevatorData));
struct elevatorData *elevator1Data;
struct elevatorData *elevator2Data;

CMailbox ioMail();

UINT __stdcall ioThread(void* args) {
	while (1) {
		if (ioToDispatcherPipeline.TestForData() > 0) {
			ioToDispatcherPipeline.Read(&req);
		}
	}
	return 0;
}

UINT __stdcall elevator1Thread(void* args) {
	elevator1Data = (struct elevatorData*)(elevator1Datapool.LinkDataPool());
	int dir;
	int status;
	int door;
	int floor;
	while (1) {
		/* When new data from the elevator is ready, update local variables */
		// dataAvailableSemaphore.Wait();
		dir = elevator1Data->dir;
		status = elevator1Data->status;
		door = elevator1Data->door;
		floor = elevator1Data->floor;
		// dataReadSemaphore.Signal();
	}
}

UINT __stdcall elevator2Thread(void* args) {
	elevator2Data = (struct elevatorData*)(elevator2Datapool.LinkDataPool());
	int dir;
	int status;
	int door;
	int floor;
	while (1) {
		/* When new data from the elevator is ready, update local variables */
		// dataAvailableSemaphore.Wait();
		dir = elevator2Data->dir;
		status = elevator2Data->status;
		door = elevator2Data->door;
		floor = elevator2Data->floor;
		// dataReadSemaphore.Signal();
	}
	return 0;
}

int main() {
	/* Initialize the child processes */
	CProcess io("..\\Debug\\IO.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator1("..\\Debug\\elevator1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator2("..\\Debug\\elevator2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);

	/* Initialize the Dispatcher threads */
	CThread ioThread(ioThread, ACTIVE, NULL);
	CThread elevator1Thread(elevator1Thread, ACTIVE, NULL);
	CThread elevator2Thread(elevator2Thread, ACTIVE, NULL);

	while (1) {
	}

	return 0;
}