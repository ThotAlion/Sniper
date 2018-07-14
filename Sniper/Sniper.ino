#include "shared.h"
#include "motor.h"
#include "sensors.h"
#include "communication.h"
#include "leds.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Encoder.h>
#include <TimerOne.h>

/*******************DEFINE*******************/
int cmdL = 0;
int cmdR = 0;
int state = 0;
long t0;
int Speed;

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
  Speed = confiance;
  //Speed = 100;
  if(Sharp.left||Sharp.middle||Sharp.right){
    Speed = Speed/2;
  }
  switch(state){
    case 0:
      cmdL = Speed;
      cmdR = Speed;
      if(Bumper.left||hall_detect){
        t0=millis();
        state = 1;
      }
      if(Bumper.right||hall_detect){
        t0=millis();
        state = 3;
      }
      if(Sharp.left){
        t0=millis();
        state = 4;
      }
      if(Sharp.right){
        t0=millis();
        state = 2;
      }
      break;
    case 1:
      cmdL = -Speed;
      cmdR = -Speed;
      if((millis()-t0)>(100000/Speed)){
        t0=millis();
        state = 2;
      }
      break;
    case 2:
      cmdL = -Speed;
      cmdR = Speed;
      if((millis()-t0)>(25000/Speed)){
        state = 0;
      }
      break;
    case 3:
      cmdL = -Speed;
      cmdR = -Speed;
      if((millis()-t0)>(100000/Speed)){
        t0=millis();
        state = 4;
      }
      break;
    case 4:
      cmdL = Speed;
      cmdR = -Speed;
      if((millis()-t0)>(50000/Speed)){
        state = 0;
      }
      break;
  }
  set_right_motor_speed(cmdR);
  set_left_motor_speed(cmdL);
  // Algo();
  // neo_to_black();
  // Log.notice("...");
  //blynk(confiance);
  
  // delay(500);
  // sunrise();
  // avant();
  // Serial.printf("Encoder %d %d\n", encoder_left.read(), encoder_right.read());
  // Serial.printf("Encoder %d\n", incLEFT);
  // fill_gradient_RGB(neo_leds, NUM_LEDS, CRGB(50,0,200), CRGB(100,300,240));
  delay(100);
}
