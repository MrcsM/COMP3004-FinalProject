#include "operations.h"
#include  <random>

Operations::Operations() {

    depthCheckValue  = 0;
    simChosen = 0;
    success = false;
    shockCount  = 0;
    cprCount = 0;

}

Operations::~Operations() {

}

bool Operations::depthCheck(float uiDepth){

    depthCheckValue = uiDepth;

    if (1.9 < depthCheckValue && depthCheckValue < 2.5) {
        return true;
    } else {
        return false;
    }
}

int Operations::analyzeRhythm() {

    simChosen = sim->getSimulation();

    //Timer for five seconds with voice prompt
    //For this timer, we could just make another function that calls the timer only then calls this function
    //A commented example will be at the bottom of the class

    if (simChosen == 1) {
        //normal();
        return 1;
    } else if (simChosen == 2 || simChosen == 3) {
        //shock();
        return 2;
    } else {
        //cpr();
        return 3;
    }

}

void Operations::shock() {
    shockCount += 1;
}

void Operations::cpr() {

    srand(time(NULL));
    int shockableRhythmReturns = rand() % 3 + 1;
    if (shockableRhythmReturns == 1) {
        setSuccess(false);
    }

     cprCount++;
}

void Operations::successOfShock() {

    std::random_device rd;
    std::uniform_int_distribution<int> dist(1,4);
    std::uniform_int_distribution<int> dist1(1,3);
    std::uniform_int_distribution<int> dist2(1,2);

    int randomNumberShock = dist(rd);
    int randomNumberShock1 = dist1(rd);
    int randomNumberShock2 = dist2(rd);

    if (shockCount == 0) {
        if (randomNumberShock == 1) {
            simChosen = 1;
            setSuccess(true);
            return;
        }
    } else if (shockCount == 1) {
        if (randomNumberShock1 ==  1) {
            simChosen = 1;
            setSuccess(true);
            return;
        }
    } else if (shockCount >  1 && shockCount < 4) {
        if (randomNumberShock2 ==  1) {
            simChosen = 1;
            setSuccess(true);
            return;
        }
    } else if (shockCount == 4) {
        simChosen = 1;
        setSuccess(true);
        return;
    } else {
        ambulance();
    }
    setSuccess(false);
    return;

}

bool Operations::getSuccess()
{
    return success;
}

void Operations::setSuccess(bool newState)
{
    success = newState;
}

int Operations::getShockCount()
{
    return shockCount;
}

int Operations::getCprCount()
{
    return cprCount;
}

void Operations::reset()
{
    depthCheckValue  = 0;
    simChosen = 0;
    success = false;
    shockCount  = 0;
    cprCount = 0;
}

void Operations::normal() {

    //Timer, voice prompt/print to console, and program ends - optional timer - 5 seconds

}

void Operations::ambulance() {

    //Timer, voice prompt/print to console, and program ends - optional timer - 5 seconds

}



