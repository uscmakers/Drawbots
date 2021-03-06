#include <Arduino.h>
#include <softwareserial.h> // remove the inverted commas after you copy the code to the IDE
#include "motor_control.h"
#include <string.h> 
#include <Servo.h>

SoftwareSerial BT(10, 11); 
Servo servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 180;
int flag=0;

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
      angle2 = angle2*3.14/180;
      double strength2 = strength1.toDouble();
      double button2 = button.toDouble();
      /*
      if ((angle2<=1.57) | (angle2>=4.712)){
        if (angle2<=1.57){
          move_bot(-strength2/100*sin(angle2), strength2/100*cos(angle2), strength2/100);
        }
        else {
          move_bot(strength2/100*sin(angle2-4.712), strength2/100*cos(angle2-4.712), strength2/100);
        }
      }
      else {
        if (angle2<=3.14){
          move_bot(-strength2/100*sin(angle2-1.57), -strength2/100*cos(angle2-1.57), strength2/100);
        }
        else {
          move_bot(strength2/100*sin(angle2-3.14), -strength2/100*cos(angle2-3.14), strength2/100);
        }
      }
      */
      if (button2 == 1.0){
        move_bot(0,0,0);
        BT.flush();
      }
      else if (button2 == 3.0) {
        motor_control(6,7,1);
        motor_control(4, 5, -1);
        motor_control(8, 9, 0);
      }
      else if (button2 == 2.0) {
        motor_control(6,7,1);
        motor_control(4, 5, 1);
        motor_control(8, 9, 0);
      }
      else if (button2 == 4.0){
        motor_control(6,7,-1);
        motor_control(4, 5, -1);
        motor_control(8, 9, 1);
      }
      Serial.print("angle;");
      Serial.print(angle2);
      Serial.print('\t');
      Serial.print("strength;");
      Serial.print(strength2);
      Serial.print('\t');
      Serial.print("button;");
      Serial.print(button2);
      Serial.print('\t');
      Serial.println("");
      Serial.flush();
      value = "";
    }
  }
}

