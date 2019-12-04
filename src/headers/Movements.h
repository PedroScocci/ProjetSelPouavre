/*
Projet S1 2019
Librairie pour le capteur infrarouge.
@auteur Jérémy Chenard
@version 1.0 03/11/2019
*/
#ifndef Movements_H_
#define Movements_H_

#include "headers/FonctionsSuiveur.h"
#include "headers/CapteurDistance.h"
#include "headers/LCD.h"

#define DEGAJUSTEMENT 2

#define PIN_SUIVEUR1 A5 //Droite
#define PIN_SUIVEUR2 A6 //Milieu
#define PIN_SUIVEUR3 A7 //Gauche

//Prototypes des fonctions
int pulsesToAccelerate (float speed);
int pulsesToDecelerate(float speed);
float chooseAccordingSpeed(int pulses);
void decelerate ();
void pid(float currentSpeed);
int scan();
void followLine();

//Variables globale
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
 
 //Constantes globale
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

//Fonctions
void forward () {
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  float speed = 0;
  int temps = 0;
  //13 secondes.
  while(temps != 8) {
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    currentSpeed = speed;
    if(getDistance(PINDISTANCEBAS) <= 20) {
      decelerate();
    }else {
      pid(currentSpeed);
    } 
    delay(accelerationMsDelay); 
    temps++;
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
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

  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
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

  MOTOR_SetSpeed(side, 0.1);

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
  bool stopped = false;

  scan();
  float speed = 0;
  while(accelerate) {
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    if(getDistance(PINDISTANCEBAS) <= 15) {
      decelerate();
      currentSpeed = 0;
      if(!stopped) {
        stopped = true;
        ecrirelcd("    OBSTACLE        DETECTE!!");
      }
    }else {
      if(stopped) {
        stopped = false;
        initialisationLCD();
      }
      currentSpeed = speed;
      int j = scan();
      if( j == 1) {
        MOTOR_SetSpeed(1, currentSpeed);
        MOTOR_SetSpeed(0, currentSpeed);
        delay(50);
      }
      else {
        accelerate = false;
      }
    }
  }
  decelerate();
}

int scan() {
  bool found = false;
  int voltage1 = 0;
  int voltage2 = 0;
  int voltage3 = 0;
  int base = 1;
  int direct = 0;
  int retour = 0;
 
  while(found == false)
  {
    voltage1 = analogRead(PIN_SUIVEUR1);
    voltage2 = analogRead(PIN_SUIVEUR2);
    voltage3 = analogRead(PIN_SUIVEUR3);

    //Tous dans le blanc
    if(voltage1 > 3 && voltage2 > 3 && voltage3 > 3){
      base = 5;
      voltage2 = analogRead(PIN_SUIVEUR2);
      delay(10);

      while(voltage2 > 3){
        if(direct == 0){
          rotate(direct,base);
          delay(50);
          direct = 1;
          base++;
        }else{
          rotate(direct,base);
          delay(50);
          direct = 0;
          base++;
        }
        delay(50);

        voltage2 = analogRead(PIN_SUIVEUR2);
     }

     retour = 1;
     found = true;
    }
    //Gauche et centre blanc
    else if(voltage1 < 3 && voltage2 > 3 && voltage3 > 3){
      turn(1,2);
    }
    //Seulement gauche
    else if(voltage1 < 3 && voltage2 < 3 && voltage3 > 3){
      turn(1,2);
      found = true;
      retour = 1;
    }
    //Tous noir
    else if(voltage1 < 3 && voltage2 < 3 && voltage3 < 3){
      delay(50);
      voltage1 = analogRead(PIN_SUIVEUR1);
      voltage2 = analogRead(PIN_SUIVEUR2);
      voltage3 = analogRead(PIN_SUIVEUR3);
      if(voltage1 < 3 && voltage2 < 3 && voltage3 < 3){
        found = true;
        retour = 0;
      } 
    }
    //Gauche et Droite
    else if(voltage1 > 3 && voltage2 < 3 && voltage3 > 3){
      found = true;
      retour = 1;
    }
    //Seulement droite
    else if(voltage1 > 3 && voltage2 < 3 && voltage3 < 3){
      turn(0,2);
      found = true;
      retour = 1;
    }
    //Droite et centre
    else if(voltage1 > 3 && voltage2 > 3 && voltage3 < 3){
      turn(0,2);
    }
    //Seulement centre
    else if(voltage1 < 3 && voltage2 > 3 && voltage3 < 3){
      found = true;
      retour = 1;
    }
  }
  return retour;
}
#endif
