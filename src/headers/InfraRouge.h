/*
Projet S1 2019
Librairie pour le capteur infrarouge.
@auteur Pedro Maria Scoccimarro
@version 1.0 14/11/2019
*/
#ifndef InfraRouge_H_
#define InfraRouge_H_

#include "LibRobus.h"
#include "headers/Movements.h"
#include "headers/FonctionsBoutons.h"

//Definitions
#define Bouton1 -8161
#define Bouton2 -16321
#define Bouton3 -14281
#define Bouton4 -12241
#define Bouton5 -4081

//Constante de direction du robot
#define AVANT 0
#define DROITE 1
#define ARRIERE 2
#define GAUCHE 3

//Variable globale
//int *infra = new int;

/*void delete_infra(){
    //désalocation de la mêmoire du pointeur infra
    delete infra;
    infra = NULL;
}*/

void capterInfra(int* infra){
    do{
        *infra = REMOTE_read();
        delay(50);
    }while(*infra == 0);
}

int capterInfra2(){
    int infra = 0;
    do{
        infra = REMOTE_read();
        delay(50);
    }while(infra == 0);
    return infra;
}

void debutInfra(){
    //initialisation du pointeur infra
    int infra = 0;

    //Captage du rayon infrarouge
    infra = capterInfra2();
    //Vers la place devant le robot
    if(infra == Bouton1){
        //followLine();
        debutBoutons();
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1, 180);
        delay(1000);
        //followLine(); //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
        rotate(0, 180);
    }
    //Vers la droite du robot
    else if(infra == Bouton2){
        rotate(1, 90);
        //followLine();
        debutBoutons();
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1,180);
        delay(1000);
        //followLine();   //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
        rotate(1, 90);
    }
    //Vers l'arrière du robot
    else if(infra == Bouton3){
        rotate(1, 180);
        //followLine();
        debutBoutons();
        delay(1000);
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1,180);
        
        //followLine(); //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
    }
    //Vers la gauche du robot
    else if(infra == Bouton4){
        rotate(0, 90);
        //followLine();
        debutBoutons();
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1,180);
        delay(1000);
        //followLine(); //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
        rotate(0, 90);
    }
}


//TESTS DE L'AUDIT #2
void test360Infra(){
    rotate(1,360);
    rotate(0,360);
}

void testInfra(){
    int infra=0;
    do
    { 
        infra = capterInfra2();
        Serial.print(infra);
        
        if (infra == Bouton1)
        {
            LiquidCrystal_I2C lcd(0x27,16,2);
            lcd.init();
            lcd.backlight();
            lcd.clear();

            ecrirelcd("Test infra");
        }
        else if (infra == Bouton2)
        {
            MOTOR_SetSpeed(0, 0.15);
            MOTOR_SetSpeed(1, 0.15);
            infra = 0;
            do{
                infra = capterInfra2();
                delay(10);
            }while(infra != Bouton2);
            MOTOR_SetSpeed(0, 0);
            MOTOR_SetSpeed(1, 0);
        }
        else if (infra == Bouton3)
        {
            test360Infra();
        }
    }while(infra != Bouton5);
    //delete_infra();
}

#endif