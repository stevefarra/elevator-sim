#pragma once
#include "rt.h"
#include "encodings.h"

void printUI() {
	CMutex cursorMutex("cursorMutex");

	cursorMutex.Wait();

	MOVE_CURSOR(0, 0);
	cout << "User input";

	MOVE_CURSOR(ELEVATOR_1_COL, 0);
	cout << "Elevator 1";
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
}