#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/LED.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#define TIME_STEP 64
using namespace webots;


int main(int argc, char **argv) {

  Robot *robot = new Robot();
  LED *LED_show[7];
  Motor *wheels[4];
  DistanceSensor *S[5];
  int TH = 500;
  int count = 0;
  bool start = true;
  char wheels_names[4][4] = {"LF", "LB", "RF", "RB"};
  char dsNames[5][3] = {"S1", "S2", "S3", "S4", "S5"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    // wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(1);
  }
  char LED_names[7][10] = {"led1", "led2", "led3", "led4", "led5", "Start_LED", "End_LED"};
  for (int i = 0; i < 7; i++) {
    LED_show[i] = robot->getLED(LED_names[i]);
  }
  for (int i = 0; i < 5; i++) {
    S[i] = robot->getDistanceSensor(dsNames[i]);
    S[i]->enable(TIME_STEP);
  }

  /////////simulation starts///////
  while (robot->step(TIME_STEP) != -1) {
    bool Ir1 = (S[0]->getValue()) < TH;
    bool Ir2 = (S[1]->getValue()) < TH;
    bool Ir3 = (S[2]->getValue()) < TH;
    bool Ir4 = (S[3]->getValue()) < TH;
    bool Ir5 = (S[4]->getValue()) < TH;
    LED_show[0]->set(255 * Ir1);
    LED_show[1]->set(255 * Ir2);
    LED_show[2]->set(255 * Ir3);
    LED_show[3]->set(255 * Ir4);
    LED_show[4]->set(255 * Ir5);

    if (Ir1 == true && Ir2 == true && Ir3 == true && Ir4 == true && Ir5 == true && start == true) {
      for (int i = 0; i < 4; i++) {
        wheels[i]->setPosition(INFINITY);
        LED_show[5]->set(255);
      }
    }
    else if (Ir1 != true && Ir2 != true && Ir3 != true && Ir4 != true && Ir5 != true) {
      count++;

      if (count > 20) {
        LED_show[6]->set(255);
        for (int i = 0; i < 4; i++) {
          wheels[i]->setVelocity(0);

        }
      }

    }
    else {
      count = 0;
      LED_show[5]->set(0);
      for (int i = 0; i < 4; i++) {
        wheels[i]->setPosition(INFINITY);

      }
      start = false;
    }
    // std::cout<<<<std::endl;



  }
}



