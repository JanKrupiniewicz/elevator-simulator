#include "Elevator.h"
#include <iostream>

void Elevator::addPerson(Person newP)
{
	house[newP.startF].people.push_back(newP);
	if (house[newP.startF].people.size() == 1 || addToQueue(newP)) {
		elevatorQueue.push(newP.startF);
	}
}

bool Elevator::addToQueue(Person newP)
{
	std::vector<int> checkP;
	int totalWeight{};
	for (Person& prs : house[newP.startF].people) {
		if (prs.id != -1 && newP.dir == prs.dir) {
			totalWeight += prs.weigth;
			checkP.push_back(prs.id);
		}
		if (totalWeight >= MAX_WEIGHT) {
			for (Person& prs : house[newP.startF].people) {
				for (int itr : checkP) {
					if (prs.id == itr) {
						prs.id = -1;
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool Elevator::operateFlor(int currFlor, Dir mainDir, Person mainPerson)
{
	bool checkFlor = false;
	for (auto it = passengers.begin(); it != passengers.end(); ) {
		Person prs = *it;
		if (prs.endF == currFlor) {
			if (&prs == &mainPerson) {
				checkFlor = true;
			}
			elevWeigth -= prs.weigth;
			it = passengers.erase(it);
			house[currFlor].newPeople++;
		}
		else {
			++it;
		}
	}

	for (auto it = house[currFlor].people.begin(); it != house[currFlor].people.end(); ) {
		Person prs = *it;
		if (prs.dir == mainDir) {
			if (elevWeigth + prs.weigth > MAX_WEIGHT)
				break;

			house[currFlor].delPeople++;
			elevWeigth += prs.weigth;
			passengers.push_back(prs);
			it = house[currFlor].people.erase(it);
		}
		else {
			++it;
		}
	}
	return checkFlor;
}

void Elevator::makeCourse()
{
	if (elevatorQueue.empty()) {
		return;
	}

	while(true) {
		int startFloor = elevatorQueue.front();
		elevatorQueue.pop();

		if (house[startFloor].people.empty()) {
			if (elevatorQueue.empty()) {
				break;
			}
			else {
				continue;
			}
		}
		
		Person mainPerson = *house[startFloor].people.begin();
		for (auto it = house[startFloor].people.begin(); it != house[startFloor].people.end(); ) {
			Person prs = *it;
			if (prs.dir == mainPerson.dir && elevWeigth + prs.weigth <= MAX_WEIGHT) {
				house[startFloor].delPeople++;
				elevWeigth += prs.weigth;
				it = house[startFloor].people.erase(it);
				passengers.push_back(prs);
			}
			else {
				++it;
			}
		}
		if (mainPerson.dir == UP) {
			while (startFloor < 5) {
				if (operateFlor(startFloor, UP, mainPerson))
					break;
				startFloor++;
			}
		}
		else {
			while (startFloor >= 0) {
				if (operateFlor(startFloor, DOWN, mainPerson))
					break;
				startFloor--;
			}
		}
		if (passengers.empty() && elevatorQueue.empty()) {
				break;
		}
	}
}

void Elevator::displayHouse()
{
	for (int i = 0; i < 5; i++) {
		std::cout << "FLOR: " << i << " statistics: new [" << house[i].newPeople << "], del [" << house[i].delPeople <<  "] " << std::endl;
		for (Person prs : house[i].people) {
			std::cout << prs.startF << " - > " << prs.endF << " ID:" << prs.id << std::endl;
		}
		std::cout << std::endl;
	}
}
