#pragma once
#include "../rt.h"
#include "..//elevator.h"
#include "../encodings.h"

class Passenger :
	public ActiveClass
{
public:
	Passenger(int _elevatorNumber = rand() % 2+1);
private:
	int main(void) override;

	int elevator;
	CTypedPipe<int> ioToDispatcherPipeline = CTypedPipe<int>("ioToDispatcherPipeline", 100);
};

