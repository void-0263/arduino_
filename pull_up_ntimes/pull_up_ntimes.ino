const int led = 8;       // LED pin
const int button = 9;    // Button pin

int count = 0;           
int button_state  = HIGH;  
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int prevStable;           // previous stable reading

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);   // internal pull-up resistor
  Serial.begin(9600);
  digitalWrite(led, HIGH);         // LED ON initially

  prevStable = digitalRead(button); // initialize previous stable reading
}

void loop() {
  int reading = digitalRead(button);

  // Debounce logic
  if (reading != button_state) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Detect button press (HIGH → LOW)
    if (reading == LOW && prevStable == HIGH) {
      count++;
      blinkOff(count);
    }

    prevStable = reading;
  }

  button_state = reading;
}

void blinkOff(int n) 
{
  for (int i = 0; i < n; i++) 
  {
    digitalWrite(led, LOW);    // LED OFF
    Serial.println("LED OFF");
    delay(500);
    digitalWrite(led, HIGH);   // LED ON
    Serial.println("LED ON");
    delay(500);
  }

  digitalWrite(led, HIGH);    // ensure LED stays ON
  delay(500);
}

