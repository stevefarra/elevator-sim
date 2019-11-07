#include "Passenger.h"


Passenger::Passenger(int elevatorNumber)
{
	
}

int Passenger::main()
{
	int req = 0;

	// create random passenger information
	// const int elevator = rand() % 2 + 1; // random elevator
	const int currentFloor = rand() % 9 + 1;
	int requestedFloor = rand() % 9 + 1;

	// in case requested floor and current floor happen to be the same increment requested floor
	if (requestedFloor == currentFloor)
	{
		requestedFloor++;
	}

	const int elevator = requestedFloor > currentFloor ? 1 : 2;

	
	// depending on requested and current floor, choose UP or DOWN command
	if (requestedFloor > currentFloor)
	{
		// OUTSIDE and going UP
		req += OUTSIDE_REQ;
		req += UP_REQ;
	} else
	{
		// OUTSIDE and going DOWN
		req += OUTSIDE_REQ;
		req += DOWN_REQ;
	}

	// add current current floor to request
	req += currentFloor;
	// send request on pipeline
	ioToDispatcherPipeline.Write(&req);

	// TODO: passenger gets into elevator

	req = 0; // reset request
	// passenger makes request from inside

	// choose elevator
	if (elevator == 1)
	{
		req += ELEVATOR1_REQ;
	} else
	{
		req += ELEVATOR2_REQ;
	}
	// enter destination floor
	req += requestedFloor;

	// send inside request through 
	ioToDispatcherPipeline.Write(&req);

	return 0;
}
