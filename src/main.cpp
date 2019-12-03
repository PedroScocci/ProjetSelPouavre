#include <LibRobus.h>
#include "headers/InfraRouge.h"

void setup()
{
  BoardInit();

  //Fermer les trapes.
  SERVO_Enable(MOTEURDROITE);
  delay(10);
  SERVO_Enable(MOTEURGAUCHE);
  delay(10);
  SERVO_SetAngle(MOTEURDROITE, POSINITDROITE);
  delay(100);
  SERVO_SetAngle(MOTEURGAUCHE, POSINITGAUCHE);
  delay(100);
  SERVO_Disable(MOTEURDROITE);
  delay(10);
  SERVO_Disable(MOTEURGAUCHE);
  delay(10);

  pinMode(INPUT_PULLUP, BOUTONROUGE);
  pinMode(INPUT_PULLUP, BOUTONJAUNE);
  pinMode(INPUT_PULLUP, BOUTONVERT);
  pinMode(INPUT_PULLUP, BOUTONBLEU);

  pinMode(INPUT, PIN_SUIVEUR1);
  pinMode(INPUT, PIN_SUIVEUR2);
  pinMode(INPUT, PIN_SUIVEUR3);

  digitalWrite(BOUTONROUGE, 1);
  digitalWrite(BOUTONBLEU, 1);
  digitalWrite(BOUTONVERT, 1);
  digitalWrite(BOUTONJAUNE, 1);

  initialisationLCD();

  delay(100);
}

void loop() 
{ 
  debutInfra();
}