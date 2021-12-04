#include <Arduino.h> 
#include <MatrixMath.h>

#define M1A 6
#define M1B 7
#define M2A 4
#define M2B 5
#define M3A 8
#define M3B 9

mtx_type gauss[3][3] = {{0.58, -0.33, 0.33}, {-0.58, -0.33, 0.33}, {0, 0.67, 0.33}};
//mtx_type gauss[3][3] = {{0, -0.586, 0.414}, {-0.707, -0.293, 0.293}, {0.707, 0.293, 0.293}};
mtx_type inp[3];
mtx_type output[3]; 
double f1, f2, f3 = 0; 

void motor_init()
{
    // Set the output pins
    pinMode(M1A, OUTPUT);
    pinMode(M1B, OUTPUT);
    pinMode(M2A, OUTPUT);
    pinMode(M2B, OUTPUT);
    pinMode(M3A, OUTPUT);
    pinMode(M3B, OUTPUT);
}

//determine how to move each motor 
void motor_control(int A, int B, double acc){
    if (acc<0){
        analogWrite(A, 0);
        analogWrite(B, -(acc*255));
    }
    else if (acc==0){
        digitalWrite(A, HIGH);
        digitalWrite(B, HIGH);
    }
    else {
        analogWrite(A, (acc*255));
        analogWrite(B, 0);
    }
}
//determine how to move the entire robot 
void move_bot(double ax, double ay, int w){
  inp[0]=ax;
  inp[1]=ay;
  inp[2]=w; 
  Matrix.Multiply((mtx_type*) gauss,(mtx_type*) inp, 3 , 3 , 1, (mtx_type*) output);
  f1 = output[0];
  f2 = output[1];
  f3 = output[2];
  motor_control(M1A, M1B, f1);
  motor_control(M2A, M2B, f2);
  motor_control(M3A, M3B, f3);
}
