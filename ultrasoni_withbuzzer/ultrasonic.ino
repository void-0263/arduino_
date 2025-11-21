// --- Pin Definitions ---
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 12;
const int buzzerPin = 11;

// --- Distance Thresholds (in cm) ---
const int BUZZER_ALARM_DISTANCE = 10;   // Very close: LED + buzzer
const int LED_WARNING_DISTANCE = 30;   // Warning zone: LED only

// --- Variables ---
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // --- Trigger the ultrasonic pulse ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // --- Read echo and calculate distance ---
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // --- Display distance on Serial Monitor ---
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // --- Control logic for LED and buzzer ---
  if (distance <= BUZZER_ALARM_DISTANCE && distance > 0) {
    // 🚨 Very close — turn on LED and make buzzer beep
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);  // Beep
    delay(100);             // Beep duration
    noTone(buzzerPin);      // Pause
    delay(100);
  } 
  else if (distance <= LED_WARNING_DISTANCE && distance > BUZZER_ALARM_DISTANCE) {
    // ⚠️ In warning zone — only LED ON
    digitalWrite(ledPin, HIGH);
    noTone(buzzerPin);
    delay(200);
  } 
  else {
    // ✅ Safe distance — everything OFF
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(500);
  }
}
