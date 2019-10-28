#pragma once
#include "..\\elevator-sim.h"

int dataFromElevator1;
int dataFromElevator2;

UINT __stdcall threadForIO(void* args) {
	while (1) {
	}
	return 0;
}

UINT __stdcall threadForElevator1(void* args) {
	while (1) {
	}
	return 0;
}

UINT __stdcall threadForElevator2(void* args) {
	while (1) {
	}
	return 0;
}

int main() {
	/* Initialize the child processes */
	CProcess io("..\\Debug\\IO.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator1("..\\Debug\\elevator1.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);
	CProcess elevator2("..\\Debug\\elevator2.exe", NORMAL_PRIORITY_CLASS, PARENT_WINDOW, ACTIVE);

	/* Initialize the Dispatcher threads */
	CThread threadForIO(threadForIO, ACTIVE, NULL);
	CThread threadForElevator1(threadForElevator1, ACTIVE, NULL);
	CThread threadForElevator2(threadForElevator2, ACTIVE, NULL);

	while (1) {
	}

	return 0;
}