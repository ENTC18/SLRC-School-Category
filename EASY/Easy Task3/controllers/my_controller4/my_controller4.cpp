#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>

#define TIME_STEP 64
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
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
  int avoidObstacleCounter = 0;
  while (robot->step(TIME_STEP) != -1) {
    double leftSpeed = 10.0;
    double rightSpeed = 10.0;
    if (avoidObstacleCounter > 0) {
      avoidObstacleCounter--;
      leftSpeed = 10.0;
      rightSpeed = -10.0;
    } else { // read sensors
      for (int i = 0; i < 2; i++) {
        if (ds[i]->getValue() < 950.0)
          avoidObstacleCounter = 10;
      }
    }
   wheels[0]->setVelocity(-leftSpeed);
    wheels[1]->setVelocity(-rightSpeed);
    wheels[2]->setVelocity(-leftSpeed);
    wheels[3]->setVelocity(-rightSpeed);
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}