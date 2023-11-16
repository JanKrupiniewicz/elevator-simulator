#pragma once
#include <queue>
#include <list>
#include "Flor.h"

#define MAX_WEIGHT 500

class Elevator
{
private:
	Flor house[5];
	Dir currDir;
	int elevWeigth;
	std::list<Person> passengers;
	std::queue<int> elevatorQueue;

	bool operateFlor(int currFlor, Dir mainDir, Person mainPerson);
	bool addToQueue(Person newP);
public:
	Elevator() = default;
	void addPerson(Person newP);
	void makeCourse();
	void displayHouse();
};

