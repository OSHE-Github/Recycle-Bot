
//Temp Feeback Imports
#include <max6675.h>
#include <Timer.h>

//Motor Control Imports
#include <AccelStepper.h>

//Spooling Imports


//Temp Feedback definitions && Methods **********************************************************************************************************

//Heater Relays
#define HEATER_RELAY_PIN 43


// ThermoCouple
//int thermo_gnd_pin = 45;
//int thermo_vcc_pin = 47;
#define THERMO_SO_PIN 50
#define THERMO_CS_PIN 51
#define THERMO_SCK_PIN 52


MAX6675 thermocouple(THERMO_SCK_PIN, THERMO_CS_PIN, THERMO_SO_PIN);

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

//End Temp Feedback ******************************************************************************************************************************



//Motor Controll definitions && Methods **********************************************************************************************************
#define AUGER_STEP_PIN A0
#define AUGER_DIR_PIN A1
#define AUGER_ENABLE_PIN  38

AccelStepper auger(1, AUGER_STEP_PIN, AUGER_DIR_PIN);



int RPMToSteps(int rpm)
{
  return (200 * rpm) / 60;
}

//End Motor Controll *****************************************************************************************************************************




//Cooling definitions && Methods *****************************************************************************************************************

//Define Fan Pins

#define FAN_PIN 3

//Define Fan speed
unsigned char speed;
unsigned int low = 1;
unsigned int high = 10;
unsigned int baseTime = 10;



//End Cooling ***********************************************************************************************************************************



void setup() {
   Serial.begin(9600);

//  pinMode(thermo_vcc_pin, OUTPUT); 
//  pinMode(thermo_gnd_pin, OUTPUT); 
//  digitalWrite(thermo_vcc_pin, HIGH);
//  digitalWrite(thermo_gnd_pin, LOW);

  tempControlTimer = t.every(5000, TempControl);
  tempControlTimer2 = t2.every(5000, TempControl);
  
  auger.setSpeed(RPMToSteps(60));
  //Fan speed set
  pinMode(FAN_PIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  t.update(); //First heater
  t2.update(); //First heater
  auger.runSpeed(); //Auger
  analogWrite(FAN_PIN, 1023); //this may work

  /*Possible need for fan
  digitalWrite(7,LOW);
  delayMicroseconds(low*10);
  digitalWrite(7,HIGH);
  delayMicroseconds(high*10);

  if (Serial.available())
  {
  speed = Serial.read() - 48;
  low = speed;
  high = baseTime - speed;
  }
   */

}
