#include <webots/Robot.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <iostream>
// time in [ms] of a simulation step
#define TIME_STEP 64

#define MAX_SPEED 6.28
float Kp=8;
float Ki=0.001;
float Kd=10;
int mid=5;
float P,I,D,previous_error;
// All the webots classes are defined in the "webots" namespace
using namespace webots;


float PID(double psValues[]){


double error= ((psValues[2]*2) + (psValues[1]*2) + (psValues[0]*2))- ((psValues[5]*2) + (psValues[6]*2) + (psValues[7]*2));

P=Kp*error;
I+=Ki*error;
D=Kd*(error-previous_error);
previous_error=error;

float output_PID=(P+I+D)/100;
std::cout << "Sensor value is: " << output_PID<< std::endl;
return output_PID;

}

// entry point of the controller
int main(int argc, char **argv) {
  // create the Robot instance.
  Robot *robot = new Robot();


  // initialize devices
  DistanceSensor *ps[8];
  char psNames[8][4] = {
    "ps0", "ps1", "ps2", "ps3",
    "ps4", "ps5", "ps6", "ps7"
  };

  for (int i = 0; i < 8; i++) {
    ps[i] = robot->getDistanceSensor(psNames[i]);
    ps[i]->enable(TIME_STEP);
  }

  Motor *leftMotor = robot->getMotor("left wheel motor");
  Motor *rightMotor = robot->getMotor("right wheel motor");
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);

  // feedback loop: step simulation until an exit event is received
  while (robot->step(TIME_STEP) != -1) {
    // read sensors outputs
    double psValues[8];
    for (int i = 0; i < 8 ; i++)
      psValues[i] = ps[i]->getValue();

    float feedback=PID(psValues);
    // printf("Sensor value is %f\n", feedback);
    // initialize motor speeds at 50% of MAX_SPEED.
    double leftSpeed  = mid-feedback ;
    double rightSpeed = mid+feedback;
   if(leftSpeed>=MAX_SPEED){
   leftSpeed=MAX_SPEED;
   }
   else if(leftSpeed<0){
   leftSpeed=0;
   }
   if(rightSpeed>=MAX_SPEED){
   rightSpeed=MAX_SPEED;
   }
   else if(rightSpeed<0){
   rightSpeed=0;
   }
   leftMotor->setVelocity(leftSpeed);
   rightMotor->setVelocity(rightSpeed);
  }

  delete robot;
  return 0; //EXIT_SUCCESS
}