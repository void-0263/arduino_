#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


const int trigPin = 9;
const int echoPin = 10;
const int redLed = 5;
const int greenLed = 6;
const int threshold = 25; 

Servo myservo;


bool isOpen = false;


void smoothOpen() {
  for (int pos = 90; pos >= 0; pos--) {
    myservo.write(pos);
    delay(5);
  }
}

void smoothClose() {
  for (int pos = 0; pos <= 90; pos++) {
    myservo.write(pos);
    delay(5);
  }
}


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  myservo.attach(3); 
  myservo.write(90);
  digitalWrite(greenLed, HIGH);

  Serial.begin(9600); 

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Done_by_Sharvesh");
  delay(1000);
  lcd.clear();
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long distance = getDistance();

  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < threshold) {

    if (!isOpen) {   
      smoothOpen();
      isOpen = true;

      // LEDs
      digitalWrite(redLed, HIGH);
      digitalWrite(greenLed, LOW);

      // LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Plate Opened");
      lcd.setCursor(0, 1);
      lcd.print("Garbage Found");

      delay(1000);  
    }
  }

  else {
    if (isOpen) {  
      
      smoothClose();
      isOpen = false;

      
      digitalWrite(greenLed, HIGH);
      digitalWrite(redLed, LOW);

      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No Garbage");
      lcd.setCursor(0, 1);
      lcd.print("Nearby");
    }
  }

  delay(100);  
}
