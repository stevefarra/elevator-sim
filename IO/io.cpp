#pragma once
#include "..\\elevator-sim.h"

int pipelineWrite;

UINT __stdcall keyboardThread(void* args) {
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
	/* Initialize the IO threads */
	CThread keyboardThread(keyboardThread, ACTIVE, NULL);
	CThread elevator1Thread(elevator1Thread, ACTIVE, NULL);
	CThread elevator2Thread(elevator2Thread, ACTIVE, NULL);

	while (1) {
	}

	return 0;
}