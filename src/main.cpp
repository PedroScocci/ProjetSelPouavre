#include <LibRobus.h>
#include "headers/InfraRouge.h"
#include "headers/CapteurDistance.h"
#include "headers/FonctionsSuiveur.h"
#include "headers/CapteurDistance.h"

bool done = false;
int i = 0;

void AvanceToutDroit(int distance)
{
  //Réinitialisation des encodeurs.
  ENCODER_Reset(0);
  ENCODER_Reset(1);
  
  //Initialisation des variables.
  int pulse=0;
  int encodeur=0;
  float speed = 0;

  //Calculer le nombre de pulse par cm.
  pulse=134*distance;

   //Tant que le moteur gauche n'a pas atteint le nombre de pulse voulu. 
  while (encodeur < pulse)
  { 
    speed += 0.1;
    if (speed > maxSpeed) speed = maxSpeed;
    currentSpeed = speed;

    pid(currentSpeed);
   
    delay(50);

    encodeur = ENCODER_Read(0);
  }
  decelerate();
}

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

  //affichage();

  Serial.begin(9600);
  delay(100);
}

void loop() 
{ 
  debutInfra();
}