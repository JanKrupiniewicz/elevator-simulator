#include <iostream>
#include "Flor.h"
#include "Elevator.h"


Person getPerson(int id) {
    int startF; std::cin >> startF;
    int endF; std::cin >> endF;
    return { id, startF, endF };
}

int main()
{
    Elevator myElevator;
    int numP = 1;
    int itr{};
    while (numP) {
        std::cin >> numP;
        for (int i = 0; i < numP; i++, itr++) {
            Person new_person = getPerson(itr);
            myElevator.addPerson(new_person);
        }
        std::cout << "B E F O R E " << std::endl;
        myElevator.displayHouse();
        myElevator.makeCourse();
        std::cout << "A F T E R " << std::endl;
        myElevator.displayHouse();
        itr++;
    }
}