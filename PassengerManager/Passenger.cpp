#include "Passenger.h"


Passenger::Passenger(int _elevatorNumber)
{
	elevator = _elevatorNumber;
	// elevator 1 going UP
	// elevator 2 going DOWN
}

int Passenger::main()
{
	int req = 0;

	// create random passenger information
	int requestedFloor;
	int currentFloor = rand() % 9 + 1;

	// for going up requestedFloor must be > currentFloor
	if (elevator == 1)
	{
		while (currentFloor == 9)
		{
			currentFloor = rand() % 9 + 1;
		}

		requestedFloor = currentFloor + rand() % (9 - (currentFloor+1) ) + 1;
	} else
	{
		while (currentFloor == 1)
		{
			currentFloor = rand() % 9 + 1;
		}

		requestedFloor = rand() % (currentFloor - 2) + 1;
		cout << currentFloor << endl;
	}
	
	
	//int requestedFloor = rand() % 9 + 1;

	//// in case requested floor and current floor happen to be the same increment requested floor
	//if (requestedFloor == currentFloor)
	//{
	//	requestedFloor++;
	//}

	//// const int elevator = requestedFloor > currentFloor ? 1 : 2;


	
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

	pipelineMutex.Wait();
	ioToDispatcherPipeline.Write(&req);
	pipelineMutex.Signal();

	if (elevator == 2)
		return 0;

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
	pipelineMutex.Wait();
	ioToDispatcherPipeline.Write(&req);
	pipelineMutex.Signal();

	return 0;
}
