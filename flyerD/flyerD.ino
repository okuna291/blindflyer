/*
This sketch demonstrates how to coordinate data
between 3 devices in a Gazell network.
The host collects RSSI samples from the Devices,
and determines which device has the strongest
average RSSI (ie: the Device that is closest
to the Host).  The Green led is set on the
closest Device.
Since the Device must initiate communication, the
device "polls" the Host evey 200ms.
*/

#include <RFduinoGZLL.h> // include rfduino library
device_t role = DEVICE1; // set Device name... DEVICE2 to DEVICE7 / HOST

//define pins


int r = 3;
int l = 4;
int u = 5;
int d = 6;

int rval = 0;
int lval = 0;
int uval = 0;
int dval = 0;



void setup()
{
  Serial.begin(9600); // begin serial communications
 
  pinMode(r, INPUT);
  pinMode(l, INPUT);
  pinMode(u, INPUT);
   pinMode(d, INPUT);

  RFduinoGZLL.txPowerLevel = 0;

  // start the GZLL stack
  RFduinoGZLL.begin(role); // begin BLE communications
}

void loop()
{
  char rdata[1];   //declaring character array -- 3 characters plus a nill charachter as terminator
  char ldata[1];
  char udata[1];
  char ddata[1];
  char mydata[4]; // declare mydata array

  String rstr;//declaring string
  String lstr;//declaring string
  String ustr;//declaring string
  String dstr;//declaring string
  String mystr;

  rval = digitalRead(r); // read pin sensor values and place into variavles
  lval = digitalRead(l);
  uval = digitalRead(u);
  dval = digitalRead(d);

  rstr.toCharArray(rdata, 1); //passing the string value of sensors to the character array
  lstr.toCharArray(ldata, 1);
  ustr.toCharArray(udata, 1);
  dstr.toCharArray(ddata, 1);

  mystr = "a," + rstr+"," + lstr+"," + ustr+"," + dstr; // combining data for sending to other rfduino... change "a" to other characters to identify message package

  mystr.toCharArray(mydata, 4); // place mystr data into character buffer

  Serial.println(mystr); // print buffer to serial

 RFduinoGZLL.sendToHost(mydata, 4); // send buffer to host other rfduino
    delay(250);
}

// if data is recived from another rfduino
void RFduinoGZLL_onReceive(device_t device, int rssi, char *data, int len)
{
  // ignore acknowledgement without payload
  if (len > 0)
  {
    // set the Green led if this device is the closest device
    device_t closest_device = (device_t)data[0];
    //digitalWrite(green_led, (role == closest_device));
  }
}
