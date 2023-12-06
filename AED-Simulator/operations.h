#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Simulations.h"
#include "stdlib.h"

class Operations {

    public:

        Operations();
        ~Operations();

        void upload();
        bool depthCheck(float);
        int analyzeRhythm();
        void shock();
        void cpr();
        void normal();
        void ambulance();
        void successOfShock();
        bool getSuccess();
        void setSuccess(bool);
        int getShockCount();
        int getCprCount();
        void reset();

     private:

        float depthCheckValue;

        Simulations *sim;

        int simChosen;
        int shockCount;
        int cprCount;
        bool success;


};

#endif
