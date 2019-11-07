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
		req = dispatcherMail.GetMessage();

		/* Decode request */
		int floor = req % 10;
		req -= floor;
		int dir = req % 100;
		int type = req - dir;

		if (type == INSIDE_REQ) {
			if (floor > elevatorData.floor) {
				elevatorData.door = CLOSED;
				elevatorData.dir = UP;
			}
			else if (floor < elevatorData.floor) {
				elevatorData.door = CLOSED;
				elevatorData.dir = DOWN;
			}
			while (floor != elevatorData.floor) {
				if (floor > elevatorData.floor) {
					elevatorData.floor++;
				}
				else if (floor < elevatorData.floor) {
					elevatorData.floor--;
				}
				elevator2.updateData(elevatorData);
				Sleep(MS_PER_FLOOR);
			}
			elevatorData.door = OPEN;
			elevatorData.dir = IDLE;
			elevator2.updateData(elevatorData);
		}
	}

	return 0;
}