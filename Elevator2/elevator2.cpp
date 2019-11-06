/* Elevator blocks waiting for a command from the dispatcher (sent
 * via the signal / mailbox) and then execute them with a suitable
 * time delay between each
 */
#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"

int main() {
	CMailbox dispatcherMail();
	Elevator elevator2(2);

	while (1) {
		elevator2.updateData();
	}

	return 0;
}