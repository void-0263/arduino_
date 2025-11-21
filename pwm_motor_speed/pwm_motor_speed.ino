int potPin = A0;
int motorPin = 9;

void setup() {
  pinMode(motorPin, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);   // Range: 0–1023
  int speed = map(potValue, 0, 1023, 0, 255);  // Convert to PWM

  analogWrite(motorPin, speed);
}
