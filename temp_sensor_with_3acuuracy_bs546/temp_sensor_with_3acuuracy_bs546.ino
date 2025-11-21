int sensorPin = A1;         // Analog pin connected to transistor base
float volt, temp;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);
  Serial.begin(9600);       // Start serial monitor at 9600 baud
}

void loop() {
  int adc = analogRead(sensorPin);          // Read analog volt
  volt = (adc * 5.0) / 1023.0;          // Convert ADC  to volts
  temp = (0.7 - volt) / 0.002;        // Convert V_BE drop to temp in °C

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  delay(500);                                   // Wait 1 second before next reading
}