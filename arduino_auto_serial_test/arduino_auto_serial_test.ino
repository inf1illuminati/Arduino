#include <Servo.h>

#include <SoftwareSerial.h>

Servo servo1; 

bool serialConnected = false;
int led = 13;
int val = 0;

bool test = true;

int pos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  servo1.attach(2);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void heen(){
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(1);                       // waits 15ms for the servo to reach the position 
    Serial.println("heen");
  } 
}

void terug(){
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    servo1.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(1);                       // waits 15ms for the servo to reach the position 
    Serial.println("terug");
  } 
}

void loop() {
 
  if(Serial.available() > 0)
  {
    val = Serial.read();
    
//    if (val == '1')
//    {
//      if(test == true)
//      {
//        test = false;
//        heen();
//      } else if (test == false)
//      {
//        test = true;
//        terug();
//      }
//    } 
    
    
  }
  // put your main code here, to run repeatedly:
  if(!serialConnected)
  {
    
    Serial.println('0');
    
  }
  
  terug();
  heen();
  
  //int angle = servo1.read();
  //Serial.println(angle);
  Servo::refresh()
}
