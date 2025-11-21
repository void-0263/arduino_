int d8 = 8;
int d9 = 9;


void setup() 
{
   pinMode( d8, OUTPUT);
   pinMode(d9, INPUT);
   Serial.begin(9600);
}


void loop() 
{
 if (digitalRead(d9) == LOW)
 {
  digitalWrite(d8, HIGH);
  Serial.println("led on");
  delay(500);
 }
 else
 {
  digitalWrite(d8, LOW);
  Serial.println("LED off");
 }
 delay(1000);


}


