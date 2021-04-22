#include <max6675.h>
#include <Timer.h>
#include "AccelStepper.h"

//x stepper motors
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38

//z stepper motors
#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

// ThermoCouple
int thermo_so_pin  = 50;
int thermo_cs_pin  = 53;
int thermo2_cs_pin  = 49;
int thermo_sck_pin = 52;
const int HEATER_RELAY_PIN = 9;

//fan 
const int FAN_RELAY_PIN = 10; 

//setup thermo couples and stepper motors
MAX6675 thermocoupleback(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);
MAX6675 thermocouplefront(thermo_sck_pin, thermo2_cs_pin, thermo_so_pin);
AccelStepper stepper(1, X_STEP_PIN, X_DIR_PIN); 
AccelStepper zstepper(1, Z_STEP_PIN, Z_DIR_PIN); 



Timer t;

void setup() {

//setup motor speed
stepper.setMaxSpeed(2000);
stepper.setSpeed(1650);
stepper.setEnablePin(X_ENABLE_PIN);
stepper.setPinsInverted(false, false, true); 
stepper.enableOutputs();


//setup motor speed
zstepper.setMaxSpeed(400);
zstepper.setSpeed(400);
zstepper.setEnablePin(Z_ENABLE_PIN);
zstepper.setPinsInverted(false, false, true); 
zstepper.enableOutputs();

pinMode(HEATER_RELAY_PIN, OUTPUT);
digitalWrite(HEATER_RELAY_PIN, LOW);

Serial.begin(9600);

t.every(5000,TempControl);

digitalWrite(FAN_RELAY_PIN, HIGH);


}
int motor = 0;
void loop() {
  //comment out the next two lines while the robot is getting to temp
  //then when you want the motors to run, uncomment them and reupload it to the robot
  //there is probably a better way to do this, but i didnt have time to get it working and this works for testing
  stepper.runSpeed();
  zstepper.runSpeed();
  
  //update temp control loop
  t.update();
}


//IMPORTANT, SETS THE TARGET TEMP!!!
const int targetTemp = 255;


bool heaterStatus;
int temp;
int tempback;

void TempControl(){
  temp = thermocouplefront.readCelsius();
  tempback = thermocoupleback.readCelsius();
  Serial.print("Temp back: ");
  Serial.println(tempback);
  Serial.print("Temp front: ");
  Serial.println(temp);
  

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
    Serial.println("on");
  }
}


void HeaterOff()
{
  if(heaterStatus != LOW)
  {
    heaterStatus = LOW;
    digitalWrite(HEATER_RELAY_PIN, LOW);
    Serial.println("off");
  }
}
