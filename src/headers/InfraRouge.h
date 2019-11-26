/*
Projet S1 2019
Librairie pour le capteur infrarouge.
@auteur Pedro Maria Scoccimarro
@version 1.0 14/11/2019
*/
#ifndef InfraRouge_H_
#define InfraRouge_H_

#include "LibRobus.h"
#include <headers/LCD.h>
#include <headers/Movements.h>

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
        delay(50);
    }while(infra == 0);
    return infra;
}

void test360Infra(){
    rotate(1,360);
    rotate(0,360);
}

void testInfra(){
    int infra;
    do
    { 
        infra = capterInfra();
        Serial.print(infra);
        if (infra == Bouton1)
        {
            LiquidCrystal_I2C lcd(0x27,16,2);
            lcd.init();
            lcd.backlight();
            lcd.clear();

            ecrirelcd("Test            ", "Infra           ");
        }
        else if (infra == Bouton2)
        {
            MOTOR_SetSpeed(0, 0.15);
            MOTOR_SetSpeed(1, 0.15);
            infra = 0;
            do{
                infra = capterInfra();
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
}

#endif