/*
Projet S1 2019
Librairie pour le capteur infrarouge.
@auteur Pedro Maria Scoccimarro
@version 1.0 14/11/2019
*/
#ifndef InfraRouge_H_
#define InfraRouge_H_

#include "LibRobus.h"

//Definitions
#define Bouton1 -8161
#define Bouton2 -16321
#define Bouton3 -14281
#define Bouton4 -12241
#define Bouton5 -4081

int capterInfra(){
    int infra = 0;
    do{
        infra = REMOTE_read();
    }while(infra == 0);
    return infra;
}

void testTournerInfra(int infra, int direction){
    MOTOR_SetSpeed(direction, 0.1);
    delay(50);
    MOTOR_SetSpeed(direction, 0);
}

#endif