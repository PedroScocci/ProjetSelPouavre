/*
Projet S1 2019
Librairie pour la distribution des épices.
@auteur Jérémy Chenard
@version 2.0 28/11/2019
*/
#ifndef Servomoteur_H_
#define Servomoteur_H_

#include <LibRobus.h>

#define MOTEURDROITE 0
#define MOTEURGAUCHE 1
#define POSINITDROITE 81
#define POSINITGAUCHE 91

//Fonction
void epice(int moteur, int temps)
{
    SERVO_Enable(moteur);
    delay(100);
    
    if(moteur == MOTEURDROITE)
    {
        //Ouvrir la trape.
        SERVO_SetAngle(moteur, 155);
        
        //Temps d'ouverture en milisecondes.
        delay(temps);

        //Fermer la trape
        SERVO_SetAngle(moteur, POSINITDROITE);
        delay(1000);
    }
    else if (moteur == MOTEURGAUCHE)
    {
        //Ouvrir la trape.
        SERVO_SetAngle(moteur, 45);

        //Temps d'ouverture en milisecondes.
        delay(temps);

        //Fermer la trape
        SERVO_SetAngle(moteur, POSINITGAUCHE);
        delay(1000);
    }

    //Désactiver le moteur.
    SERVO_Disable(moteur);
    delay(1000);
}

#endif 