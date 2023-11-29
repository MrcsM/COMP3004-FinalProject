#include "timer.h"

Timer::Timer()
{
    elapsedTimer = new QTimer(this);
    connect(elapsedTimer, SIGNAL(timeout()), this, SLOT(ElapsedTimer_TimeOut_Event_Slot()));
    elapsedTimer->setInterval(1000);

    poweredOff = true;
    elapsedCount = 0;
    offCount = 0;

    compressionTimer = new QTimer(this);
    connect(compressionTimer, SIGNAL(timeout()), this, SLOT(CompressionTimer_TimeOut_Event_Slot()));
    compressionTimer->setInterval(1000);

    cprTimer = new QTimer(this);
    connect(cprTimer, SIGNAL(timeout()), this, SLOT(CPRTimer_TimeOut_Event_Slot()));
    cprTimer->setInterval(1000);

    cprCount = 0;
}

void Timer::startElapsedTimer(int interval)
{
    elapsedTimer->setInterval(interval);
    elapsedTimer->start();
}

void Timer::startCompressionTimer(int interval)
{
    compressionTimer->setInterval(interval);
    compressionTimer->start();
}

void Timer::startCPRTimer(int interval)
{
    cprTimer->setInterval(interval);
    cprTimer->start();
}

void Timer::stopElapsedTimer()
{
    elapsedTimer->stop();
}

void Timer::stopCompressionTimer()
{
    compressionTimer->stop();
}

void Timer::stopCPRTimer()
{
    cprTimer->stop();
}

void Timer::changeElapsedInterval(int newInterval)
{
    elapsedTimer->setInterval(newInterval);
}

void Timer::changeCompressionInterval(int newInterval)
{
    compressionTimer->setInterval(newInterval);
}

void Timer::changeCPRInterval(int newInterval)
{
    cprTimer->setInterval(newInterval);
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

void Timer::CompressionTimer_TimeOut_Event_Slot()
{
    // Call the Audible Beep Function Here
}

void Timer::CPRTimer_TimeOut_Event_Slot()
{
    // CPREND IS 20, MAKE EACH INTERVAL 1 SECOND LONG APPROX
    if (cprCount >= CPREND) {
        cprCount = 0;
        // 20 SECONDS OF CPR ENDED,
        // U WILL NEED TO LET THE MAIN FUNCTION KNOW SOMEHOW,
        // OR U COULD JUST IMPLEMENT THE CPR TIMER INTO THAT CLASS INSTEAD
        // REMEMBER THAT WHEN MAKING QTIMERS OUTSIDE MAINWINDOW, U GOTTA PUT ": public QObject" where it says class Whatever
        // ALSO RUN QMAKE, WHICH IS CLICKABLE IN BUILD ON THE BAR UPTOP, BEFORE CLICKING PLAY
        qDebug()  << "CPR Ended";
        cprTimer->stop();
    } else {
        cprCount += 1;
    }
}
