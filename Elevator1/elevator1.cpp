/* Elevator blocks waiting for a command from the dispatcher (sent
 * via the signal / mailbox) and then execute them with a suitable
 * time delay between each
 */
#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"

int main() {
	CMailbox dispatcherMail;
	Elevator elevator1(1);
	int req;

	int testReq = 111;
	while (1) {
		//req = dispatcherMail.GetMessage();
		Sleep(4000);
		elevator1.updateData(testReq);
		testReq += 2;
	}

	return 0;
}