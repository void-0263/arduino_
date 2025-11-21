int potValue;   
int ledValue;

void setup() {
  pinMode(A0, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  potValue = analogRead(A0);              
  ledValue = map(potValue, 0, 1023, 0, 255); 

  analogWrite(5, ledValue);               
}

