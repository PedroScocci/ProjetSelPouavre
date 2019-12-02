#include <LibRobus.h>
#include "headers/InfraRouge.h"

void setup()
{
  BoardInit();

  SERVO_Disable(MOTEURDROITE);
  delay(100);
  SERVO_Disable(MOTEURGAUCHE);
  delay(100);

  pinMode(INPUT_PULLUP, BOUTONROUGE);
  pinMode(INPUT_PULLUP, BOUTONJAUNE);
  pinMode(INPUT_PULLUP, BOUTONVERT);
  pinMode(INPUT_PULLUP, BOUTONBLEU);

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