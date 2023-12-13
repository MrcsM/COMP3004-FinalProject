#ifndef SIMULATIONS_H
#define SIMULATIONS_H

class Simulations {
    public:

        Simulations();
        ~Simulations();
        void pickTest(int);
        int getSimulation();

    private:
        int simulationChoice;

        int randomizeChoice();

};

#endif
