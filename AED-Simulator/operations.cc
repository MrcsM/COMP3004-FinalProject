#include "operations.h"

bool Operations::depthCheck(float depth){
    if(1.9 < depth && depth < 2.1){
        return true;
    }
    else{
        return false;
    }
}

