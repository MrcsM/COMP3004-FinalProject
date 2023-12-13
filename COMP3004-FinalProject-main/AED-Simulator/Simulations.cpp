#include "Simulations.h"
#include <random>

Simulations::Simulations() {
    simulationChoice = 5;
}

Simulations::~Simulations() {

}

void Simulations::pickTest(int uiComboBoxSelection){

    simulationChoice = uiComboBoxSelection;

    if (simulationChoice == 5) {
        simulationChoice = randomizeChoice();
    }
}

int Simulations::randomizeChoice() {

    std::random_device rd;
    std::uniform_int_distribution<int> dist(1,4);

    int randomNumber = dist(rd);

    return randomNumber;

}

int Simulations::getSimulation() {

    return simulationChoice;

}
