#include <Arduino.h>

#define M1 9
#define M2 10
#define M3 11

void setup() {
  // put your setup code here, to run once:
pinMode(M1, INPUT);
pinMode(M2, INPUT);
pinMode(M3, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
//forward
analogWrite(M1, 63);
analogWrite(M2, 63);
analogWrite(M3, 63);
delay(3000);
//left
analogWrite(M1, 0);
analogWrite(M2, 63);
analogWrite(M3, -63);
delay(3000);
//right
analogWrite(M1, 0);
analogWrite(M2, -63);
analogWrite(M3, 63);
delay(3000);
//backwards
analogWrite(M1, -63);
analogWrite(M2, -63);
analogWrite(M3, -63);
delay(3000);
}