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

struct elevatorData elevator1Data;
struct elevatorData elevator2Data;

bool elevator1FaultFlag = false;
bool elevator2FaultFlag = false;

Elevator elevator1(1);
Elevator elevator2(2);
CMutex cursorMutex("cursorMutex");

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // get console handle

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
		char cmd1 = _getch();
		cursorMutex.Wait();
		MOVE_CURSOR(0, inputLine);
		cout << cmd1;
		cursorMutex.Signal();

		char cmd2 = _getch();
		cursorMutex.Wait();
		MOVE_CURSOR(1, inputLine);
		cout << cmd2;
		cursorMutex.Signal();
		inputLine++;

		/* Check for termination */
		if (cmd1 == 'e' && cmd2 == 'e') {
			cursorMutex.Wait();
			MOVE_CURSOR(0, inputLine);
			cout << "Simulation over";
			cursorMutex.Signal();
			inputLine++;
			req = TERMINATE;
			ioToDispatcherPipeline.Write(&req);
			break;
		}
		if (cmd1 == '-') {
			if (cmd2 == '1') {
				elevator1Data.status == OUT_OF_SERVICE;
			}
			else if (cmd2 == '2') {
				elevator2Data.status == OUT_OF_SERVICE;
			}
		}
		else if (cmd1 == '+') {
			if (cmd2 == '1') {
				elevator1Data.status == IN_SERVICE;
			}
			else if (cmd2 == '2') {
				elevator2Data.status == OUT_OF_SERVICE;
			}
		}
		else {
			char type = cmd1;
			int floor = cmd2 - '0';
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
	}
	return 0;
}
UINT __stdcall elevator1Thread(void* args) {
	while (1) {
		elevator1Data = elevator1.getData(IO);
		cursorMutex.Wait();

		MOVE_CURSOR(ELEVATOR_1_COL + 8, 1);
		if (elevator1Data.status == IN_SERVICE) {
			SetConsoleTextAttribute(hConsole, 1); // bright green
			cout << "In service    ";
			SetConsoleTextAttribute(hConsole, 2); // green
		}
		else if (elevator1Data.status == OUT_OF_SERVICE) {
			SetConsoleTextAttribute(hConsole, 4); // red
			cout << "Out of service";
			SetConsoleTextAttribute(hConsole, 2); // green
		}

		MOVE_CURSOR(ELEVATOR_1_COL + 6, 2);
;		if (elevator1Data.door == OPEN) {
			cout << "Open  ";
		}
		else if (elevator1Data.door == CLOSED) {
			cout << "Closed";
		}

		MOVE_CURSOR(ELEVATOR_1_COL + 11, 3);
		if (elevator1Data.dir == UP) {
			SetConsoleTextAttribute(hConsole, 6); // yellow
			cout << "Up  ";
			SetConsoleTextAttribute(hConsole, 2); // green
		}
		else if (elevator1Data.dir == DOWN) {
			SetConsoleTextAttribute(hConsole, 5); // purple
			cout << "Down";
			SetConsoleTextAttribute(hConsole, 2); // green
		}
		else if (elevator1Data.dir == IDLE) {
			cout << "Idle";
		}

		MOVE_CURSOR(ELEVATOR_1_COL + 7, 4);
		cout << elevator1Data.floor;

		cursorMutex.Signal();
	}
	return 0;
}
UINT __stdcall elevator2Thread(void* args) {
	while (1) {
		elevator2Data = elevator2.getData(IO);

		cursorMutex.Wait();
		MOVE_CURSOR(0, 3);
		cursorMutex.Signal();

		cursorMutex.Wait();

		MOVE_CURSOR(ELEVATOR_2_COL + 8, 1);
		if (elevator2Data.status == IN_SERVICE) {
			SetConsoleTextAttribute(hConsole, 1); // bright green
			cout << "In service    ";
			SetConsoleTextAttribute(hConsole, 2); // green

		}
		else if (elevator2Data.status == OUT_OF_SERVICE) {
			SetConsoleTextAttribute(hConsole, 4); // red
			cout << "Out of service";
			SetConsoleTextAttribute(hConsole, 2); // green
		}

		MOVE_CURSOR(ELEVATOR_2_COL + 6, 2);
		;		if (elevator2Data.door == OPEN) {
			cout << "Open  ";
		}
		else if (elevator2Data.door == CLOSED) {
			cout << "Closed";
		}

		MOVE_CURSOR(ELEVATOR_2_COL + 11, 3);
		if (elevator2Data.dir == UP) {
			SetConsoleTextAttribute(hConsole, 6); // yellow
			cout << "Up  ";
			SetConsoleTextAttribute(hConsole, 2); // green
		}
		else if (elevator2Data.dir == DOWN) {
			SetConsoleTextAttribute(hConsole, 5); // purple
			cout << "Down";
			SetConsoleTextAttribute(hConsole, 2); // green
		}
		else if (elevator2Data.dir == IDLE) {
			cout << "Idle";
		}

		MOVE_CURSOR(ELEVATOR_2_COL + 7, 4);
		cout << elevator2Data.floor;

		cursorMutex.Signal();
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