#include <DHT.h>
#define Type DHT11
#include <LiquidCrystal.h>

// DHT11 Variables
int tempPin = 2;
DHT HT(tempPin, Type);

float humidity;
float tempC;
float tempF;

// LCD Variables
int rsPin = 7;
int enPin = 8;
int d4Pin = 9;
int d5Pin = 10;
int d6Pin = 11;
int d7Pin = 12;

LiquidCrystal lcd(rsPin, enPin, d4Pin, d5Pin, d6Pin, d7Pin);

// Other variables:
int prepTime = 500;
int delayTime = 100;

int buttonPin = A0;
int buttonNew;
int buttonOld = 1;

int tempMode = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  HT.begin();
  delay(prepTime);
  Serial.println("< All set up! >");
  lcd.clear();
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = HT.readHumidity();
  tempC = HT.readTemperature();
  tempF = HT.readTemperature(true);

  Serial.print("| Humidity: ");
  Serial.print(humidity);
  Serial.print("| | Temperature (C): ");
  Serial.print(tempC);
  Serial.print("| | Temperature (F): ");
  Serial.println(tempF);

  // LCD Code
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  buttonNew = digitalRead(buttonPin);
  if (buttonNew == 1 && buttonOld == 0) {
    tempMode = tempMode * -1;
  }
  if (tempMode == 1) {
    lcd.print(tempC);
    lcd.print((char)223); // This is the degrees symbol
    lcd.print("C  "); // Extra spaces after "C" in case amount of digits changes and leaves behind something
  }
  else {
    lcd.print(tempF);
    lcd.print((char)223); // This is the degrees symbol
    lcd.print("F  "); // Extra spaces after "F" in case amount of digits changes and leaves behind something
  }

  buttonOld = buttonNew;
  delay(delayTime);
}
