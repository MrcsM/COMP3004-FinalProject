#ifndef SAFETY_H
#define SAFETY_H

#include "victim.h"

class Safety: public Victim {
    public:
        void runSelfTest(bool);

        //getters and setters
        bool getFailed();

        // figure this out
        bool getBatteryCharged();
        void setBatteryCharged(bool batteryStatus);

    private:
        bool failed;
        bool batteryCharged;
};

#endif
