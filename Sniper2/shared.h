// Uncomment for production
// #define DISABLE_LOGGING


#ifndef SHARED_H
#define SHARED_H
#include <Arduino.h>
#include <ArduinoLog.h>
#include <TimerOne.h>

// Comment to use digital or or uncomment to use analog sharp
//#define SHARP_ANALOG

// timer en milliseconds de vérif du sharp analogique et de l'effet hall
#define SENSOR_TIMER_MILLISECONDS 300

// Seuil de détection des Sharp analogique. Plus c'est haut, plus c'est proche en distance.
#define ANALOG_SHARP_THRESHOLD 300

// Seuil de détection du capteur à effet hall. Dépend du pole de l'aimant
#define HALL_SENSOR_THRESHOLD 790

// Max led brightness
#define MAX_BRIGHTNESS 255

#define SIZE_ARRAY_SHARP 5


// #define REncoder 2
// #define LEncoder 3

// Teensy 3.2 user led
const uint8_t pin_led_debug = 13;

// Change in OOP
struct sharp_detect {
   bool left;
   bool middle;
   bool right;
 };

struct bumper {
   bool left;
   bool right;
 };

 // struct all_sensors {
 //   struct sharp_detect sharp;
 //   struct bumper bumper;
 //   bool hall;
 // };

extern struct sharp_detect Sharp = {false, false, false} ;
extern struct bumper Bumper = {false, false};
extern bool hall_detect = false;
extern int confiance = 0;
extern float omega = 1;
extern int order = 0; // 0:hold, 1:sell 2: buy

// Pas possible de faire un struct de struct sans passer par des pointeurs
// extern struct all_sensors Sensors = {Sharp, Bumper, false } ;


// simple utility for debuging to blink a led n times during n seconds
void blink(uint8_t pin_led, int number_of_flashs, int total_time_s) {
  bool state = 0;
  for(int i=0; i<number_of_flashs*2; i++) {
    state = !state ;
    digitalWrite(pin_led, state);
    delay((total_time_s * 500)/number_of_flashs);
  }
}


#endif /* SHARED_H */
