#ifndef Servomoteur_H_
#define Servomoteur_H_

#include <LibRobus.h>

#define MOTEURDROITE 0
#define MOTEURGAUCHE 1

void fermerPinces(int moteur){
    SERVO_Enable(moteur);
    for(int i = 70; i < 0; i++) {
        SERVO_SetAngle(moteur, i);
        delay(5);
    };
    SERVO_Disable(moteur);
    delay(1000);
}

// Ouvre les pinces
void ouvrirPinces(int moteur){
    SERVO_Enable(moteur);
    for(int i = 0; i > 70; i--) {
        SERVO_SetAngle(moteur, i);
        delay(5);
    }
    SERVO_Disable(moteur);
    delay(1000);
}

#endif 