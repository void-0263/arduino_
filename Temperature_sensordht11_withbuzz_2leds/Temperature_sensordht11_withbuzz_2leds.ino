#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define GREEN_LED 8
#define RED_LED 9
#define BUZZER 10

float tempThreshold = 30.0; 
float humThreshold = 70.0;  

unsigned long previousMillis = 0; 
const long blinkInterval = 300;   
bool redLedState = LOW;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.init();
  lcd.backlight();
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Temp & Humidity");
  lcd.setCursor(0, 1);
  lcd.print("Monitor System");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DONE BY >");
  lcd.setCursor(0, 1);
  lcd.print("SHARVESH - ACT ");
  delay(2000);
  lcd.clear();
}

void loop() 
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  
  if (isnan(t) || isnan(h)) 
  {
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!   "); 
    lcd.setCursor(0, 1);
    lcd.print("Retrying...    ");
    delay(1000); 
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223); // char223 - rep degree sym.
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Humd: ");
  lcd.print(h);
  lcd.print("%   ");

  unsigned long currentMillis = millis();

  
  if (t > tempThreshold || h > humThreshold) 
  {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);

    
    if (currentMillis - previousMillis >= blinkInterval) 
    {
      previousMillis = currentMillis;
      redLedState = !redLedState;
      digitalWrite(RED_LED, redLedState);
    }

  } else 
  {
    
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW);
  }
}
