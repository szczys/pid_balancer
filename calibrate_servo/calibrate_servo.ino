/*
 * Used to calibrate servo on a ball balancer
 * Send 0-255 on Serial to put the servo into that position
 */

#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 12;

void setup() {
  Serial.begin(115200);
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 500, 3500); // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
  myservo.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    uint8_t digit_count = 0;
    uint16_t sum = 0;
    while(Serial.available() > 0) {
      uint16_t rx_byte = Serial.read();
      if ((rx_byte >= 48) && (rx_byte <= 57)) {
        digit_count += 1;
        rx_byte -= 48; //Convert ASCII to INT
        sum *= 10;
        sum += rx_byte;
      }
      else { Serial.flush(); break; }
    }
    if (digit_count > 0) {
      Serial.println(sum);
      myservo.write(sum);
    }
  }
}
