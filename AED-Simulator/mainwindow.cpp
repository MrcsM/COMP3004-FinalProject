#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //t = new Timer();
    //v = new Victim();
    //v->randomizeVictim();
    //t->startElapsedTimer(1000);
    //t->startCPRTimer(1000);
    //v->printVictim();
}

MainWindow::~MainWindow()
{
    //delete t;
    delete ui;
}

