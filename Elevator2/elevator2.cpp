/* Elevator blocks waiting for a command from the dispatcher (sent
 * via the signal / mailbox) and then execute them with a suitable
 * time delay between each
 */
#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"

int main() {
	struct elevatorData elevatorData = { IDLE, IN_SERVICE, OPEN, 0 };
	CMailbox dispatcherMail;
	Elevator elevator2(2);
	int req;

	while (1) {
	}

	return 0;
}