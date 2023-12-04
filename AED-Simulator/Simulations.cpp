#include "Simulations.h"
#include <random>

Simulations::Simulations() :ui() {

    simulationChoice = 5;

}

Simulations::~Simulations() {

}

int Simulations::pickTest(){

    simulationChoice = ui->getComboBoxSelection();

    if (simulationChoice == 5) {

        simulationChoice = randomizeChoice();
    }


    return simulationChoice;
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
