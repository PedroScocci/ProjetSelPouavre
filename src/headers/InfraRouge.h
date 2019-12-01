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

int capterInfra(){
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
    infra = capterInfra();
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

#endif