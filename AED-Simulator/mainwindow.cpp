#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>


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

    mainTimer = new QTimer(this);
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(MainTimer_TimeOut_Event_Slot()));
    mainTimer->setInterval(1000);
    mainCount = 0;
    depthCheck = false;

    ui->VictimChoice->addItem("Adult");
    ui->VictimChoice->addItem("Child");

    ui->PadsChoice->addItem("Adult");
    ui->PadsChoice->addItem("Child");

    p = new Prompt();
    t = new Timer();
    sim = new Simulations();
    op = new Operations();

    ui->rhythmcomboBox->addItem("Normal");
    ui->rhythmcomboBox->addItem("Vfib");
    ui->rhythmcomboBox->addItem("Vtach");
    ui->rhythmcomboBox->addItem("Unknown");
    ui->rhythmcomboBox->addItem("Random");
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
};

void MainWindow::shockIndicator() {
    if (!powerState) {
        ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(164, 157, 157);");
        return;
    }
    // if charged:
    ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(183, 197, 86);");
    // if not: ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(164, 157, 157);");
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
        ui->shock_count->setText("SHOCK COUNT: " + QString::number(op->getShockCount()));
        ui->cpr_count->setText("CPR COUNT: " + QString::number(op->getCprCount()));
        ui->elapsed_time->setText("ELAPSED TIME: " + formatSeconds(t->getElapsedTime()));

        // when bar graph for CPR depth of compressions is added, put here (need to add in mainwindow GUI first)
        // when ECG waveform is added, put here (needs to be added in mainwindow GUI first)

        // get voice state and print it out
        ui->visual_prompt->setText(p->playVoicePrompt(currentPrompt));
    } else {
        ui->shock_count->setText("");
        ui->cpr_count->setText("");
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

/*
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
*/

void MainWindow::MainTimer_TimeOut_Event_Slot()
{
    // START
    if (mainCount == 0) {
        makeVictim();
    }

    // PERFORM SELF TEST
    if (mainCount == 3) {

    }

    // BEGIN PROPER OPERATION
    if (mainCount >= 5) {
        statusIndicator();
    }

    if (mainCount == 5) {
        currentPrompt = Voice(UNIT_OK);
    }

    if (mainCount == 7) {
        currentPrompt = Voice(STAY_CALM);
    }

    if (mainCount == 9) {
        currentPrompt = Voice(CHECK_RESPONSIVENESS);
    }

    if (mainCount == 15) {
        currentPrompt = Voice(CALL_FOR_HELP);
    }

    if (mainCount == 20) {
        currentPrompt = Voice(ATTACH_DEFIB);
    }

    if (mainCount == 30 && v->getAge() == 'A' && ui->PadsChoice->currentIndex() == 0) {
        // ADULT VICTIM AND ADULT PADS
        currentPrompt = Voice(ADULT_PADS);
    } else if (mainCount == 30 && v->getAge() == 'C' && ui->PadsChoice->currentIndex() == 1) {
        // CHILD VICTIM AND CHILD PADS
        currentPrompt = Voice(PEDIATRIC_PADS);
    } else if (mainCount == 30 && ((v->getAge() == 'A' && ui->PadsChoice->currentIndex() == 1) || (v->getAge() == 'C' && ui->PadsChoice->currentIndex() == 0))) {
        // MISMATCH
        mainCount = 21; // RETURN TO BEGINNING OF STEP
    }

    if (mainCount == 35) {
        currentPrompt = Voice(DONT_TOUCH);
    }

    // DETERMINE IF SHOCK ADVISED
    if (mainCount == 40) {
        if (op->getSuccess() == false) {
            sim->pickTest(ui->rhythmcomboBox->currentIndex() + 1);
        } else if (op->getSuccess() == true) {
            sim->pickTest(1);
        }

        int simSuccess = sim->getSimulation();

        if (op->getCprCount() == 5 || op->getShockCount() == 5) {
            // normal: skip to ambulance arrives
            mainCount = 90;
        } else if (simSuccess == 1 || simSuccess == 4) {
            // cpr: skip to cpr
            currentPrompt = Voice(NO_SHOCK_ADVISED);
            mainCount = 55;
        } else if (simSuccess == 2 || simSuccess == 3) {
            // shock: deliver shock
            currentPrompt = Voice(SHOCK_ADVISED);
        }
    }

    if (mainCount == 42) {
        //heartButtonLight(true);   HEART BUTTON LIGHT SEEMS TO BE BROKEN GRAPHICALLY
    }

    // DO SHOCKING AFTER 5 SECONDS
    if (mainCount == 45) {
        currentPrompt = Voice(SHOCK_DELIVERED);
        op->shock();
        op->successOfShock(); //performs op->setSuccess(true);
        //heartButtonLight(false);
        mainCount = 32; // RETURN TO START OF SCAN
    }

    // START OF CPR
    if (mainCount == 60) {
        currentPrompt = Voice(START_CPR);
    }

    if (60 <= mainCount && mainCount <= 80) {
        //check if compressions are good for an adult, if not, then change that!!!
        depthCheck = op->depthCheck(ui->depthBox->text().toFloat());
        if (v->getAge() == 'A' && depthCheck == false) {
            currentPrompt = Voice(PUSH_HARDER);
        } else {
            currentPrompt = Voice(GOOD_COMPRESSIONS);
        }
    }

    if (mainCount == 80) {
        currentPrompt = Voice(STOP_CPR);
        op->cpr();
        mainCount = 32; // RETURN TO START OF SCAN
    }


    if (mainCount == 95) {
        currentPrompt = Voice(AMBULANCE_ARRIVES);
        // Turn off?
    }

    lcdDisplay();
    shockIndicator();
    indicatorLights();
    mainCount += 1;

}


void MainWindow::on_power_button_clicked()
{
    if (powerState == false) {
        mainCount = 0;
        mainTimer->start();
        powerState = true;
        op->setSuccess(false);
        depthCheck = false;

        ui->on_label->setStyleSheet(ui->on_label->styleSheet() + "color: rgb(51, 209, 122);");
        ui->off_label->setStyleSheet(ui->off_label->styleSheet() + "color: rgb(164, 157, 157);");
        t->setPoweredOffToFalse();
        t->startElapsedTimer(1000);

        currentPrompt = Voice(OFF);
    } else {
        mainTimer->stop();
        powerState = false;
        ui->on_label->setStyleSheet(ui->on_label->styleSheet() + "color: rgb(164, 157, 157);");
        ui->off_label->setStyleSheet(ui->off_label->styleSheet() + "color: rgb(51, 209, 122);");

        lcdDisplay();
        shockIndicator();
        indicatorLights();
        statusIndicator();
        op->reset();

        t->setPoweredOffToTrue();
    }
}

void MainWindow::makeVictim()
{
    // make victim
    v = new Victim();

    if (ui->VictimChoice->currentIndex() == 0) {
        // ADULT VICTIM
        v->setAge('A');
    } else if (ui->VictimChoice->currentIndex() == 1) {
        // CHILD VICTIM
        v->setAge('C');
    }
}

void MainWindow::changeRhythm(int rhythm) {

   QPixmap normal("me/student/COMP3004-FinalProject-main/AED-Simulator/images/normal.png");
   QPixmap vfib("me/student/COMP3004-FinalProject-main/AED-Simulator/images/vfib.jpeg");
   QPixmap vtach("me/student/COMP3004-FinalProject-main/AED-Simulator/images/vtach.jpeg");
   QPixmap afib("me/student/COMP3004-FinalProject-main/AED-Simulator/images/afib.jpeg");
   int width = ui->rhythmImage->width();
   int height = ui->rhythmImage->height();

   if (rhythm == 1) {

       ui->rhythmImage->setPixmap(normal.scaled(width,height,Qt::KeepAspectRatio));

   } else if (rhythm == 2) {

       ui->rhythmImage->setPixmap(vfib.scaled(width,height,Qt::KeepAspectRatio));

   } else if (rhythm == 3) {

       ui->rhythmImage->setPixmap(vtach.scaled(width,height,Qt::KeepAspectRatio));

   } else if (rhythm == 4) {

       ui->rhythmImage->setPixmap(afib.scaled(width,height,Qt::KeepAspectRatio));

   }

}

int MainWindow::getComboBoxSelection() {

    QString tempSelected = ui->rhythmcomboBox->currentText();

    if (tempSelected == "Normal") {

        return 1;

    } else if (tempSelected == "Vfib") {

        return 2;

    } else if (tempSelected == "Vtach") {

        return 3;

    } else if (tempSelected == "Unknown") {

        return 4;

    } else if (tempSelected == "Random") {

        return 5;

    } else {

        return 5;

    }

}

