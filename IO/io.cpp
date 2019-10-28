#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"
#include <conio.h>

/* Typed Pipeline between IO and Dispatcher allows incoming commands that have been
 * validated by the IO process to be given to the Dispatcher, where upon the Dispatcher
 * decides which elevator to delegate the command to e.g. floor or up/down request
 */
CTypedPipe<int> ioToDispatcherPipeline("ioToDispatcherPipeline", 100);

int req;
Elevator elevator1(1);
Elevator elevator2(2);
int elevatorStatus[3];

UINT __stdcall keyboardThread(void* args) {
	while (1) {
		/* Acquire request from user */
		char type = _getch();
		cout << type;
		int floor = _getch() - '0';
		cout << floor << endl;

		/* Parse keyboard input */
		bool error = (type != '1') && (type != '2') && (type != 'u') && (type != 'd') || (floor < 0) || (floor > 9);
		if (!error) {
			if (type == '1') {
				req += INSIDE_REQ;
				req += ELEVATOR1_REQ;
			}
			else if (type == '2') {
				req += INSIDE_REQ;
				req += ELEVATOR2_REQ;
			}
			else if (type == 'u') {
				req += OUTSIDE_REQ;
				req += UP_REQ;
			}
			else if (type == 'd') {
				req += OUTSIDE_REQ;
				req += DOWN_REQ;
			}
			req += floor;
			ioToDispatcherPipeline.Write(&req);
			req = 0;
		}
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