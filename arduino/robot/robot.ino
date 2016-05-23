#include <Adafruit_PWMServoDriver.h>

#define MAX 600
#define RESET 400
#define MIN 150

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

uint8_t hip = 0;
uint8_t knee = 1;

//{hip, knee}
uint8_t fl[2] = {0,4};
uint8_t fr[2] = {1,5};
uint8_t bl[2] = {2,6};
uint8_t br[2] = {3,7};


void setup(){

  Serial.begin(115200);
  Serial.println("Robot initializing!");

  pwmDriver.begin();
  pwmDriver.setPWMFreq(60);

  center();
  
  yield();
}


void loop(){

  walk();

}

void walk(){
  
  moveLeg(fl);
  moveLeg(br);
  moveLeg(fr);
  moveLeg(bl);

  moveBody();
  
}

void center(){

  for (uint8_t curServo = 0; curServo < 7; curServo++){
    pwmDriver.setPWM(curServo, 0, RESET);
  }

  delay(300);
}

void moveLeg(uint8_t *leg){

  //move knee up
  pwmDriver.setPWM(leg[knee], 0, MAX);

  delay(300);

  //move hip forward
  pwmDriver.setPWM(leg[hip], 0, MAX);

  delay(300);

  //move knee down
  pwmDriver.setPWM(leg[knee], 0, MIN);
  
  delay(300);
}

void moveBody(){
  pwmDriver.setPWM(fl[hip], 0, MIN);
  pwmDriver.setPWM(bl[hip], 0, MIN);
  pwmDriver.setPWM(fr[hip], 0, MIN);
  pwmDriver.setPWM(fl[hip], 0, MIN);

  delay(300);
}

