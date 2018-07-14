#include "shared.h"

//DHCP-based OSC server test code
#include <SLIPEncodedSerial.h>
#include <OSCBundle.h>
#include <OSCData.h>

OSCErrorCode error;

// Liaison série avec l'ESP
SLIPEncodedSerial SLIPSerial(Serial1);

void init_com() {
  SLIPSerial.begin(115200);  //Com série avec l'ESP8266-01 (115200 si neo_to_black et 9600 si bleu)
}

void ValueConfiance(OSCMessage &msg) {
  confiance = msg.getInt(0);
}

void OSCMsgReceive()
{
  OSCBundle bundle;
  int _size;
  while (!SLIPSerial.endofPacket()) {
    if ((_size = SLIPSerial.available()) > 0) {
      while (_size--) {
        bundle.fill(SLIPSerial.read());
      }
      if (!bundle.hasError()) {
        bundle.dispatch("/Confiance/Value", ValueConfiance);
        //bundle.dispatch("/neopixel/R",neopixel_R);
        //bundle.dispatch("/neopixel/G",neopixel_G);
        //bundle.dispatch("/neopixel/B",neopixel_B);
      } else {
        error = bundle.getError();
      }
    }
  }
}


