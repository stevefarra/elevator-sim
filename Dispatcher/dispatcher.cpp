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
CTypedPipe<int> ioAndDispatcherPipeline("ioAndDispatcherPipeline", 100);
int pipelineWrite;

Elevator elevator1(1);
Elevator elevator2(2);
int elevatorStatus[3];

CMailbox ioMail();

UINT __stdcall ioThread(void* args) {
	while (1) {
	}
	return 0;
}

/* Elevator threads respond to changes in elevator status and copy that status 
 * to local variables within Dispatcher process so that when a new command
 * arrives, it can be dealt with immediately
 */
UINT __stdcall elevator1Thread(void* args) {
	while (1) {
		elevatorStatus[1] = elevator1.getElevatorStatus();
	}
	return 0;
}

UINT __stdcall elevator2Thread(void* args) {
	while (1) {
		elevatorStatus[2] = elevator2.getElevatorStatus();
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