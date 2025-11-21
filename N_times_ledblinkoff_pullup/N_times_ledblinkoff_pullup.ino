#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD address (usually 0x27 or 0x3F) and size 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int led = 8;       // LED pin
const int button = 9;    // Button pin

int count = 0;           
int button_state  =  HIGH;  
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int prevStable;           // previous stable reading

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);   // internal pull-up resistor
  Serial.begin(9600);
  digitalWrite(led, HIGH);         // LED ON initially

  prevStable = digitalRead(button); // initialize previous stable reading

  // Initialize I2C LCD
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
  lcd.print("Ntime_LED");
  delay(1000);
  lcd.clear();
  lcd.setCursor(7, 1);
  lcd.print("BLINK_OFF");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(5000);
  lcd.clear();
  lcd.print("Press button...");
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

      // Update LCD with press count
     // clear leftover digits if count > 9

      blinkOffLCD(count);
    }

    prevStable = reading;
  }

  button_state = reading;
}

// Blink LED OFF 'n' times and update LCD
void blinkOffLCD(int n) 
{  // show blinking status

  for (int i = 0; i < n; i++) 
  {
    digitalWrite(led, LOW);    // LED OFF
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LED is OFF ");
    lcd.setCursor(0, 1);
    lcd.print("Blink: ");
    lcd.print(i + 1);
    delay(1000);

    digitalWrite(led, HIGH);  
    lcd.clear(); // LED ON
    lcd.setCursor(0, 0);
    lcd.print("LED is ON ");
    delay(1000);
  }

  digitalWrite(led, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press again...");    
  delay(100);
}
