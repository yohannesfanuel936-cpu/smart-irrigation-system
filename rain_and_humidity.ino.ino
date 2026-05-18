#include <LiquidCrystal.h>
#include <DHT.h>

// LCD pins (your exact setup)
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// DHT sensor
#define DHTPIN 6
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Rain sensor
int rainPin = 5;

void setup() {
  lcd.begin(16, 2);
  dht.begin();

  pinMode(rainPin, INPUT);

  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float humidity = dht.readHumidity();
  int rainState = digitalRead(rainPin);

  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  if (rainState == LOW) {
    lcd.print("Rain: YES   ");
  } else {
    lcd.print("Rain: NO    ");
  }

  delay(2000);
}