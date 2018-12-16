/*jjj
This sketch demonstrates how to send data from a Device
to another Device (using the Host as an intermediary)
in a Gazell network.
When Button A on Device0 is pressed and released,
the green led on Device1 will toggle.
*/

#include <RFduinoGZLL.h> // include rfduino library

device_t role = HOST; // set Device name... DEVICE2 to DEVICE7 / HOST

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete
void setup()
{
  pinMode(6,OUTPUT);
   pinMode(5,OUTPUT);
    pinMode(4,OUTPUT);
     pinMode(3,OUTPUT);
  Serial.begin(9600); // begin serial communications
  // start the GZLL stack  
  RFduinoGZLL.begin(role); // begin BLE communications
}

void loop()
{
   if (stringComplete) {
    Serial.println(inputString);
    
    if (inputString.charAt(1)=='a'){
      digitalWrite(6,HIGH);
      }

      if (inputString.charAt(1)=='b'){
      digitalWrite(5,HIGH);
      }

      if (inputString.charAt(1)=='c'){
      digitalWrite(4,HIGH);
      }

      if (inputString.charAt(1)=='d'){
      digitalWrite(3,HIGH);
      }

       if (inputString.charAt(0)=='0'){
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      }
     
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len) // this function receives BLE communications
{

//  if (data[0]==97){ // if first character is a (ascci code 97) then print out the data
  
  Serial.print(device); // print the device name
  Serial.print(","); 
  Serial.print(abs(rssi)); // print distance from device to host
  Serial.print(",");
  Serial.println(data); // print out data
//  Serial.println(",");
//  Serial.println(len); // print out lenght of recived data buffer

  
  
  if (device == DEVICE1)  // if device name is DEVICE1 relay the last known state to DEVICE1
    RFduinoGZLL.sendToDevice(device, "data from host");
//}
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

/*
This sketch demonstrates how to send data from a Device
to a Host in a Gazell network.

The host and upto 3 devices should have the RGB shield
attached.  When Button A on a Device is pressed, the
associated led on the Host will toggle.  Device1 is
associated with the Red led, Device2 with the Green led
and Device3 with the Blue led.

The Green led on the Device will blink to indicate
that an acknowledgement from the Host was received.
*/
//
//#include <RFduinoGZLL.h>
//
//device_t role = HOST;
//
//// pin for the Green Led
//int green_led = 3;
//
//void setup()
//{
//  pinMode(green_led, OUTPUT);
//
//  // start the GZLL stack  
//  RFduinoGZLL.begin(role);
//}
//
//void loop()
//{
//}
//
//void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
//{
//  char state = data[0];
//
//  // this test is not needed for a single device
//  if (device == DEVICE0)
//    digitalWrite(green_led, state);
//
//  // no data to piggyback on the acknowledgement sent back to the Device
//  // RFduinoGZLL.sendToDevice(device, "OK");
//}
