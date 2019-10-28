#pragma once
#include "..\\elevator-sim.h"

int elevator1Data;
int elevator2Data;
int pipelineRead;

UINT __stdcall ioThread(void* args) {
	while (1) {
	}
	return 0;
}

UINT __stdcall elevator1Thread(void* args) {
	while (1) {
	}
	return 0;
}

UINT __stdcall elevator2Thread(void* args) {
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
	CThread ioThread(ioThread, ACTIVE, NULL);
	CThread elevator1Thread(elevator1Thread, ACTIVE, NULL);
	CThread elevator2Thread(elevator2Thread, ACTIVE, NULL);

	while (1) {
	}

	return 0;
}