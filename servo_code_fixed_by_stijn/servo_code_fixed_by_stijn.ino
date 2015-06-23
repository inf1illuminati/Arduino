#include <Servo.h>
#define BaudRate 9600
#define LEDPin 13

char incomingOption;
long previousMillis = 0;
long interval = 100;

//Servo aServo;
//Servo bServo;
//Servo cServo;
//Servo dServo;
//Servo eServo;
//Servo fServo;
//Servo gServo;
//Servo hServo;

Servo servos[8];

int pos[] = {0, 0, 0, 0, 0, 0, 0, 100};
bool richting[] = {0, 0, 0, 0, 0};
int selectedServo = 0;
bool closeGrip = 0;
bool richtingVoet = 0;
bool on = 0;
bool voetOn = 0;
bool servoSelected = 0;

void moveServo(int servo, int pos) {
  servos[servo].write(pos);
}

void setup() {
  servos[5].attach(2, 800, 2100); //base1
  servos[6].attach(3, 800, 2100); //base2
  servos[0].attach(4, 500, 2500); //high torque
  servos[1].attach(5, 800, 2100); //standard arm
  servos[2].attach(6, 500, 2400); //micro 1
  servos[3].attach(7, 400, 2400); //micro metal
  servos[4].attach(8, 500, 2400); //micro 2
  servos[7].attach(9, 400, 2400); //micro gripper
  pinMode(LEDPin, OUTPUT);
  //myservo.attach(11, 605, 2320);
  //myservo.attach(11, 500, 2400);
  Serial.begin(BaudRate);
  //myservo.write(0);
}

void loop() {
  //Serial.println('0');
  incomingOption = Serial.read();
  switch (incomingOption) {
    case '1': //stop
      on = 0;
      voetOn = 0;
      break;
    case '2': //richting 180
      on = 1;
      richting[selectedServo] = 1;
      break;
    case '3': //richting 0
      on = 1;
      richting[selectedServo] = 0;
      break;
    case 'a': //high torque servo
      selectedServo = 0;
      servoSelected = 1;
      
      break;
    case 'b': //één na onderste servo
      selectedServo = 1;
      servoSelected = 1;
      break;
    case 'c': //eerste micro servo
      selectedServo = 2;
      servoSelected = 1;
      break;
    case 'd': //eerste metalen micro servo
      selectedServo = 3;
      servoSelected = 1;
      break;
    case 'e': //tweede micro servo
      selectedServo = 4;
      servoSelected = 1;
      break;
    case 'h': //grijper (tweede metalen micro servo)
      if (closeGrip) {
        closeGrip = 0;
        if ((unsigned long)(millis() - previousMillis) >= interval) {
          previousMillis = millis();
          servos[7].write(140);;
        }
      } else {
        closeGrip = 1;
        if ((unsigned long)(millis() - previousMillis) >= interval) {
          previousMillis = millis();
          servos[7].write(100);;
        }
//        servos[7].write(120);
//        delay(500);
      }
      servoSelected = 0;
      break;
    case 'f': //voet richting 120 (twee servo's)
      richtingVoet = 1;
      on = 1;
      voetOn = 1;
      servoSelected = 0;
      break;
    case 'g': //voet richting 0 (twee servo's)
      richtingVoet = 0;
      on = 1;
      voetOn = 1;
      servoSelected = 0;
      break;
    default:
      break;
  }
  if (on && servoSelected) {
    if (richting[selectedServo]) {
      if ((pos[selectedServo] <= 180 && selectedServo != 1) || (pos[selectedServo] <= 120 && selectedServo == 1)) {
        moveServo(selectedServo, pos[selectedServo]);
        pos[selectedServo]++;
        delay(15);
      }
    } else {
      if (pos[selectedServo] >= 0) {
        moveServo(selectedServo, pos[selectedServo]);
        pos[selectedServo]--;
        delay(15);
      }
    }
  } else if (on && !servoSelected) {
    if (voetOn) {
      if (richtingVoet) {
        if (pos[5] <= 180) {
          pos[5]++;
          moveServo(5, pos[5]);
        }
        if (pos[6] <= 180) {
          pos[6]++;
          moveServo(6, pos[6]);
        }
        delay(15);
      } else {
        if (pos[5] >= 0) {
          pos[5]--;
          moveServo(5, pos[5]);
        }
        if (pos[6] >= 0) {
          pos[6]--;
          moveServo(6, pos[6]);
        }
        delay(15);
      }
    }
    //    } else if (closeGrip) {
    //      if (pos[7] < 180) {
    //        moveServo(7, pos[7]);
    //        pos[7]++;
    //      }
    //    } else if(pos[7] > 0) {
    //      moveServo(7, pos[7]);
    //      pos[7]--;
    //    }
  }
}

