#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/LED.hpp>
#include <webots/Motor.hpp>
#define TIME_STEP 64
using namespace webots;


int main(int argc, char **argv) {

 Robot *robot = new Robot();
 LED *LED1[1];
 Motor *wheels[4];
 char wheels_names[4][4] = {"LFJ", "RFJ", "LBJ", "RBJ"};
 for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
   // wheels[i]->setPosition(INFINITY);
    //wheels[i]->setVelocity(0.0);
  }
  
    LED1[0] = robot->getLED("led");
  
     while (robot->step(TIME_STEP) != -1) {
 /*   
       float a = 1;
      car_emitter[0]->send( &a,sizeof(float));
     
while(hear==0 &&(car_receiver[0]->getQueueLength())>0){
    const void *message= car_receiver[0]->getData();
    float *p = (float* )message;
    car_receiver[0]->nextPacket();
 if(*p==2){
    
  
     
    /// car_receiver[0]->disable();
   //  hear=1;
    //  t=robot->getTime();
      
   //  break;}
  
  
  //}
  */
 // if(hear==1 && (robot->getTime())>t+2 ){
   LED1[0]->set(255);
      wheels[0]->setPosition(20);
      wheels[1]->setPosition(20);
      wheels[2]->setPosition(-20);
      wheels[3]->setPosition(20);
      std::cout<<"msg received  - go"<<std::endl;
 // hear=2;
 // t=robot->getTime();


 // }
  
 
  }}
  
  

