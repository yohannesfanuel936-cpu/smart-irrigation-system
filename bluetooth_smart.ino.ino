#include <Arduino.h>

char btData;

int ledPin = 7;       // manual LED
int pumpPin = 8;      // pump
int uvPin = 9;        // UV light
int fanPin = 10;      // DC fan
int ldrPin = A0;      // light sensor

int ldrThreshold = 500;  // adjust to your environment

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(uvPin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 1️⃣ LDR controls UV light only
  int lightLevel = analogRead(ldrPin);
  if (lightLevel < ldrThreshold) { 
    digitalWrite(uvPin, HIGH);  // it's dark → UV ON
  } else {
    digitalWrite(uvPin, LOW);   // it's light → UV OFF
  }

  // 2️⃣ Bluetooth controls LED, Pump, and Fan
  if (Serial.available()) {
    btData = Serial.read();

    if (btData == '1') digitalWrite(ledPin, HIGH);
    if (btData == '0') digitalWrite(ledPin, LOW);

    if (btData == 'P') digitalWrite(pumpPin, HIGH);
    if (btData == 'S') digitalWrite(pumpPin, LOW);

    if (btData == 'F') digitalWrite(fanPin, HIGH);
    if (btData == 'G') digitalWrite(fanPin, LOW);
  }
}