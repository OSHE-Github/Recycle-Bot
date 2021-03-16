#include <SPI.h>

double readCelsius(uint8_t cs) {
    uint16_t v;

    digitalWrite(cs, LOW);
    v = SPI.transfer(0x00);
    v <<= 8;
    v |= SPI.transfer(0x00);
    digitalWrite(cs, HIGH);

    if (v & 0x4) {
        // uh oh, no thermocouple attached!
        return NAN; 
    }

    v >>= 3;

    return v*0.25;
}

void setup() {
    SPI.begin();
    pinMode(49, OUTPUT);
    pinMode(52, OUTPUT);
    digitalWrite(49, HIGH);
    digitalWrite(52, HIGH);

    Serial.begin(9600);
}

void loop() {
    Serial.print(readCelsius(49));
    Serial.print(" ");
    Serial.println(readCelsius(52));
    delay(1000);
}
