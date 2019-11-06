#pragma once
#include "../rt.h"
#include "../encodings.h"

class Passenger :
	public ActiveClass
{
public:
	Passenger();
private:
	int main(void) override;
};

