#include <iostream>
#include "RailwayStation.h"

using std::ostream;
using std::istream;
using std::cout;


ostream& operator <<(ostream& out, const RailwayStation& rs)
{
	out << rs.getLocation().city;
	return out;
}

istream& operator >>(istream& in, RailwayStation& rs)
{
	return in;
}

RailwayStation::RailwayStation(std::string name_, Address location_, int size_, Train* pts_)
{
	name = name_;
	location = location_;
	size = size_;
	ptrains = new Train[size];
	for (int i = 0; i < size; i++)
	{
		ptrains[i] = pts_[i];
	}
}

RailwayStation::RailwayStation(const RailwayStation& obj)
{
	name = obj.name;
	location = obj.location;
	size = obj.size;
	ptrains = new Train[size];
	for (int i = 0; i < size; i++)
	{
		ptrains[i] = obj.ptrains[i];
	}
}

RailwayStation::~RailwayStation()
{
	if (ptrains) delete[] ptrains;
	ptrains = NULL;
	size = 0;
}

RailwayStation& RailwayStation::operator=(const RailwayStation& obj)
{
	if (this == &obj) return *this;
	this->~RailwayStation();
	name = obj.name;
	location = obj.location;
	size = obj.size;
	ptrains = new Train[size];
	for (int i = 0; i < size; i++)
	{
		ptrains[i] = obj.ptrains[i];
	}
}

const Address& RailwayStation::getLocation() const
{
	return location;
}

double RailwayStation::averangeOccupancy() const
{
	double totalRoominess = 0, totalSoldSeats = 0, averengeOccupancy = 0;
	for (int i = 0; i < size; i++)
	{
		totalRoominess += ptrains[i].roominess;
		totalSoldSeats += ptrains[i].soldSeats;
	}
	averengeOccupancy = (totalSoldSeats / totalRoominess) * 100;
	return averengeOccupancy;
}

double RailwayStation::availableSeats(unsigned int trainNumber) const
{
	for (int i = 0; i < size; i++)
	{
		if (ptrains[i].number == trainNumber)
		{
			return ptrains[i].roominess - ptrains[i].soldSeats;
		}
	}
	return 0.0;
}

double RailwayStation::totalAvailableSeats() const
{
	double totalAvailableSeats = 0;
	for (int i = 0; i < size; i++)
	{
		totalAvailableSeats += availableSeats(ptrains[i].number);
	}
	return totalAvailableSeats;
}

double RailwayStation::percentageFullyTrains() const
{
	double totalFullyTrains = 0, percentageFullyTrains = 0;
	for (int i = 0; i < size; i++)
	{
		if (ptrains[i].roominess == ptrains[i].soldSeats) ++totalFullyTrains;
	}
	percentageFullyTrains = (totalFullyTrains / size) * 100;
	return percentageFullyTrains;
}

bool RailwayStation::isExistdTrain(unsigned int trainNumber) const
{
	for (int i = 0; i < size; i++)
	{
		if (ptrains[i].number == trainNumber) return true;
	}
	return false;
}

bool RailwayStation::addTrain(unsigned int number, bool isFast, unsigned int roominess, unsigned int soldSeats)
{
	if (isExistdTrain(number) || soldSeats > roominess) return false;
	
	Train newTrain{ number, isFast, roominess, soldSeats };
	return addTrain(newTrain);
	
}

bool RailwayStation::addTrain(Train newTrain)
{
	Train* ts = new Train[size + 1];
	for (int i = 0; i < size; i++)
	{
		ts[i] = ptrains[i];
	}
	ts[size] = newTrain;
	delete[] ptrains;
	ptrains = ts;
	++size;
	return true;
}

bool RailwayStation::deleteTrain(unsigned int trainNumber)
{
	if (!isExistdTrain(trainNumber)) return false;
	
	Train* ts = new Train[size - 1];
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		if (ptrains[i].number == trainNumber) continue;
		ts[j++] = ptrains[i];
	}
	delete[] ptrains;
	ptrains = ts;
	--size;
	return true;
}
