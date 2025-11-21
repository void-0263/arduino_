int ldr = A0;
int led = 5; // 5 pwm pin so we can smoothen the transition b/w brightness and dimness.

int threshold = 600;   
int brightness = 0;    
int target = 0;        

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(ldr);
  Serial.println(value);

  
  if (value > threshold) {
    target = 255;
  }
  
  else {
    target = 0;
  }

  
  if (brightness < target) {
    brightness++;
  } else if (brightness > target) {
    brightness--;
  }

  analogWrite(led, brightness); 

  delay(5); 
}
