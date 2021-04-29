#pragma once
#include <string>

struct Address
{
	std::string city;
	std::string street;
	unsigned int houseNumber;
};

struct Train
{
	unsigned int number;
	bool isFast;
	unsigned int roominess;
	unsigned int soldSeats;
};

class RailwayStation
{
public:
	RailwayStation() : name("Новый ЖД-вокзал"), location({"Киев", "Вокзальная", 1}), size(0), ptrains(nullptr) {}
	RailwayStation(std::string name_, Address location_, int size_, Train* pts_);
	RailwayStation(const RailwayStation& obj);
	~RailwayStation();

	RailwayStation& operator =(const RailwayStation& obj);
	const Address& getLocation()const;
	double averangeOccupancy()const;
	double availableSeats(unsigned int trainNumber)const;
	double totalAvailableSeats()const;
	double percentageFullyTrains()const;
	bool isExistdTrain(unsigned int trainNumber)const;
	bool addTrain(unsigned int number, bool isFast, unsigned int roominess, unsigned int soldSeats);
	bool addTrain(Train newTrain);
	bool deleteTrain(unsigned int trainNumber);
	
private:
	std::string name;
	Address location;
	int size;
	Train* ptrains;
};

std::ostream& operator <<(std::ostream& out, const RailwayStation& rs);
std::istream& operator >>(std::istream& out, RailwayStation& rs);