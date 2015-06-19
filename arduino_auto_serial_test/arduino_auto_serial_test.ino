#include <Servo.h>

#include <SoftwareSerial.h>

Servo servo2; 

bool serialConnected = false;
int led = 13;
int val = 0;

bool test = true;

int pos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  servo2.attach(2);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

String motornumber(int motornummer, int pos){
  if (motornummer == 1) return "servo2.write(pos);";
}

void heen(int motor, int pos1){
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    //String x = motornumber(motor, pos);
    //Serial.println(motornumber(x));
    //x;
    
    motornumber(motor, pos);
    //Serial.write(motornumber(motor, pos));
                  // tell servo to go to position in variable 'pos' 
    delay(5);                       // waits 15ms for the servo to reach the position 
    //Serial.println("heen");
  } 
}

void terug(int motor, int pos1){
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    String y = motornumber(motor, pos);
    y;
        // tell servo to go to position in variable 'pos' 
    delay(5);                       // waits 15ms for the servo to reach the position 
    //Serial.println("terug");
  } 
}

void loop() {
 
  if(Serial.available() > 0)
  {
    val = Serial.read();
    
    Serial.println(val);
    
    if (val == '1')
    {
      if(test == true)
      {
        test = false;
        digitalWrite(led, HIGH);
      } else if (test == false)
      {
        test = true;
        digitalWrite(led, LOW);
      }
    } 
    
    
  }
  // put your main code here, to run repeatedly:
  if(!serialConnected)
  {
    
    Serial.println('0');
    
  }
  
//  terug(2, 180);
//  heen(2, 180);
  
  //int angle = servo1.read();
  //Serial.println(angle);
  //Servo::refresh()
}
