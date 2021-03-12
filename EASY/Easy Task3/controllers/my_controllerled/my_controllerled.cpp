#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/LED.hpp>
#include <webots/Motor.hpp>
#define TIME_STEP 64
#include <webots/Receiver.hpp>
using namespace webots;


int main(int argc, char **argv) {

 Robot *robot = new Robot();
 
 LED *LED1[1];
 Receiver *car[1];
  
 
    LED1[0] = robot->getLED("led1");
    car[0]=robot->getReceiver("car");
    car[0]->enable(10);
     
     while (robot->step(TIME_STEP) != -1) {
     LED1[0]->set(255);
     
while((car[0]->getQueueLength())>0){
    const void *message= car[0]->getData();
    float *p = (float* )message;
    car[0]->nextPacket();

     //std::cout<<p<<std::endl;
  }}
  
  }

