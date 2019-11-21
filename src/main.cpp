#include <LibRobus.h>
#include <headers/InfraRouge.h>
#include <headers/CapteurDistance.h>
#include <headers/FonctionsSuiveur.h>

#define ROUGE 0
#define VERT 1
#define BLEU 2
#define JAUNE 3

#define BOUTONROUGE 35
#define BOUTONJAUNE 34
#define BOUTONVERT  33
#define BOUTONBLEU  32

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
  
}

void loop() 
{
 
}