#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "mainwindow.h"
#include "Simulations.h"

class Operations{

    public:

        Operations();
        ~Operations();

        void upload();
        bool depthCheck();
        void analyzeRhythm();
        void shock();
        void cpr();
        void normal();
        void ambulance();

     private:

        float depthCheckValue;

        Simulations *sim;
        MainWindow *ui;

        Timer *t;
        Prompt *p;

        int simChosen;
        int shockCount;
        int cprCount;
        bool success;

        bool successOfShock();


};

#endif
