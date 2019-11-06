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

CMutex cursorMutex("cursorMutex");

void printUI() {
	cursorMutex.Wait();

	MOVE_CURSOR(0, 0);
	cout << "User input";

	MOVE_CURSOR(ELEVATOR_1_COL, 0);
	cout << "ELEVATOR 1";
	MOVE_CURSOR(ELEVATOR_1_COL, 1);
	cout << "Status: ";
	MOVE_CURSOR(ELEVATOR_1_COL, 2);
	cout << "Door: ";
	MOVE_CURSOR(ELEVATOR_1_COL, 3);
	cout << "Direction: ";
	MOVE_CURSOR(ELEVATOR_1_COL, 4);
	cout << "Floor: ";

	MOVE_CURSOR(ELEVATOR_2_COL, 0);
	cout << "ELEVATOR 2";
	MOVE_CURSOR(ELEVATOR_2_COL, 1);
	cout << "Status: ";
	MOVE_CURSOR(ELEVATOR_2_COL, 2);
	cout << "Door: ";
	MOVE_CURSOR(ELEVATOR_2_COL, 3);
	cout << "Direction: ";
	MOVE_CURSOR(ELEVATOR_2_COL, 4);
	cout << "Floor: ";

	cursorMutex.Signal();
}

UINT __stdcall keyboardThread(void* args) {
	int inputLine = 1;
	while (1) {
		/* Acquire request from user and print it */
		char type = _getch();
		cursorMutex.Wait();
		MOVE_CURSOR(0, inputLine);
		cout << type;
		cursorMutex.Signal();

		int floor = _getch() - '0';
		cursorMutex.Wait();
		MOVE_CURSOR(1, inputLine);
		cout << floor;
		cursorMutex.Signal();
		inputLine++;

		/* Parse keyboard input and add it to the pipeline */
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

UINT __stdcall elevator1Thread(void* args) {
	struct elevatorData elevator1Data;
	while (1) {
		elevator1Data = elevator1.getData();
		cursorMutex.Wait();
		MOVE_CURSOR(ELEVATOR_1_COL + 7, 1);
		if (elevator1Data.status == IN_SERVICE) {
			cout << "In service";
		}
		else if (elevator1Data.status == OUT_OF_SERVICE) {
			cout << "Out of service";
		}
	}
	return 0;
}

UINT __stdcall elevator2Thread(void* args) {
	struct elevatorData elevator2Data;
	while (1) {
		elevator2Data = elevator2.getData();
	}
	return 0;
}

int main() {
	/* Initialize the UI */
	printUI();

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