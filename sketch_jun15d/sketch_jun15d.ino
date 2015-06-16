#include <SoftwareSerial.h>

//#define "Samba2-2.4G" "Samba2-2.4G"  //name of wireless access point to connect to
//#define "" ""  //wifi ""word
#define DST_IP "146.227.57.195" //my web site, replace with yours

#define LED 13
#define RESET 12

SoftwareSerial wifi(10, 11);
int loops = 0;  //a counter for testing

void setup()  //initialise device & connect to access point in setup
{
  pinMode(RESET,OUTPUT);
  reset();

  pinMode(LED,OUTPUT);
  wifi.begin(9600);    // hardware serial connects to esp8266 module
  Serial.begin(9600); // usb serial connects to to pc
  delay(4000);    //wait for usb serial enumeration on 'Serial' & device startup
  if(!cwmode3()) Serial.println("cwmode3 failed");
  boolean wifi_connected=false;  //not connected yet...
  for(int i=0;i<5;i++)    //attempt 5 times to connect to wifi - this is a good idea
  {
    if(connectWiFi())  //are we connected?
    {
      wifi_connected = true;  //yes
      break;              //get outta here!
    }
  }
  if (!wifi_connected) hang("wifi not connected");  //these seem ok - never had a problem
  delay(250);    
  if(!cipmux0()) hang("cipmux0 failed");
  delay(250);
  if(!cipmode0()) hang("cipmode0 failed");
  delay(250);
}

void loop()
{
  reset();  //only CERTAIN way I've found of keeping it going
  delay(5000);  //esp takes a while to restart
 // Serial.print("loops = ");  //check for successful connections to server
  //Serial.println(loops); 
  loops++;
  String cmd = "AT+CIPSTART=\"TCP\",\"";  //make this command: AT+CPISTART="TCP","146.227.57.195",80
  cmd += DST_IP;
  cmd += "\",80";

  wifi.println(cmd);  //send command to device

  delay(2000);  //wait a little while for 'Linked' response - this makes a difference
  if(wifi.find("Linked"))  //message returned when connection established WEAK SPOT!! DOESN'T ALWAYS CONNECT
  {
   // Serial.print("Connected to server at ");  //debug message
   // Serial.println(DST_IP);
  }
  else
  {
  //  Serial.println("'Linked' response not received");  //weak spot! Need to recover elegantly
  }

  cmd =  "GET /~sexton/test.txt HTTP/1.0\r\n";  //construct http GET request
  cmd += "Host: cse.dmu.ac.uk\r\n\r\n";        //test file on my web
  wifi.print("AT+CIPSEND=");                //www.cse.dmu.ac.uk/~sexton/test.txt
  wifi.println(cmd.length());  //esp8266 needs to know message length of incoming message - .length provides this

  if(wifi.find(">"))    //prompt offered by esp8266
  {
   // Serial.println("found > prompt - issuing GET request");  //a debug message
    wifi.println(cmd);  //this is our http GET request
  }
  else
  {
    wifi.println("AT+CIPCLOSE");  //doesn't seem to work here?
    Serial.println("No '>' prompt received after AT+CPISEND");
  }

  //Parse the returned header & web page. Looking for 'Date' line in header

  if (wifi.find("Date: ")) //get the date line from the http header (for example)
  {
    for (int i=0;i<31;i++)  //this should capture the 'Date: ' line from the header
    {
      if (wifi.available())  //new cahracters received?
      {
        char c=wifi.read();  //print to console
        Serial.write(c);
      }
      else i--;  //if not, keep going round loop until we've got all the characters
    }
  }

  wifi.println("AT+CIPCLOSE");  

  if(wifi.find("Unlink"))  //rarely seems to find Unlink? :(
  {
    Serial.println("Connection Closed Ok...");
  }
  else
  {
    //Serial.println("connection close failure");
  }
}
//------------------------------------------------------------------------------------
boolean connectWiFi()
{
  String cmd="AT+CWJAP=\"";  //form eg: AT+CWJAP="dynamode","55555555555555555555555555"
  cmd+="Samba2-2.4G";
  cmd+="\",\"";
  cmd+="";
  cmd+="\"";
  wifi.println(cmd);
  delay(5000); //give it time - my access point can be very slow sometimes
  if(wifi.find("OK"))  //healthy response
  {
    Serial.println("Connected to WiFi...");
    return true;
  }
  else
  {
    Serial.println("Not connected to WiFi.");
    return false;
  }
}
//--------------------------------------------------------------------------------  
//ditch this in favour of hardware reset. Done
boolean softwarereset()
{
  wifi.println("AT+RST");
  if (wifi.find("ready"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//--------------------------------------------------------------------------------
void reset()
{
  digitalWrite(RESET,LOW);
  digitalWrite(LED,HIGH);
  delay(100);
  digitalWrite(RESET,HIGH);
  digitalWrite(LED,LOW);
}
//------------------------------------------------------------------------------
boolean cwmode3()
// Odd one. CWMODE=3 means configure the device as access point & station. This function can't fail?

{
  wifi.println("AT+CWMODE=3");
  if (wifi.find("no change"))  //only works if CWMODE was 3 previously
  {
    return true;
  }
  else
  {
    return false;
  }
}
//----------------------------------------------------------------------------------
boolean cipmux0()
{
  wifi.println("AT+CIPMUX=0");
  if (wifi.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//-----------------------------------------------------------------------
boolean cipmode0()
{
  wifi.println("AT+CIPMODE=0");
  if (wifi.find("OK"))
  {
    return true;
  }
  else
  {
    return false;
  }
}
//------------------------------------------------------------------------
void hang(String error_String)    //for debugging
{
  Serial.print("Halted...   ");
  Serial.println(error_String);
  while(1)
  {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
}
//----------------------------------------------------------------------------
void hangreset (String error_String)    //for debugging
{
  Serial.print(error_String);
  Serial.println(" - resetting");
  reset();
}
//#include <SoftwareSerial.h>
//
//SoftwareSerial wifi(10, 11);
//
//void setup()
//{
//  delay(5000);
//  Serial.begin(9600);
//  wifi.begin(9600);
//}
//
//void loop()
//{
//  /* send everything received from the hardware uart to usb serial & vv */
//  if (Serial.available() > 0) {
//    char ch = Serial.read();
//    wifi.print(ch);
//  }
//  if (wifi.available() > 0) {
//    char ch = wifi.read();
//    Serial.print(ch);
//  }
//}
