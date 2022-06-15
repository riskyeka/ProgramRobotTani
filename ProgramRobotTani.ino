#include <A4988.h>
#include <BasicStepperDriver.h>
#include <DRV8825.h>
#include <DRV8834.h>
#include <DRV8880.h>
#include <MultiDriver.h>
#include <SyncDriver.h>
#include <BTS7960.h>

#define R_M1 6
#define L_M1 5
#define R_M2 7
#define L_M2 4
#define EN1 36
#define EN2 38
 
// using a 200-step motor (most common)
#define MOTOR_STEPS 200
// configure the pins connected
#define DIR_M1 37 
#define STEP_M1 3 
#define MS1_M1 43 
#define MS2_M1 41 
#define MS3_M1 39
#define ENS1   35 
#define DIR_M2 42
#define STEP_M2 2
#define MS1_M2 49
#define MS2_M2 47
#define MS3_M2 45
#define ENS2   40

#define dinamo 44

BTS7960 motor1(EN1, L_M1, R_M1);
BTS7960 motor2(EN2, L_M2, R_M2);
A4988 stepper1(MOTOR_STEPS, DIR_M1, STEP_M1, MS1_M1, MS2_M1, MS3_M1);
A4988 stepper2(MOTOR_STEPS, DIR_M2, STEP_M2, MS1_M2, MS2_M2, MS3_M2);

struct Num{
  int stepper1;
  int stepper2;
};
Num Step;

enum Number{R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15,R16,R17,R18,R19,R20};
Number stepRobot, stepFull;

unsigned long currTime=0; 
unsigned long lastTime=0;

bool flag = false;

void StepperDisable(int pil){
  switch(pil){
    case 1:
      digitalWrite(ENS1, HIGH);
      break;

    case 2:
      digitalWrite(ENS2, HIGH);
      break;

    case 3:
      digitalWrite(ENS1, HIGH);
      digitalWrite(ENS2, HIGH);
      break;
  }
}

void StepperEnable(int pil){
  switch(pil){
    case 1:
      digitalWrite(ENS1, LOW);
      break;

    case 2:
      digitalWrite(ENS2, LOW);
      break;

    case 3:
      digitalWrite(ENS1, LOW);
      digitalWrite(ENS2, LOW);
      break;
  }
}

void MotorEnable(void){
  motor1.Enable();
  motor2.Enable();
}

void MotorDisable(void){
  motor1.Disable();
  motor2.Disable();
}

void RMaju(int value){
  MotorEnable();
  motor1.TurnLeft(value);
  motor2.TurnRight(value);
}

void RMundur(int value){
  MotorEnable();
  motor1.TurnRight(value);
  motor2.TurnLeft(value);
}

void RMaju_Kanan(int value){
  MotorEnable();
  motor1.TurnLeft(value);
  motor2.Stop();
}

void RMaju_Kiri(int value){
  motor1.Stop();
  motor2.TurnRight(value);
}

void RMundur_Kanan(int value){
  MotorEnable();
  motor1.TurnRight(value);
  motor2.Stop();
}

void RMundur_Kiri(int value){
  MotorEnable();
  motor1.Stop();
  motor2.TurnLeft(value);
}

void setup() {
  pinMode(ENS1, OUTPUT);
  pinMode(ENS2, OUTPUT);
  stepper1.begin(50,1);
  stepper2.begin(50,1);
  pinMode(dinamo, OUTPUT);
  digitalWrite(dinamo, HIGH);
  Serial.begin(9600);
}

void subProgram(){
  switch(stepRobot){
    case R1:
      StepperDisable(3);
      currTime = millis()-lastTime;
      if(currTime <= 2000){
        RMaju(60);
      }
      else if(currTime > 2000){
        MotorDisable();
        Step.stepper1 = 1;
        stepRobot = R2;
      }
      break;

    case R2:
      currTime = 0;
      StepperEnable(1);
      if(Step.stepper1 <= 14){
        stepper1.rotate(90);
        Step.stepper1 += 1;
      }
      else{
        StepperDisable(3);
        digitalWrite(dinamo, LOW);
        stepRobot = R3;
      }
      break;

    case R3:
      Step.stepper1 = 1;
      delay(5000);
      digitalWrite(dinamo, HIGH);
      stepRobot = R4;
      break;

    case R4:
      StepperEnable(1);
      if(Step.stepper1 <= 14){
        stepper1.rotate(-90);
        Step.stepper1 += 1;
      }
      else{
        Step.stepper2 = 1;
        stepRobot = R5;
      }
      break;
      
    case R5:
      StepperEnable(2);
      if(Step.stepper2 <= 2){
        stepper2.rotate(360);
        Step.stepper2 += 1;
      }
      else{
        Step.stepper1 = 1;
        stepRobot = R6;
      }
      break;

    case R6:
      if(Step.stepper1 <= 18){
        stepper1.rotate(90);
        Step.stepper1 += 1;
      }
      else{
        stepRobot = R7;
      }
      break;

    case R7:
      Step.stepper1 = 1;
      delay(1000);
      stepRobot = R8;
      break;

    case R8:
      StepperEnable(1);
      if(Step.stepper1 <= 18){
        stepper1.rotate(-90);
        Step.stepper1 += 1;
      }
      else{
        Step.stepper2 = 1;
        stepRobot = R9;
      }
      break;

    case R9:
      StepperEnable(2);
      if(Step.stepper2 <= 6){
        stepper2.rotate(360);
        Step.stepper2 += 1;
      }
      else{
        Step.stepper1 = 1;
        stepRobot = R10;
      }
      break;

    case R10:
      if(Step.stepper1 <= 14){
        stepper1.rotate(90);
        Step.stepper1 += 1;
      }
      else{
        StepperDisable(3);
        digitalWrite(dinamo, LOW);
        stepRobot = R11;
      }
      break;

    case R11:
      Step.stepper1 = 1;
      delay(5000);
      digitalWrite(dinamo, HIGH);
      stepRobot = R12;
      break;

    case R12:
      StepperEnable(1);
      if(Step.stepper1 <= 14){
        stepper1.rotate(-90);
        Step.stepper1 += 1;
      }
      else{
        Step.stepper2 = 1;
        stepRobot = R13;
      }
      break;

    case R13:
      StepperEnable(2);
      if(Step.stepper2 <= 2){
        stepper2.rotate(-360);
        Step.stepper2 += 1;
      }
      else{
        Step.stepper1 = 1;
        stepRobot = R14;
      }
      break;

    case R14:
      if(Step.stepper1 <= 18){
        stepper1.rotate(90);
        Step.stepper1 += 1;
      }
      else{
        stepRobot = R15;
      }
      break;

    case R15:
      Step.stepper1 = 1;
      delay(1000);
      stepRobot = R16;
      break;

    case R16:
      StepperEnable(1);
      if(Step.stepper1 <= 18){
        stepper1.rotate(-90);
        Step.stepper1 += 1;
      }
      else{
        Step.stepper2 = 1;
        stepRobot = R17;
      }
      break;

    case R17:
      StepperEnable(2);
      if(Step.stepper2 <= 6){
        stepper2.rotate(-360);
        Step.stepper2 += 1;
      }
      else{
        delay(1000);
        lastTime = millis();
        flag = true;
      }
      break;
  }
}

void mainProgram(){
  switch(stepFull){
    case R1:
      subProgram();
      if(flag == true){
        flag = false;
        stepRobot = R1;
        stepFull = R2; 
      }
      break;

    case R2:
      subProgram();
      if(flag == true){
        flag = false;
        stepRobot = R1;
        stepFull = R3; 
      }
      break;

    case R3:
      StepperDisable(3);
      RMaju_Kanan(80);
      delay(10900);
      stepFull = R1; 
      break;
  }
}

void loop() {
  mainProgram();
}
