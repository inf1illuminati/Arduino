#include <Servo.h>

Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;

int state;

int servo2stand = 90;
int servo3stand = 90;
int servo4stand = 90;
int servo5stand = 90;
int servo6stand = 60;
int servo7stand = 60;
int servo8stand = 60;
int servo9stand = 90;

void setup() {

  servo2.attach(2, 500, 2400); //mini servo
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6, 800, 2100); //normale servo
  servo7.attach(7);
  servo8.attach(8);
  servo9.attach(9, 750, 2250); //thijs servo
  
  servo2.write(90);
  delay(1000);
  servo3.write(90);
  delay(1000);
  servo4.write(90);
  delay(1000);
  servo5.write(90);
  delay(1000);
  servo6.write(60);
  delay(1000);
  servo7.write(60);
  delay(1000);
  servo8.write(60);
  delay(1000);
  servo9.write(90);
  delay(1000);
  

  Serial.begin(9600);
}

String motornumber(int motornummer, int pos) {
  if (motornummer == 1) return "servo2.write(pos);";
}

void heen (int motor, int pos1)
{
  if (motor = 1) {
    if (pos1 > servo2stand){
      int pos = servo2stand;
      servo2stand = pos1;
      for (pos1 < pos; pos1 += 1)
      {
        servo2.write(pos1);
        delay(15);
        Serial.println("allah snackbar boven");        
      }
    }
    else if (pos1 < servo2stand)
    {
      int pos = servo2stand;
      servo2stand = pos1;
      for (pos1 >= pos; pos -= 1)
      {
        servo2.write(pos1);
        delay(15);
        Serial.println("allah snackbar onder");
      }
    }
    else 
    {
      Serial.println("allah snackbar");
    }
  }
  else if (motor = 2)  {
    servo3.write(pos1);
  }
  else if (motor = 3) {
    servo4.write(pos1);
  }
  else if (motor = 4) {
    servo5.write(pos1);
  }
  else if (motor = 5) {
    servo6.write(pos1);
  }
  else if (motor = 6) {
    servo7.write(pos1);
  }
  else if (motor = 7) {
    servo8.write(pos1);
  }
  else if (motor = 8) {
    servo9.write(pos1);
  }


  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  //  servo1.write(150);
  //  delay(1000);
  //  servo1.write(0);
  //  delay(1000);
  //Serial.println(pizza(1));

  if (Serial.available() > 0) {
    state = Serial.read();
    heen(1, state);
    //servo6.write(state);
    //delay(1000);
  }
//  servo6.write(120);
//  delay(1000);
//  servo7.write(0);
//  delay(1000);
  
  //SoftwareServo::refresh()

}
