#include <iostream>
#include <Windows.h>
#include "RailwayStation.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Address KharkivPassengerLocation{ "Харьков", "Вокзальная", 1 };

	Train t1{ 123, false, 100, 56 };
	Train t2{ 55, true, 50, 40 };

	Train* ts = new Train[2];
	ts[0] = t1;
	ts[1] = t2;

	RailwayStation KharkivPassenger("Харьпасс", KharkivPassengerLocation, 2, ts);

	KharkivPassenger.addTrain(1223, true, 150, 15);
	KharkivPassenger.deleteTrain(1223);



	return 0;
}