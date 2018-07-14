#include "shared.h"
#include <Arduino.h>
#define FILTER_SHARP_TAB_SIZE 5

// prototypes
void check_bumper(void);
void check_sensors(void);
void check_digital_sharp(void);
void update_array(int, int *,int *);
int get_average_from_array(int *);


// Sharp IR GP2Y0A41SK0F or GP2D150A
const uint8_t pin_G_sharp = A8;
const uint8_t pin_M_sharp = A7;
const uint8_t pin_D_sharp = A6;

// Bumper
const uint8_t pin_micro_1 = 11;
const uint8_t pin_micro_2 = 10;

// Hall sensor for magnet detection
// nouvelle pin bornier du bas
const uint8_t pin_hall = A5;
volatile int hall_value = 0;

//
// // Filter for analog sharp (TODO)
// extern int tab_G_sharp[FILTER_SHARP_TAB_SIZE];
// extern int tab_M_sharp[FILTER_SHARP_TAB_SIZE];
// extern int tab_D_sharp[FILTER_SHARP_TAB_SIZE];

bool debug_state = 0 ;


void init_sensors() {

  #ifndef SHARP_ANALOG // Digital Sharp
    blink(pin_led_debug, 5, 5);  // DEBUG 5 blinks in 5 seconds
    Serial.println("DIGITAL Sharp mode");
    pinMode(pin_G_sharp, INPUT_PULLUP);
    pinMode(pin_M_sharp, INPUT_PULLUP);
    pinMode(pin_D_sharp, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(pin_G_sharp), check_digital_sharp, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pin_D_sharp), check_digital_sharp, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pin_M_sharp), check_digital_sharp, CHANGE);
  #else // Analogic Sharp
    blink(pin_led_debug, 30, 5);  // DEBUG 15 blinks in 5 seconds
    Serial.println("ANALOG Sharp mode");
  #endif
  // Timer for hall sensor and Sharp if analog
  Timer1.initialize(SENSOR_TIMER_MILLISECONDS * 100); // on check les sharp toutes les 100ms
  Timer1.attachInterrupt(check_sensors);


  // Hall
  pinMode(pin_hall, INPUT);


  // Bumper
  pinMode(pin_micro_1, INPUT_PULLUP);
  pinMode(pin_micro_2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin_micro_1), check_bumper, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pin_micro_2), check_bumper, CHANGE);

}


// dégueu à optimiser
// Sharp GP2Y0A41SK0F
void check_analog_sharp() {

  static int left_sensor_t[SIZE_ARRAY_SHARP];
  static int right_sensor_t[SIZE_ARRAY_SHARP];
  static int middle_sensor_t[SIZE_ARRAY_SHARP];

  static int current_left = 0;
  static int current_right = 0;
  static int current_middle = 0;

  update_array(analogRead(pin_G_sharp), left_sensor_t, &current_left);
  update_array(analogRead(pin_M_sharp), right_sensor_t,&current_right);
  update_array(analogRead(pin_D_sharp), middle_sensor_t,&current_middle);

  Sharp.left = get_average_from_array(left_sensor_t) > ANALOG_SHARP_THRESHOLD ? true : false ;
  Sharp.right = get_average_from_array(right_sensor_t) > ANALOG_SHARP_THRESHOLD ? true : false ;
  Sharp.middle = get_average_from_array(middle_sensor_t) > ANALOG_SHARP_THRESHOLD ? true : false ;

  // Debug
  if (Sharp.left || Sharp.right || Sharp.middle) {
   Log.notice(F("Analog Sharp detected %T %T %T" CR), Sharp.left, Sharp.middle, Sharp.right);
  }
  digitalWrite(pin_led_debug, (Sharp.left || Sharp.right || Sharp.middle));
}

// Sharp GP2D150A
void check_digital_sharp() {
  Sharp.left = digitalRead(pin_G_sharp);
  Sharp.right = digitalRead(pin_D_sharp);
  Sharp.middle = digitalRead(pin_M_sharp);


  // Debug
  if (Sharp.left || Sharp.right || Sharp.middle) {
    Log.notice(F("Digital Sharp detected %T %T %T" CR), Sharp.left, Sharp.middle, Sharp.right);
  }
  digitalWrite(pin_led_debug, (Sharp.left || Sharp.right || Sharp.middle));
}

void check_hall_sensor() {

  hall_value = 0;
  for(int i=0; i<5 ; i++) {
    hall_value += analogRead(pin_hall) ;
  }
  hall_value /= 5;

  hall_detect = hall_value > HALL_SENSOR_THRESHOLD ? true : false ;
  if (hall_detect) {
    Log.notice(F("Hall sensor detected %i" CR), hall_value);
  }
  // digitalWrite(pin_led_debug, hall_detect);

}

// Generic IR detection function
void check_sensors() {

  check_hall_sensor();

  #ifdef SHARP_ANALOG
    check_analog_sharp();
  #endif
}

void check_bumper() {

  Bumper.left = !digitalRead(pin_micro_1);
  Bumper.right = !digitalRead(pin_micro_2);

  // Debug
  if (Bumper.left || Bumper.right) {
    Log.notice(F("Bumper detected %T %T" CR), Bumper.left, Bumper.right);
  }
  digitalWrite(pin_led_debug, (Bumper.left || Bumper.right));
  // debug_state = (debug_state) ? false : true;
}


int get_average_from_array(int *source_t)
{
  // copy array from source
  int i,j;
  int copy_t[SIZE_ARRAY_SHARP];
  for (i = 0; i < SIZE_ARRAY_SHARP; ++i) {
       copy_t[i] = source_t[i];
   }
  //sort and filter extremum
   for (i = 1; i < SIZE_ARRAY_SHARP; ++i) {
       int elem = copy_t[i];
       for (j = i; j > 0 && copy_t[j-1] > elem; j--)
           copy_t[j] = copy_t[j-1];
       copy_t[j] = elem;
   }
   //compute average
   int sum=0;
   //we ignore first and last value in the array
   for (i = 1; i < SIZE_ARRAY_SHARP-1; ++i) {
      sum= sum+copy_t[i];
   }
   return sum/(SIZE_ARRAY_SHARP-2);
}

// FIFO simplified
void update_array(int new_value, int *array,int *current) {
  array[*current]=new_value;
  *current = (*current+1)%SIZE_ARRAY_SHARP;
}



 void Algo()
 {


  //distance = ;

   //if(distance > 30) return 31;
   //else if(distance < 4) return 3;
  //else return distance;
   int i;
   int left_sensor = 0;
   int right_sensor = 0;
   int middle_sensor = 0;

   for (i = 0; i < 5; i++)
     left_sensor += analogRead(pin_G_sharp);
   for (i = 0; i < 5; i++)
     right_sensor += analogRead(pin_D_sharp);
   for (i = 0; i < 5; i++)
     middle_sensor += analogRead(pin_M_sharp);

   left_sensor = left_sensor / 5;
   right_sensor = right_sensor / 5;
   middle_sensor = middle_sensor / 5;

   if (left_sensor < CONF_SENSOR && right_sensor < CONF_SENSOR && middle_sensor < CONF_SENSOR) {
     // avant();
     delay(100);
   }
   else if (left_sensor >= CONF_SENSOR && right_sensor < CONF_SENSOR) {
     // arret_droite();
     delay(100);
   }
   else if (right_sensor >= CONF_SENSOR && left_sensor < CONF_SENSOR) {
     // arret_gauche();
     delay(100);
   }
   else
   {
     // arret();
     // arriere();
     // delay(100);
     // tour();
     // delay(500);
   }
 }


/*******************INTERRUPTION*******************/
