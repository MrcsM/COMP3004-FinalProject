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
        void startCompressionTimer(int);
        void startCPRTimer(int);

        void stopElapsedTimer();
        void stopCompressionTimer();
        void stopCPRTimer();

        void changeElapsedInterval(int);
        void changeCompressionInterval(int);
        void changeCPRInterval(int);

        void setPoweredOffToTrue();
        void setPoweredOffToFalse();

        int getElapsedTime() {
            return elapsedCount;
        }

    private slots:
        void ElapsedTimer_TimeOut_Event_Slot();
        void CompressionTimer_TimeOut_Event_Slot();
        void CPRTimer_TimeOut_Event_Slot();

    private:
        QTimer *elapsedTimer; // how long it's been powered on, resets 5 seconds after it has been turned off
        bool poweredOff;
        int elapsedCount;
        int offCount;

        QTimer *compressionTimer; // adapted to the patient's compression rate, use changeeCompressionInterval to change to correct heart compression rate

        QTimer *cprTimer; // 2 minutes for CPR length
        int cprCount;
};

#endif // TIMER_H
