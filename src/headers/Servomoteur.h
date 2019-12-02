#ifndef Servomoteur_H_
#define Servomoteur_H_

#include <LibRobus.h>

#define MOTEURDROITE 0
#define MOTEURGAUCHE 1

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
        SERVO_SetAngle(moteur, 81);
        delay(1000);
    }
    else if (moteur == MOTEURGAUCHE)
    {
        //Ouvrir la trape.
        SERVO_SetAngle(moteur, 45);

        //Temps d'ouverture en milisecondes.
        delay(temps);

        //Fermer la trape
        SERVO_SetAngle(moteur, 91);
        delay(1000);
    }

    
    
    //Désactiver le moteur.
    SERVO_Disable(moteur);
    delay(1000);
}

#endif 