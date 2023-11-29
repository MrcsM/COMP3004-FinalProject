#ifndef VICTIM_H
#define VICTIM_H

#include <iostream>
#include "stdlib.h"
#include <qtimer.h>
#include "QDebug"

#define MAXCHAR 8
#define MAXWEIGHT 635
#define MAXAGE 123
#define MALECHOSEN 1
#define FEMALECHOSEN 2
#define OTHERCHOSEN 3

class Victim : public QObject
{
public:
    Victim();
    void setWeight(int);
    void setAge(int);
    void setSex(char);
    int getWeight();
    int getAge();
    char getSex();
    void randomizeVictim();
    void printVictim();
private:
    int weight;
    int age;
    char sex;
};

#endif // VICTIM_H
