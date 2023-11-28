#include "victim.h"

Victim::Victim()
{
    weight = 0;
    age = 0;
    sex = 0;
}

void Victim::setWeight(int w)
{
    if (w > MAXWEIGHT) {
        std::cout << "Please enter a weight below " << MAXWEIGHT << ".\n" << std::endl;
    }
    weight = w;
}

void Victim::setAge(int a)
{
    age = a;
}

void Victim::setSex(char s)
{
    sex = s;
}

int Victim::getWeight()
{
    return weight;
}

int Victim::getAge()
{
    return weight;
}

char Victim::getSex()
{
    return sex;
}

void Victim::randomizeVictim()
{
    srand(time(NULL));

    weight = rand() % MAXWEIGHT + 1;
    age = rand() % MAXAGE;
    int sexSelectorTemp = rand() % 3 + 1;

    if (sexSelectorTemp == MALECHOSEN) {
        sex = 'M';
    } else if (sexSelectorTemp == FEMALECHOSEN) {
        sex = 'F';
    } else if (sexSelectorTemp == OTHERCHOSEN) {
        sex = 'O';
    }

}

void Victim::printVictim()
{
    qDebug() << "Weight: " << weight << "\nAge:"  << age << "\nSex:" << sex << "\n";
}
