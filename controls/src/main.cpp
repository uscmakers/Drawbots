#include <Arduino.h>
#include <softwareserial.h> // remove the inverted commas after you copy the code to the IDE
#include "motor_control.h"
#include <string.h> 
#include <Servo.h>

SoftwareSerial BT(10, 11); 
Servo servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 180;

// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND

String value = "";
void setup(){
  servo.attach(3);
  BT.begin(9600);
  Serial.begin(9600);
  motor_init();
  BT.println("Hello from Arduino");
  servo.write(180);
}
 
void loop(){
  if(BT.available() > 0){
    value = BT.readStringUntil('#');
    //Serial.println(value);
    if(value.length() == 7){
      String angle1 = value.substring(0,3);
      String strength1 = value.substring(3,6);
      String button = value.substring(6, 8);
      double angle2 = angle1.toDouble();
      double strength2 = strength1.toDouble();
      double button2 = button.toDouble();
      if ((angle2<=90) | (angle2>=270)){
        if (angle2<=90){
          move_bot(strength2/100, 0, -angle2);
        }
        else {
          move_bot(strength2/100, 0, angle2-270);
        }
      }
      else {
        if (angle2<=180){
          move_bot(-strength2/100, 0, -angle2);
        }
        else {
          move_bot(-strength2/100, 0, angle2-180);
        }
      }
      if (button2 == 1){
        move_bot(0,0,0);
        BT.flush();
      }
      else if (button2 == 4) {
        if (pos==180){
          pos=0;
          servo.write(pos);
        }
        else {
          pos=180;
          servo.write(pos);
        }
      }
      Serial.print("angle;");
      Serial.print(angle2);
      Serial.print('\t');
      Serial.print("strength;");
      Serial.print(strength2);
      Serial.print('\t');
      Serial.println("");
      Serial.flush();
      value = "";
    }
  }
}

