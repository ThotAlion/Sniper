#include "shared.h"


#define SPEED 50

// H bridge pin
const uint8_t pin_I1_D = 5; //define I1 port
const uint8_t pin_I2_D = 6; //define I2 port
const uint8_t pin_PWM_D = 3; //define EA(PWM speed regulation)port

const uint8_t pin_I1_G = 7; //define I1 port
const uint8_t pin_I2_G = 8; //define I2 port
const uint8_t pin_PWM_G = 4; //define EA(PWM speed regulation)port

//Odometer
const uint8_t pin_enc_left_A = 14; //encodeur moteur gauche
const uint8_t pin_enc_left_B = 15;

const uint8_t pin_enc_right_A = 16;
const uint8_t pin_enc_right_B = 17;



// declare GPIO for mobility
void init_gpio_motor() {

  // Odometer
  pinMode(pin_enc_left_A,INPUT_PULLUP);
  pinMode(pin_enc_left_B,INPUT_PULLUP);
  pinMode(pin_enc_right_A, INPUT_PULLUP);
  pinMode(pin_enc_right_B, INPUT_PULLUP);

  // attachInterrupt(digitalPinToInterrupt(pin_enc_left_A), incr_odometer_ISR, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(pin_enc_left_B), incr_odometer_ISR, CHANGE);


  // Left H bridge
  pinMode(pin_I1_G, OUTPUT);
  pinMode(pin_I2_G, OUTPUT);
  pinMode(pin_PWM_G, OUTPUT);

  // Right H bridge
  pinMode(pin_I1_D, OUTPUT);
  pinMode(pin_I2_D, OUTPUT);
  pinMode(pin_PWM_D, OUTPUT);
}




void set_left_motor_speed(int cmd) {
  if (cmd < 0) {
    if (cmd < -255) {
      cmd = -255;
    }
    analogWrite(pin_PWM_G, -cmd);
    digitalWrite(pin_I1_G, HIGH);
    digitalWrite(pin_I2_G, LOW);
    
  } else {
    if (cmd > 255) {
      cmd = 255;
    }
    analogWrite(pin_PWM_G, cmd);
    digitalWrite(pin_I1_G, LOW);
    digitalWrite(pin_I2_G, HIGH);
  }
}

void set_right_motor_speed(int cmd) {
  if (cmd < 0) {
    if (cmd < -255) {
      cmd = -255;
    }
    analogWrite(pin_PWM_D, -cmd);
    digitalWrite(pin_I1_D, LOW);
    digitalWrite(pin_I2_D, HIGH);
    
  } else {
    if (cmd > 255) {
      cmd = 255;
    }
    analogWrite(pin_PWM_D, cmd);
    digitalWrite(pin_I1_D, HIGH);
    digitalWrite(pin_I2_D, LOW);
  }
}

void set_motor_speed(uint8_t dir_pin, uint8_t speed_pin, uint8_t brake_pin,int speed) {
  
}

// -----------------------

void arret() {
  analogWrite(pin_PWM_G, 0);
  analogWrite(pin_PWM_D, 0);
  digitalWrite(pin_I1_G, HIGH); // DC motor stop rotating
  digitalWrite(pin_I2_G, HIGH);
  digitalWrite(pin_I1_D, HIGH); // DC motor stop rotating
  digitalWrite(pin_I2_D, HIGH);
}

void arret_gauche() {
  analogWrite(pin_PWM_G, 0);
  digitalWrite(pin_I1_G, HIGH); // DC motor stop rotating
  digitalWrite(pin_I2_G, HIGH);
  analogWrite(pin_PWM_D, SPEED);
  digitalWrite(pin_I1_D, HIGH); // DC motor rotates clockwise
  digitalWrite(pin_I2_D, LOW);
}

void arret_droite() {
  analogWrite(pin_PWM_D, 0);
  digitalWrite(pin_I1_D, HIGH); // DC motor stop rotating
  digitalWrite(pin_I2_D, HIGH);
  analogWrite(pin_PWM_G, SPEED - 20);
  digitalWrite(pin_I1_G, LOW); // DC motor rotates clockwise
  digitalWrite(pin_I2_G, HIGH);
}

void avant() {
  analogWrite(pin_PWM_G, SPEED - 20);
  analogWrite(pin_PWM_D, SPEED);
  digitalWrite(pin_I1_G, LOW); // DC motor rotates clockwise
  digitalWrite(pin_I2_G, HIGH);
  digitalWrite(pin_I1_D, HIGH); // DC motor rotates clockwise
  digitalWrite(pin_I2_D, LOW);
}
void arriere() {
  analogWrite(pin_PWM_G, SPEED - 20);
  analogWrite(pin_PWM_D, SPEED);
  digitalWrite(pin_I1_G, HIGH); // DC motor rotates clockwise
  digitalWrite(pin_I2_G, LOW);
  digitalWrite(pin_I1_D, LOW); // DC motor rotates clockwise
  digitalWrite(pin_I2_D, HIGH);
}
void tour() {
  analogWrite(pin_PWM_G, SPEED);
  analogWrite(pin_PWM_D, SPEED);
  digitalWrite(pin_I1_G, LOW); // DC motor rotates clockwise
  digitalWrite(pin_I2_G, HIGH);
  digitalWrite(pin_I1_D, LOW); // DC motor rotates clockwise
  digitalWrite(pin_I2_D, HIGH);
}
