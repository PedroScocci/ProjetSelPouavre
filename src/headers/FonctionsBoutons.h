/*
Projet S1 2019
Librairie pour les boutons.
@auteur Pedro Maria Scoccimarro
@version 1.0 27/11/2019
*/
#include "LibRobus.h"
#include "headers/LCD.h"
#include "headers/Servomoteur.h"

//Pin des boutons
#define BOUTONROUGE 30
#define BOUTONVERT  47
#define BOUTONBLEU  41
#define BOUTONJAUNE 35

//Constante pour pressage du bouton
#define APPUYER 0
#define RECOMMENCER 1
#define FIN 2

//Varaible globale pour réponses des fonctions des boutons
int reponse = 0;

int demandeAutreEpice(){
    //Version 2
    rotate(1,180);
    delay(200);
    ecrirelcd("Plus d'epices?  R = Non  V = Oui");

    reponse = 0;
    do{
        if(APPUYER == digitalRead(BOUTONROUGE)){
            reponse = FIN;
        }else if(APPUYER == digitalRead(BOUTONVERT)){
            reponse = RECOMMENCER;
        }
    }while(reponse == 0);
    
    ecrirelcd("R:SEL  V:POIVREJ:ANIS  B:THYM");
    return reponse;
}

void debutBoutons(){
    //Message de bienvenu
    ecrirelcd("Bonjour mon nom est SEL");
    delay(3000);
    
    reponse = 0;
    
    //Message informatif
    ecrirelcd("Veuillez choisir une epice");
    delay(2000);
    ecrirelcd("R: SEL V: POIVREJ: SAFRAN B: AIL");
    do{
        //Choix de l'épice
        if(APPUYER == digitalRead(BOUTONROUGE)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de: SEL");
            delay(100);
            rotate(0,180);
            delay(500);
            epice(0,100);
            delay(500);
            reponse = demandeAutreEpice();
    
        }else if(APPUYER == digitalRead(BOUTONVERT)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de: POIVRE(RIP)");
            delay(100);
            rotate(0,180);
            delay(500);
            epice(0,100);
            delay(500);
            reponse = demandeAutreEpice();

        }else if(APPUYER == digitalRead(BOUTONJAUNE)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de: SAFRAN");
            delay(100);
            rotate(1,180);
            delay(500);
            epice(1,100);
            delay(500);
            reponse = demandeAutreEpice();

        }else if(APPUYER == digitalRead(BOUTONBLEU)){
            Serial.println("Bouton Rouge");
            ecrirelcd("Distribution de: AIL");   
            delay(100);
            rotate(1,180);
            delay(500);
            epice(1,100);
            delay(500);
            reponse = demandeAutreEpice();

        }
    }while(reponse != FIN);
}

