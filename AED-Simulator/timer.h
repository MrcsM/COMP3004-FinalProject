#ifndef TIMER_H
#define TIMER_H

#include <qtimer.h>
#include "QDebug"
#define CPREND 20

class Timer : public QObject
{
    Q_OBJECT

    public:
        Timer();

        void startElapsedTimer(int);

        void stopElapsedTimer();

        void changeElapsedInterval(int);

        void setPoweredOffToTrue();
        void setPoweredOffToFalse();

        int getElapsedTime() {
            return elapsedCount;
        }

    private slots:
        void ElapsedTimer_TimeOut_Event_Slot();

    private:
        QTimer *elapsedTimer; // how long it's been powered on, resets 5 seconds after it has been turned off
        bool poweredOff;
        int elapsedCount;
        int offCount;
};

#endif // TIMER_H
