#include <iostream>
#include <stdlib.h>
#include "PID.h"

#define WINDOW_SIZE 20


using namespace std;


PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  p_error = 0;
  i_error = 0;
  d_error = 0;
  window      = (int*) calloc( WINDOW_SIZE , sizeof(window[0]) ) ;
  i           = WINDOW_SIZE - 1 ;
  sum         = 0 ;
}

void PID::UpdateError(double cte, double dt) {
  d_error = (cte - p_error) / dt;
  p_error = cte;
  i_error = add_i(cte * dt);
}

double PID::TotalError(double speed) {
  //PID parameters corrected for different speed
  return (Kp - 0.0032 * speed) * p_error + Ki * i_error + (Kd + 0.0002 * speed) * d_error;
}

// For i_error calculation we sum up only WINDOW_SIZE measurements
// inspired by code from https://stackoverflow.com/questions/25024012/running-sum-of-the-last-n-integers-in-an-array
double PID::add_i(double err){
  i          = (i+1) % WINDOW_SIZE ;
  sum        = sum - window[i] + err ;
  return sum;
}
