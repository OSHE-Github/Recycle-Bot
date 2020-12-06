//imports
#include <Event.h>
#include <Timer.h>
#include <AccelStepper.h>
#include <max6675.h>
#include <Stepper.h>

//constants

//fans
const int FAN_PIN = 40; // Fan output

//Augermotor
#define AUGER_STEP_PIN A0
#define AUGER_DIR_PIN A1
#define AUGER_ENABLE_PIN  38

AccelStepper auger(1, AUGER_STEP_PIN, AUGER_DIR_PIN);
Timer t;

//Heater control
//USE AUX-3 ON HEADER BOARD

//Heater Relays
#define HEATER_RELAY_PIN 43


// ThermoCouple
//int thermo_gnd_pin = 45;
//int thermo_vcc_pin = 47;
#define THERMO_SO_PIN 50
#define THERMO_CS_PIN 51
#define THERMO_SCK_PIN 52

MAX6675 thermocouple(THERMO_SCK_PIN, THERMO_CS_PIN, THERMO_SO_PIN);

int tempControlTimer;
int targetTemp = 10;

//Cold end motor
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

void setup() {
  // put your setup code here, to run once:
  //fans
  pinMode(FAN_PIN, OUTPUT);


  //Auger motor
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

  //Heater loop
  Serial.begin(9600);

//  pinMode(thermo_vcc_pin, OUTPUT); 
//  pinMode(thermo_gnd_pin, OUTPUT); 
//  digitalWrite(thermo_vcc_pin, HIGH);
//  digitalWrite(thermo_gnd_pin, LOW);

  tempControlTimer = t.every(5000, TempControl);

  //Spooling
  // set the speed at 60 rpm:
  ColdStepper.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}

int temp;

void loop() {
  // put your main code here, to run repeatedly:
  
  //fans
  digitalWrite(FAN_PIN, HIGH); // turn on fans

  //auger motor
  auger.runSpeed();
  t.update();
  
  // step one revolution  in one direction:
  ColdStepper.step(stepsPerRevolution);
  
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


//functions for heater control
bool heaterStatus;
int timeout;

void TempControl()
{
  temp = thermocouple.readCelsius();
  if(temp < targetTemp)
  {
    HeaterOn();
  }
  else
  {
    HeaterOff();
  } 
}

void HeaterOn()
{
  if(heaterStatus != HIGH)
  {
    heaterStatus = HIGH;
    digitalWrite(HEATER_RELAY_PIN, HIGH);
  }
}

void HeaterOff()
{
  if(heaterStatus != LOW)
  {
    heaterStatus = LOW;
    digitalWrite(HEATER_RELAY_PIN, LOW);
  }
}
