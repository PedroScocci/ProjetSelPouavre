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

  pinMode(BOUTONROUGE, INPUT_PULLUP);
  pinMode(BOUTONJAUNE, INPUT_PULLUP);
  pinMode(BOUTONVERT, INPUT_PULLUP);
  pinMode(BOUTONBLEU, INPUT_PULLUP);

  pinMode(PIN_SUIVEUR1, INPUT);
  pinMode(PIN_SUIVEUR2, INPUT);
  pinMode(PIN_SUIVEUR3, INPUT);

  initialisationLCD();

  delay(100);
}

void loop() 
{ 
  debutInfra();
}