#include "Safety.h"

bool Safety::getBatteryCharged(){
    return batteryCharged;
}

bool Safety::getCablePluggedIn(){
    return cablePluggedIn;
}

bool Safety::getFailed(){
    return failed;
}

// there was supposed to be so much more here, we just did not use
void Safety::runSelfTest(bool pass){
    failed = !pass;
}

bool Safety::isCableattached(){
    return cableAttached;
}
bool Safety::isChild(int weight, int age){
    if(age <= 8 || weight < 55){
        return true;
    }
    else{
        return false;
    }
}
bool Safety::isTouching(){
    return touching;
}
bool Safety::isWet(){
    return wet;
}
bool Safety::safeEnvironment(){
    return safe;
}
