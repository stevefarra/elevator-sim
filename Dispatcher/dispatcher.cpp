#pragma once
#include "..\\elevator-sim.h"

int main() {
	/* Initialize the child processes */
	CProcess io("..\\Debug\\IO.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator1("..\\Debug\\elevator1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator2("..\\Debug\\elevator2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);

	while (1) {
		Sleep(500);
		cout << "Hello 1" << endl;
	}
	return 0;
}