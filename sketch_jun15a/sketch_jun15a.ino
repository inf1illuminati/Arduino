#include <SoftwareSerial.h>

//String state = "abc";

SoftwareSerial wifi(10, 11); // RX, TX

void setup() {
  // put your setup code here, to run once:
//  wifi.begin(115200);
  
  Serial.begin(9600);
  wifi.begin(9600);
}

void loop() {
  while(wifi.available()) Serial.write(wifi.read());
  while(Serial.available()) wifi.write(Serial.read());

//  if (wifi.available() > 0){
//    String state = wifi.read();
//    
//    if (state.substring(0) == "IPD"){
//      Serial.write(state);
//    }
//  }
}
