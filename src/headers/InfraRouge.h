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

//Constante de direction du robot
#define AVANT 0
#define DROITE 1
#define ARRIERE 2
#define GAUCHE 3

//Prototype des fonctions
void debutInfra();
int capterInfra();

//Fonctions
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
        followLine();
        delay(100);
        debutBoutons();
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1, 180);
        delay(500);
        followLine(); //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
        delay(100);
        forward();
        rotate(0, 180);
    }
    //Vers la droite du robot
    else if(infra == Bouton2){
        rotate(1, 90);
        followLine();
        delay(100);
        debutBoutons();
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1,180);
        delay(500);
        followLine();   //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
        delay(50);
        forward();
        rotate(1, 90);
    }
    //Vers l'arrière du robot
    else if(infra == Bouton3){
        rotate(1, 180);
        followLine();
        delay(100);
        debutBoutons();
        delay(500);
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1,180);
        followLine(); //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
        delay(50);
        forward();
    }
    //Vers la gauche du robot
    else if(infra == Bouton4){
        rotate(0, 90);
        followLine();
        delay(100);
        debutBoutons();
        // DEVRAIT AVOIR FAIT UN 180
        rotate(1,180);
        delay(500);
        followLine(); //DEVRAIT S'ARRÊTER APRÈS ÊTRE RENDU AU MILIEU
        delay(50);
        forward();
        rotate(0, 90);
    }
}

#endif