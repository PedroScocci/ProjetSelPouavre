/*
Projet S1 2019
Librairie pour les boutons.
@auteur Pedro Maria Scoccimarro
@version 1.0 27/11/2019
*/
#include "LibRobus.h"
#include "headers/LCD.h"

//Pin des boutons
#define BOUTONROUGE 30
#define BOUTONJAUNE 35
#define BOUTONVERT  47
#define BOUTONBLEU  41

//Constante pour pressage du bouton
#define APPUYER 0
#define RECOMMENCER 1
#define FIN 2

//Varaible globale pour réponses des fonctions des boutons
int reponse = 0;

int demandeAutreEpice(){
    //Version 1
    /*ecrirelcd("Voulez-vous une ","autre epice?    ");
    delay(3000);
    ecrirelcd("Rouge = Non     ","Vert = Oui      ");*/

    //Version 2
    ecrirelcd("Plus d'epices?  ", "R = Non  V = Oui");

    reponse = 0;
    do{
        if(APPUYER == digitalRead(BOUTONROUGE)){
            reponse = FIN;
        }else if(APPUYER == digitalRead(BOUTONVERT)){
            reponse = RECOMMENCER;
        }
    }while(reponse == 0);
    
    return reponse;
}

void debutBoutons(){
    //Message de bienvenu
    ecrirelcd("Bonjour mon est ","SEL             ");
    delay(4000);
    
    do{
        //Message informatif
        ecrirelcd("Veuillez choisir","une epice       ");
        delay(4000);
        ecrirelcd("R: SEL V: POIVRE","J: SAFRAN B: AIL");
        //Choix de l'épice
        if(APPUYER == digitalRead(BOUTONROUGE)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de:","SEL             ");
            //FONCTION DES SERVOMOTEURS (DEVRAIT FAIRE UN 180)
            delay(1000);
            reponse = demandeAutreEpice();
    
        }else if(APPUYER == digitalRead(BOUTONVERT)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de:","POIVRE          ");
            //FONCTION DES SERVOMOTEURS (DEVRAIT FAIRE UN 180)
            delay(1000);
            reponse = demandeAutreEpice();

        }else if(APPUYER == digitalRead(BOUTONJAUNE)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de:","SAFRAN          ");
            //FONCTION DES SERVOMOTEURS (DEVRAIT FAIRE UN 180)
            delay(1000);
            reponse = demandeAutreEpice();

        }else if(APPUYER == digitalRead(BOUTONBLEU)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de:","AIL             ");   
            //FONCTION DES SERVOMOTEURS (DEVRAIT FAIRE UN 180)
            delay(1000);
            reponse = demandeAutreEpice();

        }
    }while(reponse != FIN);
}

