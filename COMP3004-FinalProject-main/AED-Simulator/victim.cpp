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

void Victim::setAge(char a)
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

char Victim::getAge()
{
    return age;
}

char Victim::getSex()
{
    return sex;
}

void Victim::randomizeVictim()
{
    srand(time(NULL));

    weight = rand() % MAXWEIGHT + 1;

    int ageSelectorTemp = rand() % 2 + 1;
    if (ageSelectorTemp == 0) {
        age = 'A';
    } else if (ageSelectorTemp == 1) {
        age = 'C';
    }

    int sexSelectorTemp = rand() % 3 + 1;
    if (sexSelectorTemp == MALECHOSEN) {
        sex = 'M';
    } else if (sexSelectorTemp == FEMALECHOSEN) {
        sex = 'F';
    } else if (sexSelectorTemp == OTHERCHOSEN) {
        sex = 'O';
    }

}
