#include "prompt.h"

Prompt::Prompt(){}

QString Prompt::playVoicePrompt(Voice v) {
    switch(v) {
    case UNIT_OK:
        return "Power Up Self Tests successfully passed.";
        break;
    case UNIT_FAILED:
        return "Power Up Self Tests failed. Unit is not usable for victim care.";
        break;
    case CHANGE_BATTERIES:
        return "Low Battery Detected. Replace batteries immediately before victim care.";
        break;
    case STAY_CALM:
        return "Remain Calm.";
        break;
    case CHECK_RESPONSIVENESS:
        return "Check for responsiveness.";
        break;
    case CALL_FOR_HELP:
        return "Call for Help";
        break;
    case OPEN_AIRWAY:
        return "Place victim in the supine position and perform Head Tilt - Chin Lift or Jaw - Thrust maneuver to open victim's airway";
        break;
    case CHECK_BREATHING:
        return "Check for Breathing";
        break;
    case GIVE_TWO_BREATHS:
        return "If victim is not breathing, give two rescue breaths";
        break;
    case PLUG_IN_CABLE:
        return "Connect the proper electrode cable to the AED";
        break;
    case ATTACH_DEFIB:
        return "Attach defibrillation pads to the victim's bare chest";
        break;
    case CHECK_PADS:
        return "Check defibrillation pads. Ensure electrodes are in working condition, good contact is made, and the proper pads are being used.";
        break;
    case ADULT_PADS:
        return "Adult electrode pads have been detected. Defibrillation energy settings have been adjusted accordingly.";
        break;
    case PEDIATRIC_PADS:
        return "Pediatric electrode pads have been detected. Defibrillation energy settings have been adjusted accordingly.";
        break;
    case DONT_TOUCH:
        return "Do not touch the victim, ECG rhythm analysis in progress.";
        break;
    case SHOCK_ADVISED:
        return "Shock Advised";
        break;
    case NO_SHOCK_ADVISED:
        return "No Shock Advised";
        break;
    case KEEP_PATIENT_STILL:
        return "Analysis Halted. Keep patient still.";
        break;
    case CANNOT_DELIVER_SHOCK:
        return "Battery too low to charge shock. Please replace the battery.";
        break;
    case DELIVERING_SHOCK:
        return "Shock will be delivered. Do not touch the patient.";
        break;
    case SHOCK_DELIVERED:
        return "Shock Delivered";
        break;
    case START_CPR:
        return "Begin CPR";
        break;
    case CONTINUE_CPR:
        return "Continue CPR";
        break;
    case PUSH_HARDER:
        return "CPR Compressions need to be harder.";
        break;
    case GOOD_COMPRESSIONS:
        return "Compressions are good.";
        break;
    case STOP_CPR:
        return "Stop CPR. ECG rhythm analysis about to begin.";
        break;
    case IF_NEW_BATTERIES:
        return "Press the Battery Reset Button located in the battery compartment after replacing ALL batteries in the device.";
        break;
    case NON_RESCUE:
        return "Entered diagnostics/data communications mode.";
        break;
    case COMMUNICATIONS:
        return "IrDA Communications has been established.";
        break;
    case AMBULANCE_ARRIVES:
        return "Ambulance has arrived. Leave job to paramedics.";
        break;
    case NORMAL_RHYTHM:
        return "Normal Rhythm detected. Re-analyzing, do not touch the victim.";
        break;
    case NEW_BATTERIES:
        return "Batteries have been replaced. Charge is at 100%.";
        break;
    case OFF:
        return "";
        break;
    }
}
