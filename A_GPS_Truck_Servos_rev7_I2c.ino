/*
*/
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x43);

//i2c Servo-LED driver board pins
#define Throttle      0   // ESC output pin
#define FrontSteering 1   // Steering servo control pin
#define Red_LED       2   // RGB indication LED
#define Green_LED     3   // RGB indication LED
#define Blue_LED      4   // RGB indication LED
//////////////////////////////Timing////
unsigned long interval = 300;
unsigned long previousMillis = 0;

int instruction = 0;     // the information from the Master Arduino is stored here
// STEERING SERVO SETTINGS Using writeMicroseconds()
int FrontCenter = 1474;  
int SoftRight =  1224;   
int SoftLeft =   1712;   
int HardRight = 974;
int HardLeft =  1950;

// SPEED CONTROL SERVO SETTINGS Using writeMicroseconds()
int ThrottleCenter = 1446; // center = +238 OR -250
int ThrottleSpeed = 1750;
int SlowForward = 1700;  //1600 was too slow, changed 8.19.17
int FastForward = 1966;
int SlowReverse = 1300;
int FastReverse = 956;
////////////////////////////LED CONTROL/////////////////
int Red_State = 4096;
int Red_State2 = 0;
int Green_State = 4096;
int Green_State2 = 0;
int Blue_State = 4096;
int Blue_State = 0;


void setup() {

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

void loop() {

}
if (currentMillis - previousMillis > interval) {
  // save the last time you blinked the LED
  previousMillis = currentMillis;

  // if the LED is off turn it on and vice-versa:
  if (Red_State == 4096) //LOW
    Red_State = 0;  //HIGH
  Red_State2 = 4096;
  else
    Red_State = 4096; //LOW
  Red_State2 = 0;

  if (Green_State == 4096) //LOW
    Green_State = 0;  //HIGH
  Green_State2 = 4096;
  else
    Green_State = 4096;  //LOW
  Green_State2 = 0;

  if (Blue_State == 4096)  //LOW
    Blue_State = 0; //HIGH
  Blue_State2 = 4096;
  else
    Blue_State = 4096;  //LOW
  Blue_State2 = 0;
}
// Serial.println(instruction);
switch (instruction) {
case 0:
  pwm.setPWM(Throttle, 0, ThrottleCenter);             //    pwm.setPWM(servonum, 0, pulselen);
  pwm.setPWM(FrontSteering, 0, FrontCenter);
  pwm.setPWM(Red_LED, Red_State, Red_State2);     //setPWM(channel, on time, off time) 0 to 4096
  pwm.setPWM(Green_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Blue_LED, 4096, 0);                //LEDs totally off use setPWM(pin, 4096, 0);
  break;
case 11:   //hard left
  pwm.setPWM(Throttle, 0, SlowForward);
  pwm.setPWM(FrontSteering, 0, HardLeft);
  pwm.setPWM(Red_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Green_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Blue_LED, Blue_State, Blue_State2);
  break;
case 12:   //hard right
  pwm.setPWM(Throttle, 0, SlowForward);
  pwm.setPWM(FrontSteering, 0, HardRight);
  pwm.setPWM(Red_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Green_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Blue_LED, Blue_State, Blue_State2);
  break;
case 20:   //fast straight
  pwm.setPWM(Throttle, 0, ThrottleSpeed);
  pwm.setPWM(FrontSteering, 0, FrontCenter);
  pwm.setPWM(Red_LED, Red_State);
  pwm.setPWM(Green_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Blue_LED, Red_State, Red_State2);
  break;
case 21:   //fast left
  pwm.setPWM(Throttle, 0, ThrottleSpeed);
  pwm.setPWM(FrontSteering, 0, SoftLeft);
  pwm.setPWM(Red_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Green_LED, Green_State, Green_State2);
  pwm.setPWM(Blue_LED, 4096, 0);                //LEDs totally off use setPWM(pin, 4096, 0);
  break;
case 22:   //fast right
  pwm.setPWM(Throttle, 0, ThrottleSpeed);
  pwm.setPWM(FrontSteering, 0, SoftRight);
  pwm.setPWM(Red_LED, 4096, 0);               //LEDs totally off use setPWM(pin, 4096, 0);
  pwm.setPWM(Green_LED, Green_State, Green_State2);
  pwm.setPWM(Blue_LED, 4096, 0);                //LEDs totally off use setPWM(pin, 4096, 0);
  break;

case 30:    // your hand is close to the sensor
  // Serial.println("Reverse");
  pwm.setPWM(Throttle, 0, SlowReverse);
  pwm.setPWM(FrontSteering, 0, SoftRight);
  break;
}


