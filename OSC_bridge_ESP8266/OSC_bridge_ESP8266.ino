// This program converts UDP OSC messages into SLIP Serial OSC messages on the ESP8266 wifi board
// At the moment there is no OSC bundle support, not sure I need it at the moment


#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <SLIPEncodedSerial.h>


int status = WL_IDLE_STATUS;
const char* ssid = "sniperAProbot";  //  your network name (SSID)
const char* pass = "razorshark";       // your network password

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

int localPort = 8888;

IPAddress outIp(192, 168, 10, 159); //default IP, will change with received udp
IPAddress espip(192, 168, 10, 22);
IPAddress gateway(192, 168, 10, 233);
IPAddress subnet(255, 255, 255, 0);

SLIPEncodedSerial SLIPSerial(Serial);

void setup()
{
  Serial.println("WIFI a lancer");
  SLIPSerial.begin(115200);
  WiFi.begin(ssid, pass);
  WiFi.config(espip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Udp.begin(localPort);
}

void loop() {
  // read=udp->serial
  int rd;
  OSCBundle rMsg;
  static unsigned long  tr = 0;

  if ((rd = Udp.parsePacket()) > 0) {
    if (tr - micros() > 10000)
    {
      outIp = Udp.remoteIP();
      while (rd--)
        rMsg.fill(Udp.read());
      if (!rMsg.hasError())
      {
        SLIPSerial.beginPacket();
        rMsg.send(SLIPSerial);
        SLIPSerial.endPacket();
      }
      rMsg.empty();
    }
    else
    {
      while (rd--)
        Udp.read();
    }
    tr = micros();
  }
}
