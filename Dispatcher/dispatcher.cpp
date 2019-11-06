/* Dispatcher process has three threads and uses status of elevators so that
 * it can decide which elevator is in the best position to deal with an 
 * incoming up/down request
 */
#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"

/* Typed Pipeline between IO and Dispatcher allows incoming commands that have been
 * validated by the IO process to be given to the Dispatcher, where upon the Dispatcher
 * decides which elevator to delegate the command to e.g. floor or up/down request
 */
CTypedPipe<int> ioToDispatcherPipeline("ioToDispatcherPipeline", 100);
int req;

Elevator elevator1(1);
Elevator elevator2(2);
struct elevatorData elevator1Data;
struct elevatorData elevator2Data;

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
	while (1) {
		elevator1Data = elevator1.getData(DISPATCHER);
	}
}

UINT __stdcall elevator2Thread(void* args) {
	while (1) {
		elevator2Data = elevator2.getData(DISPATCHER);
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

	int testReq = 111;
	while (1) {
		Sleep(6000);
		elevator1.Post(testReq);
		testReq += 2;
	}

	return 0;
}