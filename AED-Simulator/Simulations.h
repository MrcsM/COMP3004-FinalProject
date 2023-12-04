#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include "mainwindow.h"

class Simulations{
    public:

        Simulations();
        ~Simulations();
        int pickTest();
        int getSimulation();

    private:

        MainWindow *ui;
        int simulationChoice;

        int randomizeChoice();

};

#endif
