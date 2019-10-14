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

void ValueSellUp(OSCMessage &msg) {
  omega += msg.getInt(0)*10;
  if(omega>150){
    omega=150;
  }
  if(omega<0){
    omega=0;
  }
  order = 1;
  Serial.println(omega);
}

void ValueSellDown(OSCMessage &msg) {
  omega -= msg.getInt(0)*10;
  if(omega>150){
    omega=150;
  }
  if(omega<0){
    omega=0;
  }
  order = 1;
  Serial.println(omega);
}

void ValueHoldUp(OSCMessage &msg) {
  omega += msg.getInt(0)*10;
  if(omega>150){
    omega=150;
  }
  if(omega<0){
    omega=0;
  }
  order = 0;
  Serial.println(omega);
}

void ValueHoldDown(OSCMessage &msg) {
  omega -= msg.getInt(0)*10;
  if(omega>150){
    omega=150;
  }
  if(omega<0){
    omega=0;
  }
  order = 0;
  Serial.println(omega);
}

void ValueBuyUp(OSCMessage &msg) {
  omega += msg.getInt(0)*10;
  if(omega>150){
    omega=150;
  }
  if(omega<0){
    omega=0;
  }
  order = 2;
  Serial.println(omega);
}

void ValueBuyDown(OSCMessage &msg) {
  omega -= msg.getInt(0)*10;
  if(omega>150){
    omega=150;
  }
  if(omega<0){
    omega=0;
  }
  order = 2;
  Serial.println(omega);
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
        bundle.dispatch("/ROBOT_6/CONF", ValueConfiance);
        bundle.dispatch("/ROBOT_6/SELL_DOWN", ValueSellDown);
        bundle.dispatch("/ROBOT_6/SELL_UP", ValueSellUp);
        bundle.dispatch("/ROBOT_6/BUY_DOWN", ValueBuyDown);
        bundle.dispatch("/ROBOT_6/BUY_UP", ValueBuyUp);
        bundle.dispatch("/ROBOT_6/HOLD_DOWN", ValueHoldDown);
        bundle.dispatch("/ROBOT_6/HOLD_UP", ValueHoldUp);
      } else {
        error = bundle.getError();
      }
    }
  }
}
