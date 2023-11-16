#pragma once
#include <list>
#include <time.h>

enum Dir {
	UP, DOWN
};

struct Person
{
	int id;
	int startF;
	int endF;
	int weigth;
	Dir dir;

	Person() = default;

	Person(int id, int startF, int endF)
		:id(id), startF(startF), endF(endF) 
	{
		// srand(time(NULL));
		// weigth = rand() % 20 + 60;
		weigth = 70;

		if (endF - startF > 0) {
			dir = UP;
		}
		else {
			dir = DOWN;
		}
	}
};

struct Flor
{
	std::list<Person> people;
	int newPeople;
	int delPeople;

	Flor() = default;
};