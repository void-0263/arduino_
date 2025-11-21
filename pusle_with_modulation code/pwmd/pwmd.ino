int ledPin = 9;  // Use pin 9 for PWM output

void setup() {
  // Initialize the digital pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Fade in from 0 to 255 brightness
  for (int ledVal = 0; ledVal <= 255; ledVal += 1) {
    analogWrite(ledPin, ledVal);
    delay(15); // controls fade speed
  }

  // Fade out from 255 to 0 brightness
  for (int ledVal = 255; ledVal >= 0; ledVal -= 1) {
    analogWrite(ledPin, ledVal);
    delay(15);
  }
  delay (1000);
}
