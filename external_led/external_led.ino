int pin = 8;
int pin_1 =9;
int pin_2 =10;
int ar[] = { pin, pin_1, pin_2}, i;



void setup() {
  // we're gonna use for loop to minimize the memory consumption.
  for ( i = 0; i < 3; i++)
  {
    pinMode(ar[i], OUTPUT);
  }
  Serial.begin(9600);

}

void loop() 
{
  for ( i=0; i<3; i++)
  {
    digitalWrite(ar[i], HIGH);
    Serial.println("LED IS ON");
    delay(1000);

    digitalWrite(ar[i], LOW);
    Serial.println("LED IS OFF");
    delay(1000);
  }
  

}
