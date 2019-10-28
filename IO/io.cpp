#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"
#include <conio.h>

/* Typed Pipeline between IO and Dispatcher allows incoming commands that have been
 * validated by the IO process to be given to the Dispatcher, where upon the Dispatcher
 * decides which elevator to delegate the command to e.g. floor or up/down request
 */
CTypedPipe<int> ioAndDispatcherPipeline("ioAndDispatcherPipeline", 100);

int pipelineWrite;
Elevator elevator1(1);
Elevator elevator2(2);
int elevatorStatus[3];

UINT __stdcall keyboardThread(void* args) {
	char c[2];
	while (1) {
		c[0] = _getch();
		cout << c[0];
		c[1] = _getch();
		cout << c[1] << endl;
	}
	return 0;
}

/* Elevator threads handle updates from each of the two elevators and redraw the screen */
UINT __stdcall elevator1Thread(void* args) {
	while (1) {
		elevatorStatus[1] = elevator1.getElevatorStatus();
	}
	return 0;
}

UINT __stdcall elevator2Thread(void* args) {
	while (1) {
		elevatorStatus[2] = elevator1.getElevatorStatus();
	}
	return 0;
}

int main() {
	/* Initialize the IO threads */
	CThread keyboardThread(keyboardThread, ACTIVE, NULL);
	CThread elevator1Thread(elevator1Thread, ACTIVE, NULL);
	CThread elevator2Thread(elevator2Thread, ACTIVE, NULL);

	/* Indicates dispatcher has terminated at end of simulation */
	CMailbox dispatcherMail();

	while (1) {
	}

	return 0;
}