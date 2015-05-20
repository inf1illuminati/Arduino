#include <SoftwareSerial.h>
bool serialConnected = false;
int led = 13;
int val = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
 
  if(Serial.available() > 0)
  {
    val = Serial.read();
    
    if (val == '1')
    {
      digitalWrite(led, HIGH);
      //serialConnected = true;
      delay(1000);
      digitalWrite(led, LOW);
    } 
    
    
  }
  // put your main code here, to run repeatedly:
  if(!serialConnected)
  {
    
    Serial.println('0');
    
  }


}
