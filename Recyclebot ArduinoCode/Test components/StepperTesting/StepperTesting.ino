#include <Event.h>
#include <Timer.h>

#include <AccelStepper.h>

//USE X-axis

#define AUGER_STEP_PIN A0
#define AUGER_DIR_PIN A1
#define AUGER_ENABLE_PIN 38

AccelStepper auger(1, AUGER_STEP_PIN, AUGER_DIR_PIN);
Timer t;

void setup() {
  auger.setMaxSpeed(1000);  //set max speed
  auger.setAcceleration(500); //acceleration of 500 steps per second MAY NOT NEED
  //auger set up
  pinMode(AUGER_ENABLE_PIN, OUTPUT);
  pinMode(AUGER_STEP_PIN, OUTPUT);
  pinMode(AUGER_DIR_PIN, OUTPUT);

  digitalWrite(AUGER_ENABLE_PIN, HIGH);
  digitalWrite(AUGER_STEP_PIN, LOW);
  digitalWrite(AUGER_DIR_PIN, HIGH);

  pinMode(LED_BUILTIN , OUTPUT);

  auger.setSpeed(RPMToSteps(60));
  t.every(1000, Blink);
}

void loop() {
  auger.runSpeed();
  t.update();
}

int RPMToSteps(int rpm)
{
  return (200 * rpm) / 60;
}

void Blink()
{
  static bool blinkVal = LOW;
  blinkVal = ~blinkVal;
  digitalWrite(LED_BUILTIN , blinkVal);
}
