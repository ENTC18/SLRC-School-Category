#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Keyboard.hpp>


#define TIME_STEP 64
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  Keyboard kb;
  DistanceSensor *ds[2];
  
  char dsNames[2][10] = {"DSR", "DSL"};
  for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
  

  
  Motor *wheels[4];
  char wheels_names[4][8] = {"LF", "RF", "LB", "RB"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0.0);
  }
  
  kb.enable(TIME_STEP);
  double leftSpeed = 0.0;
  double rightSpeed = 0.0;
  while (robot->step(TIME_STEP) != -1) {
    int key=kb.getKey();
    
    if (key==315){
    leftSpeed = 1.0;
    rightSpeed = 1.0;
    } else if (key==317){
    leftSpeed = -1.0;
    rightSpeed = -1.0;
    }else if (key==316){
    leftSpeed = 1.0;
    rightSpeed = -1.0;
    }else if (key==314){
    leftSpeed = -1.0;
    rightSpeed = 1.0;
    }else {
    leftSpeed = 0.0;
    rightSpeed = 0.0;
    }
  std::cout<<ds[0]->getValue()<<"=Right Sensor"<<std::endl;
   std::cout<<ds[1]->getValue()<<"=Left Sensor"<<std::endl;
    wheels[0]->setVelocity(-leftSpeed*5);
    wheels[1]->setVelocity(-rightSpeed*5);
    wheels[2]->setVelocity(-leftSpeed*5);
    wheels[3]->setVelocity(-rightSpeed*5);
 
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}