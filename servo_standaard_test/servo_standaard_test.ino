#include <Servo.h>

Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;


void setup() {

  servo2.attach(2, 500, 2400); //mini servo
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6, 800, 2100); //normale servo
  servo7.attach(7);
  servo8.attach(8);
  servo9.attach(9, 750, 2250); //thijs servo

  Serial.begin(9600);
}

String motornumber(int motornummer, int pos) {
  if (motornummer == 1) return "servo2.write(pos);";
}

void heen (int motor, int pos1)
{
  if (motor = 1) servo2.write(pos1);
  else if (motor = 2) servo3.write(pos1);
  else if (motor = 3) servo4.write(pos1);
  else if (motor = 4) servo5.write(pos1);
  else if (motor = 5) servo6.write(pos1);
  else if (motor = 6) servo7.write(pos1);
  else if (motor = 7) servo8.write(pos1);
  else if (motor = 8) servo9.write(pos1);


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
    int state = Serial.read();
//    heen(1, state);
    servo2.write(state);
    delay(1000);
  }
  
  SoftwareServo::refresh()

}
