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
    void setAge(char);
    void setSex(char);
    int getWeight();
    char getAge();
    char getSex();
    void randomizeVictim();
private:
    int weight;
    char age;
    char sex;
};

#endif // VICTIM_H
