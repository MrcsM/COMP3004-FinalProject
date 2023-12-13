#include "Safety.h"

// change this stuff later so battery is actually used
bool Safety::getBatteryCharged(){
    return batteryCharged;
}

bool Safety::getFailed(){
    return failed;
}

// there was supposed to be so much more here, we just did not use
void Safety::runSelfTest(bool pass){
    failed = !pass;
}
