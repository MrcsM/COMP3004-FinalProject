#include "timer.h"

Timer::Timer()
{
    elapsedTimer = new QTimer(this);
    connect(elapsedTimer, SIGNAL(timeout()), this, SLOT(ElapsedTimer_TimeOut_Event_Slot()));
    elapsedTimer->setInterval(1000);

    poweredOff = true;
    elapsedCount = 0;
    offCount = 0;
}

void Timer::startElapsedTimer(int interval)
{
    elapsedTimer->setInterval(interval);
    elapsedTimer->start();
}

void Timer::stopElapsedTimer()
{
    elapsedTimer->stop();
}

void Timer::changeElapsedInterval(int newInterval)
{
    elapsedTimer->setInterval(newInterval);
}

void Timer::setPoweredOffToTrue()
{
    poweredOff = true;
}

void Timer::setPoweredOffToFalse()
{
    poweredOff = false;
}

void Timer::ElapsedTimer_TimeOut_Event_Slot()
{
    //THIS FUNCTION IS JUST COUNTING HOW MUCH TIME THE PROGRAM HAS BEEN ON FOR
    // AND IT TURNS OFF AFTER 5 SECONDS OF BEING POWEREDOFF
    if (poweredOff == true) {
        offCount += 1;
    }
    if (offCount == 5) {
        offCount = 0;
        elapsedCount = 0;
        elapsedTimer->stop();
    } else {
        elapsedCount += 1;

        qDebug() << elapsedCount;
    }

}
