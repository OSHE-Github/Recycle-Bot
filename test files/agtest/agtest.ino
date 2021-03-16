#include "AccelStepper.h"

#define X_STEP_PIN 46
#define X_DIR_PIN 48
#define X_ENABLE_PIN 62
//todo: add heater elements
//add final 2 steppers on e0 and e1
// replace stepper library with own code
// get heating element working
//let user code in settings and also test stuff to make presets
//the final is to write software for the lcd screen that lets you control all the motor speeds, temps, and has material presets
//also gives you info on temp on screen (and says, preheating and shit like that. Bascially like marlin interface but for the recyclebot)

AccelStepper stepper(1, X_STEP_PIN, X_DIR_PIN); // 1 = Driver

void setup() {
stepper.setMaxSpeed(200);
//stepper.setAcceleration(50);
stepper.setSpeed(200);

stepper.setEnablePin(X_ENABLE_PIN);
stepper.setPinsInverted(false, false, true); //invert logic of enable pin
stepper.enableOutputs();
}

void loop() {
stepper.runSpeed();
 // stepper.runSpeed();
//stepper.runToNewPosition(0);
//
//stepper.moveTo(500);
//while (stepper.currentPosition() != 300)
//stepper.run();
//
//// cause an overshoot as we whiz past 300
////stepper.setCurrentPosition(600);
}
