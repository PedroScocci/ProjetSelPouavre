#include <LibRobus.h>
#include <headers/InfraRouge.h>
#include <headers/FonctionsSuiveur.h>
#include <headers/Servomoteur.h>

#define ROUGE 0
#define VERT 1
#define BLEU 2
#define JAUNE 3

#define BOUTONROUGE 30
#define BOUTONVERT  35
#define BOUTONJAUNE 47
#define BOUTONBLEU  41

#define APPUYER 0

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

  affichage();

  Serial.begin(9600);
  delay(100);
}

void loop() 
{ 
  //Capteur infra-rouge
  Serial.println(digitalRead(BOUTONROUGE));
  Serial.println(digitalRead(BOUTONVERT));
  Serial.println(digitalRead(BOUTONBLEU));
  Serial.println(digitalRead(BOUTONJAUNE));

  if(APPUYER == digitalRead(BOUTONROUGE))
  {
    Serial.println("Bouton Rouge");
    ecrirelcd("   Infrarouge   ","                ");
    testInfra();

    affichage();
    digitalWrite(BOUTONROUGE, 1);
  }
  //Suiveur de ligne
  if(APPUYER == digitalRead(BOUTONJAUNE))
  {
    Serial.println("Bouton Jaune");
    ecrirelcd("Suiveur de ligne","                ");
    followLine();
    
    affichage();
    digitalWrite(BOUTONJAUNE, 1);
  }
  
  //Epice
  if(APPUYER == digitalRead(BOUTONVERT))
  {
    ecrirelcd("      Epice     ","                ");
    /*SERVO_Enable(MOTEURDROITE);
    delay(100);
    SERVO_SetAngle(MOTEURDROITE, 45);
    delay(100);

    SERVO_Disable(MOTEURDROITE);
    delay(1000);

    SERVO_Enable(MOTEURGAUCHE);
    delay(100);
    SERVO_SetAngle(MOTEURGAUCHE, 45);
    delay(100);

    SERVO_Disable(MOTEURGAUCHE);
    delay(1000);

    affichage();*/
    epice(MOTEURDROITE);
    digitalWrite(BOUTONVERT, 1);
  }

  //Affichage
  if(APPUYER == digitalRead(BOUTONBLEU))
  {
    Serial.println("Bouton Bleu");
    ecrirelcd("     Hello      ","     World      ");
    
    delay(2500);
    affichage();
    digitalWrite(BOUTONBLEU, 1);
  }
  delay(50);
}