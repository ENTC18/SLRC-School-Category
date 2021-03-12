#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/LED.hpp>
#define TIME_STEP 64
#include <webots/Emitter.hpp>
using namespace webots;
#include <webots/Receiver.hpp>

int main(int argc, char **argv) {
int hear=0;
 Robot *robot = new Robot();
 
   Motor *bars[1];
   Emitter *door_emitter[1];
   Receiver *door_receiver[1];


 
    bars[0] = robot->getMotor("barrier motor");
    door_emitter[0] = robot->getEmitter("door");
    door_receiver[0] = robot->getReceiver("receiver_bar");
    door_receiver[0]->enable(10);
  
 
     
     while (robot->step(TIME_STEP) != -1) {

   while((door_receiver[0]->getQueueLength())>0  ){
    const void *message= door_receiver[0]->getData();
    float *p = (float* )message;
    door_receiver[0]->nextPacket();
    if(*p==1 && hear==0){
    
     std::cout<<"msg received  - opening"<<std::endl;
      bars[0]->setPosition(-1);
     
      hear=1;
      float a = 2;
      door_emitter[0]->send( &a,sizeof(float));
     break;} 
     if(*p==3 && hear==1){
    
     std::cout<<"msg received  - closing"<<std::endl;
    bars[0]->setPosition(0);
     
     break;} 
  }

   
     
}}

