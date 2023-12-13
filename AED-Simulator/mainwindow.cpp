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
    ui->heart_label_discharged->setVisible(true);
    ui->heart_label->setVisible(false);

    currentPrompt = Voice(OFF);
    powerState = false;

    mainTimer = new QTimer(this);
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(MainTimer_TimeOut_Event_Slot()));
    mainTimer->setInterval(1000);
    mainCount = 0;
    depthCheck = false;
    nothingHappens = 0;
    batteryHealth = 100;
    batteryMinus = false;
    afterShock = false;

    ui->VictimChoice->addItem("Adult");
    ui->VictimChoice->addItem("Child");

    ui->PadsChoice->addItem("Adult");
    ui->PadsChoice->addItem("Child");

    p = new Prompt();
    t = new Timer();
    sim = new Simulations();
    op = new Operations();
    safety = new Safety();

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
    } else if (currentPrompt == Voice(START_CPR) || currentPrompt == Voice(CONTINUE_CPR) || currentPrompt == Voice(GIVE_TWO_BREATHS) || currentPrompt == Voice(PUSH_HARDER) || currentPrompt == Voice(GOOD_COMPRESSIONS)) {
        ui->cpr_indicator->setStyleSheet(ui->cpr_indicator->styleSheet() + "background-color: rgb(51, 209, 122);");
    }
};

void MainWindow::statusIndicator() {
    if (powerState) {
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
        // display the shock count, cpr count, elapsed time
        ui->shock_count->setText("SHOCK COUNT: " + QString::number(op->getShockCount()));
        ui->cpr_count->setText("CPR COUNT: " + QString::number(op->getCprCount()));
        ui->elapsed_time->setText("ELAPSED TIME: " + formatSeconds(t->getElapsedTime()));
        ui->batteryLabel->setText("BATTERY HEALTH: " + QString::number(batteryHealth) + "%");

        // get voice state and print it out
        ui->visual_prompt->setText(p->playVoicePrompt(currentPrompt));
    } else {
        // huge reset
        ui->shock_count->setText("");
        ui->cpr_count->setText("");
        ui->elapsed_time->setText("");
        ui->batteryLabel->setText("");
        ui->visual_prompt->setText("");
        ui->visual_prompt->setText("");
    }
};

// this gets called when shocks are administered
// so when shock, call heartButtonLight(true), right after heartButtonLight(false)
void MainWindow::heartButtonLight(bool shock) {
    if (shock) {
        ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(51, 209, 122);");
        ui->heart_label_discharged->setVisible(false);
        ui->heart_label->setVisible(true);
    } else {
        ui->shock_indicator->setStyleSheet(ui->shock_indicator->styleSheet() + "background-color: rgb(164, 157, 157);");
        ui->heart_label_discharged->setVisible(true);
        ui->heart_label->setVisible(false);
    }
};

void MainWindow::MainTimer_TimeOut_Event_Slot()
{
    // START
    if (mainCount == 0) {
        makeVictim();
        //v->randomizeVictim() - if we wanted to we could!
    }

    if (mainCount == 3) {
        ui->self_test->hide();

        if (ui->self_test->checkState() == Qt::Checked) {
            safety->runSelfTest(false);
        } else {
            safety->runSelfTest(true);
        }
    }

    // DO SELF TEST CHECK THEN BEGIN PROPER OPERATION
    if (mainCount == 5) {
        if (safety->getFailed()) {
            currentPrompt = Voice(UNIT_FAILED);
            mainCount = 95;

            ui->pass_label->setVisible(false);
            ui->failed_label->setVisible(true);
            ui->disabled_pass->setVisible(true);
            ui->disabled_failed->setVisible(false);
        } else {
            currentPrompt = Voice(UNIT_OK);
            statusIndicator();
        }
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
        currentPrompt = Voice(CHECK_PADS);
    }

    if (mainCount == 35) {
        currentPrompt = Voice(DONT_TOUCH);
        op->setFirstAnalysisComplete();
    }

    // DETERMINE IF SHOCK ADVISED
    if (mainCount == 40) {
        sim->pickTest(ui->rhythmcomboBox->currentIndex() + 1); // regardless of whether the shock was successful, if the victim is vfib'n again right after a successful one it needs to be caught

        if (batteryHealth < 35) {
            currentPrompt = Voice(CHANGE_BATTERIES);
        }

        int simSuccess = sim->getSimulation();

        if (simSuccess == 1) {
            nothingHappens++;
        } else {
            nothingHappens = 0;
        }

        if (nothingHappens == 5 || op->getCprCount() == 5 || op->getShockCount() == 5) {
            // normal 5 straight times/too many cpr/shocks: skip to ambulance arrives
            mainCount = 90;
        } else if (simSuccess == 4) {
            // cpr: skip to cpr
            currentPrompt = Voice(NO_SHOCK_ADVISED);
            mainCount = 55;
        } else if (simSuccess == 2 || simSuccess == 3) {
            // shock: deliver shock

            if (afterShock == true) {
                currentPrompt = Voice(START_CPR);
                afterShock = false;
                mainCount = 55;
            } else {

                currentPrompt = Voice(SHOCK_ADVISED);
                afterShock = true;

            }

        }
    }

    if (mainCount == 41 && sim->getSimulation() == 1) {
        mainCount = 33; // back to analyze
        currentPrompt = Voice(NORMAL_RHYTHM);
    }

    if (mainCount == 42) {
        heartButtonLight(true);
    }

    // DO SHOCKING AFTER 5 SECONDS
    if (mainCount == 45) {
        currentPrompt = Voice(SHOCK_DELIVERED);
        op->shock();
        batteryHealth = batteryHealth - 20;
        op->successOfShock(); //performs op->setSuccess(true);

        if (op->getSuccess()) { // switch back to unknown rhythm because shock was successful & we don't want go straight ambulance
            ui->rhythmcomboBox->setCurrentText("Unknown");
            sim->pickTest(4);
            changeRhythm(1);
        }

        if (batteryHealth < 40) {
            currentPrompt = Voice(CHANGE_BATTERIES);
        }

        heartButtonLight(false);
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


    if (mainCount == 94) {
        currentPrompt = Voice(AMBULANCE_ARRIVES);
    }

    if (mainCount == 95) {
        t->setPoweredOffToTrue(); // so the final 5 second countdown starts here
    }

    if (mainCount == 100) {
        mainTimer->stop();
        powerState = false;
        ui->on_label->setStyleSheet(ui->on_label->styleSheet() + "color: rgb(164, 157, 157);");
        ui->off_label->setStyleSheet(ui->off_label->styleSheet() + "color: rgb(51, 209, 122);");

        lcdDisplay();
        indicatorLights();
        statusIndicator();
        ui->rhythmImage->clear();
        op->reset();
        ui->self_test->show();
    }

    lcdDisplay();
    indicatorLights();

    if (op->firstAnalysisComplete()) {
        changeRhythm(getComboBoxSelection());
    }

    mainCount += 1;
    batteryChange();

    if (batteryHealth < 10 && mainCount < 94) {
        mainCount = 95;
        currentPrompt = Voice(CHANGE_BATTERIES);
    }

    if (batteryHealth <= 0) {
        mainCount = 100;
    }
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
        indicatorLights();
        statusIndicator();
        ui->rhythmImage->clear();
        op->reset();

        t->setPoweredOffToTrue();
        ui->self_test->show();
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

  if (!powerState || !op->firstAnalysisComplete()) {
      ui->rhythmImage->clear();
      return;
  }

   QPixmap normal(":/images/images/normal.png");
   QPixmap vfib(":/images/images/vfib.png");
   QPixmap vtach(":/images/images/vtach.png");
   QPixmap afib(":/images/images/afib.jpeg");
   int width = ui->rhythmImage->width();
   int height = ui->rhythmImage->height();

   if (rhythm == 1) {

       ui->rhythmImage->setPixmap(normal.scaled(width,height));

   } else if (rhythm == 2) {

       ui->rhythmImage->setPixmap(vfib.scaled(width,height));

   } else if (rhythm == 3) {

       ui->rhythmImage->setPixmap(vtach.scaled(width,height));

   } else if (rhythm == 4) {

       ui->rhythmImage->setPixmap(afib.scaled(width,height));

   } else {
       std::random_device rd;
       std::uniform_int_distribution<int> dist(1,4);


       changeRhythm(dist(rd));
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


void MainWindow::on_batteryButton_clicked()
{

    batteryHealth = 100;
    currentPrompt = Voice(NEW_BATTERIES);
}

void MainWindow::batteryChange() {

    if (batteryMinus == true) {
        batteryHealth--;
        batteryMinus = false;
    } else {
        batteryMinus = true;
    }

}
