#ifndef Movements_H_
#define Movements_H_

#include <headers/FonctionsSuiveur.h>
#include <headers/CapteurDistance.h>

int pulsesToAccelerate (float speed);
int pulsesToDecelerate(float speed);
float chooseAccordingSpeed(int pulses);
void decelerate ();
void pid(float currentSpeed);
int correct (float speed, int index);
void scan();
void followLine();

float maxSpeed = 0.2;
float currentSpeed = 0;

float wheelDiameter = 7.62;
float pi = PI;
float ppr = 3200;
float distancePerTurn = pi * wheelDiameter;
int pulsesPerCm = ppr / distancePerTurn;

bool searching = false;
bool isBackward = false;

int accelerationMsDelay = 100; //25 or higher (tenir compte que le maximum de boucle est 10)

const int decelerationPulses[10]=
{
    0,
    0,
    32,
    57,
    74,
    96,
    123,
    145,
    165,
    185
};

void forward () {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  bool accelerate = true;
  float speed = 0;
  while(accelerate) {
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    currentSpeed = speed;
    if(getDistance(PINDISTANCEHAUT) <= 20) {
      accelerate = false;
      decelerate();
    }else {
      pid(currentSpeed);
    } 
    delay(accelerationMsDelay); 
  }
}

void backward (float distance) {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  bool accelerate = true;
  float speed = 0;
  int decelerationPulses = 0;
  long distanceInPulses = 0;
  distanceInPulses = (long) pulsesPerCm * (long) distance;
  while(accelerate) {
    speed -= 0.1;
    if (speed < maxSpeed * -1) speed = maxSpeed * -1;
    currentSpeed = speed;
    decelerationPulses = pulsesToDecelerate((currentSpeed * -1)) * 100 / accelerationMsDelay;
    if(ENCODER_Read(0) * -1 > distanceInPulses - decelerationPulses) {
      accelerate = false;
      decelerate();
    }else {
      pid(currentSpeed);
    } 
    delay(accelerationMsDelay); 
  } 
}

void decelerate () {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  while (currentSpeed != 0) {
    if(isBackward) {
      currentSpeed = currentSpeed + 0.1;
      if(currentSpeed > 0) currentSpeed = 0;
      pid(currentSpeed);
    }else { 
      currentSpeed = currentSpeed - 0.1;
      if(currentSpeed < 0) currentSpeed = 0;
      pid(currentSpeed);
    }
    delay(accelerationMsDelay);
  } 
  isBackward = false; 
}

void pid(float currentSpeed) //reculons longue distance ca bug.
{
  if(currentSpeed != (float) 0) {
    float proportionnalControl = 0.001;

    float leftPulse = ENCODER_Read(0);
    float rightPulse = ENCODER_Read(1);
    float error = leftPulse - rightPulse;
    float rightSpeed = 0;
    float leftSpeed = 0;
    int backwardFactor = 0;
    if(isBackward) {
      backwardFactor = -1;
      error = (leftPulse + rightPulse);
    }else { 
      backwardFactor = 1;
    }
    if(error>5)
    {
      rightSpeed = (error * proportionnalControl * backwardFactor) + currentSpeed;  
      MOTOR_SetSpeed(1, rightSpeed);
      MOTOR_SetSpeed(0, currentSpeed);
    }
    else if(error<-5)
    {
      leftSpeed = (error * -1 * proportionnalControl * backwardFactor) + currentSpeed;
      MOTOR_SetSpeed(0, leftSpeed);
      MOTOR_SetSpeed(1, currentSpeed);
    }else{
      MOTOR_SetSpeed(0, currentSpeed);
      MOTOR_SetSpeed(1, currentSpeed);
    }
    error = 0;
  }else {
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
  } 
}

int pulsesToDecelerate (float speed) {
  return decelerationPulses[((int)(speed * 10))-1];
}

void turn (int side, int angle) {
  ( side == 0 ) ? side = 1 : side = 0;
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  int pulses = 0;
  float encoder = 0;
  pulses = (((angle * PI) / 180) * 19) * pulsesPerCm;

  MOTOR_SetSpeed(side, 0.4);

  while(encoder <pulses)
  {
     encoder= ENCODER_Read(side);
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}

void rotate (int side, int angle) {
  ENCODER_Reset(0);
  ENCODER_Reset(1);

  int pulses = 0;
  float encoder = 0;
  pulses = (((angle * PI) / 180) * 19) * pulsesPerCm;
  int otherSide = 0;
  (side == 0) ? otherSide = 1 : otherSide = 0;

  MOTOR_SetSpeed(side, -0.2);
  MOTOR_SetSpeed(otherSide, 0.2);
 
  while(encoder < pulses)
  {
     encoder= (ENCODER_Read(side) * -1) + ENCODER_Read(otherSide) ;
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}

void followLine() {
  bool accelerate = true;
  scan();
  Serial.println("ALLODSAd");
  float speed = 0;
  while(accelerate) {
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    currentSpeed = speed;
    /*if(getDistance(PINDISTANCEHAUT) <= 20) {
      
      accelerate = false;
      decelerate();
    }else {*/
      int voltage = getLineValue();
      int j = correct(currentSpeed, getTensionIndex(voltage));
      Serial.println(j);
      if( j == 1) {
        Serial.println("342354234234");
        MOTOR_SetSpeed(1, currentSpeed);
        MOTOR_SetSpeed(0, currentSpeed);
      }else {
        accelerate = false;
      }
    //}
  }
}

void scan() {
  bool found = false;
  int voltage = getLineValue();
  int index = getTensionIndex(voltage);
  if(index == 5) {
    found = true;
  }
  while(!found) {
    rotate(0,23);
    voltage = getLineValue();
    index = getTensionIndex(voltage);
    if(index == 5) {
      found = true;
    }else {
      int count = 0;
      while(count < 45 && !found) {
        rotate(1,1);
        voltage = getLineValue();
        index = getTensionIndex(voltage);
        if(index == 5) {
          found = true;
        }else {
          count++;
        }
        if(count == 45) {
          rotate(0,22);
        }
      }
    }
  }
}

int correct (float speed, int index) {
  switch (index)
  {
    case 0:case 7: decelerate(); return 0; break;
    case 1:case 4: rotate(1,1); return 1; break;
    case 3:case 6: rotate(0,1); return 1; break;
  }
  return 1;
} 

#endif 