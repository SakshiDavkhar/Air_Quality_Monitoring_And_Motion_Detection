#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MQ135.h>

// Pins
const int PIN_MQ135 = A0;
const int PIN_PIR   = 2;
const int PIN_BUZZER = 12;

LiquidCrystal_I2C lcd(0x27, 16, 2); 
MQ135 gasSensor(PIN_MQ135);

void setup() {
    Serial.begin(9600);
    pinMode(PIN_PIR, INPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Init System...");
}

void loop() {
    float rzero = gasSensor.getRZero(); // For calibration
    float ppm = gasSensor.getPPM();
    int motion = digitalRead(PIN_PIR);

    lcd.setCursor(0, 0);
    lcd.print("PPM: ");
    lcd.print(ppm);

    lcd.setCursor(0, 1);
    lcd.print("Motion: ");
    lcd.print(motion ? "YES" : "NO ");

    // Smart Activation Logic
    if (ppm > 400 && motion == HIGH) {
        digitalWrite(PIN_BUZZER, HIGH);
    } else {
        digitalWrite(PIN_BUZZER, LOW);
    }

    delay(1000);
}