#include <max6675.h>
#include <Timer.h>

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

Timer t;
int tempControlTimer;
int targetTemp = 10;
  
void setup() {
  Serial.begin(9600);

//  pinMode(thermo_vcc_pin, OUTPUT); 
//  pinMode(thermo_gnd_pin, OUTPUT); 
//  digitalWrite(thermo_vcc_pin, HIGH);
//  digitalWrite(thermo_gnd_pin, LOW);

  tempControlTimer = t.every(5000, TempControl);
}

int temp;

void loop() {
    t.update();
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
