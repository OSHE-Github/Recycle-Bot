#include <max6675.h>


// ThermoCouple
int thermo_so_pin  = 50;
int thermo_cs_pin  = 53;
int thermo2_cs_pin  = 49;
int thermo_sck_pin = 52;
const int HEATER_RELAY_PIN = 9;
  
MAX6675 thermocoupleback(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);
MAX6675 thermocouplefront(thermo_sck_pin, thermo2_cs_pin, thermo_so_pin);
  
void setup() {
  pinMode(HEATER_RELAY_PIN, OUTPUT);
  digitalWrite(HEATER_RELAY_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Temp back: ");
  Serial.println(thermocoupleback.readCelsius());
  TempControl(1);
  delay(2500);
  Serial.print("Temp front: ");
  Serial.println(thermocouplefront.readCelsius());
  TempControl(1);
  delay(2500);

}

const int targetTemp = 200;
int temp;
bool heaterStatus;

void TempControl(int heater){
  switch (heater) {
  case 0:
    temp = thermocoupleback.readCelsius();    
    break;
  case 1:
    temp = thermocouplefront.readCelsius();
    break;
}

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
