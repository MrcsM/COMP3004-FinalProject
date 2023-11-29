#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->off_label->setStyleSheet(ui->off_label->styleSheet() + "color: rgb(51, 209, 122);");

    ui->disabled_failed->setVisible(true);
    ui->disabled_pass->setVisible(true);
    ui->pass_label->setVisible(false);
    ui->failed_label->setVisible(false);

    currentPrompt = Voice(OFF);
    powerState = false;

    p = new Prompt();
    t = new Timer();
    //v = new Victim();
    //v->randomizeVictim();
    //t->startCPRTimer(1000);
    //v->printVictim();

    connect(ui->power_button, SIGNAL(pressed()), this, SLOT (powerButton()));
}

MainWindow::~MainWindow()
{
    delete t;
    delete ui;
}

void MainWindow::indicatorLights() {
    ui->responsiveness_indicator->setStyleSheet(ui->responsiveness_indicator->styleSheet() + "background-color: rgb(119, 118, 123);");
    ui->help_indicator->setStyleSheet(ui->help_indicator->styleSheet() + "background-color: rgb(119, 118, 123);");
    ui->defibs_indicator->setStyleSheet(ui->defibs_indicator->styleSheet() + "background-color: rgb(119, 118, 123);");
    ui->analyzing_indicator->setStyleSheet(ui->analyzing_indicator->styleSheet() + "background-color: rgb(119, 118, 123);");
    ui->cpr_indicator->setStyleSheet(ui->cpr_indicator->styleSheet() + "background-color: rgb(119, 118, 123);");

    if (currentPrompt == Voice(CHECK_RESPONSIVENESS)) {
        ui->responsiveness_indicator->setStyleSheet(ui->responsiveness_indicator->styleSheet() + "background-color: rgb(51, 209, 122);");
    } else if (currentPrompt == Voice(CALL_FOR_HELP)) {
        ui->help_indicator->setStyleSheet(ui->help_indicator->styleSheet() + "background-color: rgb(51, 209, 122);");
    } else if (currentPrompt == Voice(ATTACH_DEFIB)) {
        ui->defibs_indicator->setStyleSheet(ui->defibs_indicator->styleSheet() + "background-color: rgb(51, 209, 122);");
    } else if (currentPrompt == Voice(DONT_TOUCH)) {
        ui->analyzing_indicator->setStyleSheet(ui->analyzing_indicator->styleSheet() + "background-color: rgb(51, 209, 122);");
    } else if (currentPrompt == Voice(START_CPR)) {
        ui->cpr_indicator->setStyleSheet(ui->cpr_indicator->styleSheet() + "background-color: rgb(51, 209, 122);");
    }

    QTimer::singleShot(1000, this, &MainWindow::indicatorLights);
};

void MainWindow::shockIndicator() {
    if (!powerState) {
        ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(164, 157, 157);");
        return;
    }
    // if charged:
    ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(183, 197, 86);");
    // if not: ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(164, 157, 157);");

    QTimer::singleShot(500, this, &MainWindow::shockIndicator);
};

void MainWindow::statusIndicator() {
    if (powerState) {
        // if self test passes, whats below is what would show (requires Simulations)
        //currentPrompt = Voice(UNIT_OK);
        ui->pass_label->setVisible(true);
        ui->disabled_pass->setVisible(false);
        ui->disabled_failed->setVisible(true);
    } else {
        ui->disabled_failed->setVisible(true);
        ui->disabled_pass->setVisible(true);
        ui->pass_label->setVisible(false);
        ui->failed_label->setVisible(false);
    }
};

void MainWindow::lcdDisplay() {
    if (powerState) {
        ui->shock_count->setText("SHOCK COUNT: 0"); // get from Display when added
        ui->elapsed_time->setText("ELAPSED TIME: " + formatSeconds(t->getElapsedTime()));

        // when bar graph for CPR depth of compressions is added, put here (need to add in mainwindow GUI first)
        // when ECG waveform is added, put here (needs to be added in mainwindow GUI first)

        // get voice state and print it out
        ui->visual_prompt->setText(p->playVoicePrompt(currentPrompt));

        QTimer::singleShot(1000, this, &MainWindow::lcdDisplay);
    } else {
        ui->shock_count->setText("");
        ui->elapsed_time->setText("");
        ui->visual_prompt->setText("");
    }
};

// this gets called when shocks are administered
// so when shock, call heartButtonLight(true), right after heartButtonLight(false)
void MainWindow::heartButtonLight(bool shock) {
    if (shock) {
        ui->shock_indicator->setStyleSheet(ui->on_label->styleSheet() + "background-color: rgb(51, 209, 122);");
    } else {
        ui->shock_indicator->setStyleSheet(ui->on_label->styleSheet() + "background-color: rgb(164, 157, 157);");
    }
};

void MainWindow::cycle() {
    if (!powerState) {
        currentPrompt = Voice(OFF);
        return;
    }

    if (currentPrompt == Voice(OFF)) {
        currentPrompt = Voice(UNIT_OK);
    } else if (currentPrompt == Voice(UNIT_OK)) {
        currentPrompt = Voice(STAY_CALM);
    } else if (currentPrompt == Voice(STAY_CALM)) {
        currentPrompt = Voice(CHECK_RESPONSIVENESS);
    } else if (currentPrompt == Voice(CHECK_RESPONSIVENESS)) {
        currentPrompt = Voice(CALL_FOR_HELP);
    } else if (currentPrompt == Voice(CALL_FOR_HELP)) {
        currentPrompt = Voice(ATTACH_DEFIB);
    } else if (currentPrompt == Voice(ATTACH_DEFIB)) {
        currentPrompt = Voice(ADULT_PADS);
    } else if (currentPrompt == Voice(ADULT_PADS)) {
        currentPrompt = Voice(DONT_TOUCH);
    } else if (currentPrompt == Voice(DONT_TOUCH)) {
        currentPrompt = Voice(SHOCK_ADVISED);
    } else if (currentPrompt == Voice(SHOCK_ADVISED)) {
        currentPrompt = Voice(SHOCK_DELIVERED);
    } else if (currentPrompt == Voice(SHOCK_DELIVERED)) {
        currentPrompt = Voice(START_CPR);
    } else if (currentPrompt == Voice(START_CPR)) {
        currentPrompt = Voice(CHECK_RESPONSIVENESS);
    }

    QTimer::singleShot(1000, this, &MainWindow::cycle);
}

void MainWindow::powerButton() {
    // add check for charge first so it doesn't turn the machine off if we're just trying to discharge

    powerState = !powerState;

    if (powerState) {
        ui->on_label->setStyleSheet(ui->on_label->styleSheet() + "color: rgb(51, 209, 122);");
        ui->off_label->setStyleSheet(ui->off_label->styleSheet() + "color: rgb(164, 157, 157);");

        currentPrompt = Voice(OFF);

        t->setPoweredOffToFalse();
        t->startElapsedTimer(1000);

        lcdDisplay();
        shockIndicator();
        indicatorLights();

        // after self test is done, call this one
        statusIndicator();

        // testing indicator lights, will be removed before release
        cycle();
    } else {
        ui->on_label->setStyleSheet(ui->on_label->styleSheet() + "color: rgb(164, 157, 157);");
        ui->off_label->setStyleSheet(ui->off_label->styleSheet() + "color: rgb(51, 209, 122);");

        lcdDisplay();
        shockIndicator();
        indicatorLights();
        statusIndicator();

        t->setPoweredOffToTrue();
        t->stopElapsedTimer();
    }
}
