// ----------------------------------------------------------
// Project: LED & Button with LCD (I2C Module)
// Goal: Each button press makes LED blink one more time.
//       LCD displays LED ON/OFF status using I2C interface.
// ----------------------------------------------------------

#include <Wire.h>               // Enables I2C communication
#include <LiquidCrystal_I2C.h>  // Library for I2C LCD

// Step 1: Initialize LCD
// 0x27 or 0x3F are the common I2C addresses.
// If display doesn't show text, try changing 0x27 -> 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2); // (address, columns, rows)

// Step 2: Define LED and Button pins
const int pin = 8;
const int button = 9;

// Step 3: Variables to track button state
int count = 0;
int button_state = LOW;
unsigned long debounce_time = 0;
unsigned long debounce_delay = 50;

// ----------------------------------------------------------
void setup() {
  pinMode(pin, OUTPUT);
  pinMode(button, INPUT); // Pulldown resistor connected to GND

  // Step 4: Initialize LCD
  lcd.init();        // Start the LCD
  lcd.backlight();   // Turn on LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("DONE BY..");
  delay(1000);
  lcd.clear();
  lcd.setCursor(8, 1);
  lcd.print("Sharvesh");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("N_time_LED_BLINK");
  delay(1000);
  lcd.clear();
  lcd.print("System Ready");
  delay(5000);
  lcd.clear();
  lcd.print("Press button...");
}
// ----------------------------------------------------------
void loop() 
{
  int reading = digitalRead(button);

  // Step 5: Debounce logic
  if (reading != button_state) {
    debounce_time = millis();
  }

  if ((millis() - debounce_time) > debounce_delay) 
  {
    static int buttonPrev = LOW;

    if (reading == HIGH && buttonPrev == LOW) 
    {
      count++;
      blinkLED(count);
    }

    buttonPrev = reading;
  }

  button_state = reading;
}
// ----------------------------------------------------------
// Function: blinkLED
// Makes LED blink 'n' times and updates LCD
void blinkLED(int n) 
{
  for (int i = 0; i < n; i++) 
  {
    digitalWrite(pin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LED is ON ");
    lcd.setCursor(0, 1);
    lcd.print("Blink: ");
    lcd.print(i + 1);
    delay(1000);

    digitalWrite(pin, LOW);
    lcd.setCursor(0, 0);
    lcd.print("LED is OFF ");
    delay(1000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press again...");
  delay(1000);
}
// ----------------------------------------------------------
