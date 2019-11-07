#include "../rt.h"
#include "Passenger.h"

int main(void)
{
	Passenger* passengerList[80];
	int elevator1Passengers = 0;
	int elevator2Passengers = 0;
	int i = 0;
	
	while (elevator1Passengers < 4 && elevator2Passengers < 4)
	{
		// choose elevator randomly
		int elevator = rand() % 2 + 1;

		// increase passenger list in corresponding elevator
		if (elevator == 1)
			elevator1Passengers++;
		else
			elevator2Passengers++;

		// if two many passengers in current elevator, skip this iteration
		if (elevator1Passengers >= 4 || elevator2Passengers >= 4)
			continue;

		// create and active passenger
		passengerList[i] = new Passenger(elevator);
		passengerList[i]->Resume();
		i++;
		
		// sleep random value from 1000 to 1500 ms
		SLEEP(rand() & 500 + 1001);
	}
	
}
