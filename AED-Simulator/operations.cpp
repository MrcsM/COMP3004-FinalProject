#include "operations.h"
#include  <random>

Operations::Operations() :sim(), ui(), t(), p() {

    depthCheckValue  = 0;
    simChosen = 0;
    success = false;
    shockCount  = 0;
    cprCount = 0;

}

Operations::~Operations() {

}

bool Operations::depthCheck(){

    depthCheckValue = ui->getDepth();

    if(1.9 < depthCheckValue && depthCheckValue < 2.5){
        return true;
    }
    else{
        return false;
    }
}

void Operations::analyzeRhythm() {

    simChosen = sim->getSimulation();

    ui->changeRhythm(simChosen);

    //Timer for five seconds with voice prompt
    //For this timer, we could just make another function that calls the timer only then calls this function
    //A commented example will be at the bottom of the class

    if (simChosen == 1) {

        normal();

    } else if (simChosen == 2 || simChosen == 3) {

        shock();

    } else {

        cpr();

    }

}

void Operations::shock() {

    if (successOfShock()) {

        shockCount++;
        //analyzeTimer() - only if you did class below example, and remove analyzeRhythm()
        analyzeRhythm();

    } else {

        shockCount++;
        cpr();

    }

}

//Need timer with voice prompts
void Operations::cpr() {

     if (cprCount == 4) {
         ambulance();
     }
     cprCount++;
     //timer to wait the twenty seconds and mimic compressions

     //analyzeTimer() - only if you did class below example, and remove analyzeRhythm()v
     analyzeRhythm();
}

bool Operations::successOfShock() {

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
            return true;
        }

    } else if (shockCount == 1) {

        if (randomNumberShock1 ==  1) {
            simChosen = 1;
            return true;
        }

    } else if (shockCount >  1 && shockCount < 4) {

        if (randomNumberShock2 ==  1) {
            simChosen = 1;
            return true;
        }

    } else {

        ambulance();

    }

    return false;

}

void Operations::normal() {

    //Timer, voice prompt/print to console, and program ends - optional timer - 5 seconds

}

void Operations::ambulance() {

    //Timer, voice prompt/print to console, and program ends - optional timer - 5 seconds

}

//void Operations::analyzeTimer() {
    //calls timer for analyzing and then stopTimer() would call analyzeRhythm
//Other comments what to change if you do this approach
//}



