/* Elevator blocks waiting for a command from the dispatcher (sent
 * via the signal / mailbox) and then execute them with a suitable
 * time delay between each
 */
#pragma once
#include "..\\rt.h"
#include "..\\elevator.h"
#include "..\\encodings.h"

CDataPool elevator1Datapool("elevator1Datapool", sizeof(struct elevatorData));
struct elevatorData* elevator1Data;

int main() {
	CMailbox dispatcherMail();
	Elevator elevator1(1);
	elevator1Data = (struct elevatorData*)(elevator1Datapool.LinkDataPool());

	while (1) {
		
	}

	return 0;
}