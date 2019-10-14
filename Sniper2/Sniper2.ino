#include "shared.h"
#include "motor.h"
#include "sensors.h"
#include "communication.h"
#include "leds.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Encoder.h>

/*******************DEFINE*******************/



void setup() {
  // USB serial
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);
  
  
  pinMode(pin_led_debug, OUTPUT);
  init_gpio_motor();
  init_sensors();
  init_neo_pixel();
  init_com(); //Com série avec l'ESP8266-01 (115200 si neo_to_black et 9600 si bleu)

  #ifdef DISABLE_LOGGING
  Serial.println("Logging disabled");
  #endif

}

/*******************MAIN CODE*******************/

void loop() {
  OSCMsgReceive();
  delay(100);
}
