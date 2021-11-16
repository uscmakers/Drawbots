#include <Arduino.h>
#include <softwareserial.h> // remove the inverted commas after you copy the code to the IDE

SoftwareSerial BT(10, 11); 
// creates a "virtual" serial port/UART
// connect BT module TX to D10
// connect BT module RX to D11
// connect BT Vcc to 5V, GND to GND
String value= "";
void setup(){
  Serial.begin(9600);
}

void loop(){
  
  if(Serial.available() > 0){
    value = Serial.readStringUntil('#');
  }
  if(value.length() == 7){
    String angle = value.substring(0,3);
    String strength = value.substring(3,6);
    String button = value.substring(6,8);
    Serial.print("angle;");
    Serial.print(angle);
    Serial.print('\t');
    Serial.print("strength;");
    Serial.print(strength);
    Serial.print('\t');
    Serial.print("button;");
    Serial.print(button);
    Serial.println("");
    Serial.flush();
    value = "";
  }
}











// void setup()  
// {
//   // set digital pin to control as an output
//   pinMode(13, OUTPUT);
//   // set the data rate for the SoftwareSerial port
//   BT.begin(9600);
//   // Send test message to other device
//   BT.println("Hello from Arduino");
// }
// char a; // stores incoming character from other device
// void loop() 
// {
//   if (BT.available())// if text arrived in from BT serial...
//   {
//     a=(BT.read());
//     if (a=='1')
//     {
//       digitalWrite(13, HIGH);
//       BT.println("LED on");
//     }
//     if (a=='2')
//     {
//       digitalWrite(13, LOW);
//       BT.println("LED off");
//     }
//     if (a=='?')
//     {
//       BT.println("Send '1' to turn LED on");
//       BT.println("Send '2' to turn LED on");
//     }   

//     if(a == 'N'){

//     }
//     if(a == 'E'){
      
//     }
//     if(a == 'S'){
      
//     }
//     if(a == 'W'){
      
//     }
//     if(a == 'A'){
      
//     }
//     if(a == 'B'){
      
//     }
//     if(a == 'C'){
      
//     }
//     if(a == 'D'){
      
//     }

//     // you can add more "if" statements with other characters to add more commands
//   }

