#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
#include "timer.h"
#include "victim.h"
#include "prompt.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void indicatorLights();
    void shockIndicator();
    void statusIndicator();
    void lcdDisplay();
    void heartButtonLight(bool);

private:
    Ui::MainWindow *ui;
    Timer *t;
    Victim *v;
    int curr;
    Prompt *p;

    Voice currentPrompt;
    bool powerState;

private slots:
    void powerButton();

    void cycle();

    QString formatSeconds(int seconds) {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        int remain = seconds % 60;

        QString format;

        if (hours > 0) {
            format += QString::number(hours) + "h";
        }

        if (minutes > 0) {
            format += QString::number(minutes) + "m";
        }

        if (remain > 0 || (hours == 0 && minutes == 0)) {
            format += QString::number(remain) + "s";
        }

        return format;
    }

};
#endif // MAINWINDOW_H
