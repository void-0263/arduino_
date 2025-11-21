// ---------------------------------------------
// Project: Button Controlled LED with Pulldown Resistor
// Goal: Each time you press the button, the LED blinks
//       as many times as the number of presses so far.
//
// Hardware connections:
//   - LED connected to digital pin 8 (through 220Ω resistor to GND)
//   - Button connected to digital pin 9 (with 10kΩ pulldown resistor to GND)
// ---------------------------------------------

// Step 1: Define which pins are used
const int led = 8;      // Pin for LED
const int button = 9;   // Pin for Button

// Step 2: Create variables to keep track of button presses and state
int count = 0;          // Counts how many times button was pressed
int button_state = LOW;   // Remembers the last button state (HIGH or LOW)
unsigned long debounce_time = 0;  // Time when the button state last changed
unsigned long debounce_delay = 50;    // Delay (ms) to filter out noise when pressing button

// ---------------------------------------------
void setup() {
  // Step 3: Tell Arduino what each pin does
  pinMode(led, OUTPUT);     // LED will be controlled by Arduino
  pinMode(button, INPUT);
  Serial.begin(9600);   // Button is read as an input (uses pulldown resistor)
  
}
// ---------------------------------------------
void loop() {
  // Step 5: Read the button’s current state (HIGH if pressed, LOW if not)
  int reading = digitalRead(button);

  // Step 6: Debounce logic
  // If the reading has changed since last time, reset the timer
  if (reading != button_state) {
    debounce_time = millis();  // Record the time of this change
  }

  // Step 7: Check if enough time has passed to confirm the button press
  if ((millis() - debounce_time) > debounce_delay) {
    // Step 8: We’ll detect the moment the button changes from LOW to HIGH
    static int buttonPrev = LOW; // Remember previous stable state

    if (reading == HIGH && buttonPrev == LOW) {
      // Button was just pressed!
      count++;               // Increase the count
      blinkLED(count);       // Blink LED as many times as count
    }

    // Update the previous button state
    buttonPrev = reading;
  }

  // Step 9: Save current reading for next loop
  button_state = reading;
}
// ---------------------------------------------
void blinkLED(int n) {
  // This function makes the LED blink "n" times
  // It uses a for loop to repeat the ON/OFF pattern n times
  // (count) is the n used here!!!
  for (int i = 0; i < n; i++) {
    digitalWrite(led, HIGH);
    Serial.println("led on");  // Turn LED ON
    delay(300);                   // Wait 200 milliseconds
    digitalWrite(led, LOW);
    Serial.println("led off");   // Turn LED OFF
    delay(300);                   // Wait again before next blink
  }

  // Small pause before the next button press is detected
  delay(500);
}
// ---------------------------------------------
