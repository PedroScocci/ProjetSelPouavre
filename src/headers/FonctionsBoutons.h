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

//Prototypes des fonctions
void debutBoutons();
int demandeAutreEpice();

//Fonctions
void debutBoutons(){
    //Message de bienvenu
    ecrirelcd("Bonjour mon nom est SEL");
    delay(1500);
    
    reponse = 0;
    
    //Message informatif
    ecrirelcd("Veuillez choisirune epice");
    delay(2000);
    ecrirelcd("R:SEL     J:ANISV:POIVRE  B:THYM");
    do{
        //Choix de l'épice
        if(APPUYER == digitalRead(BOUTONROUGE)){
            ecrirelcd("Distribution de: SEL");
            delay(100);
            rotate(0,180);
            delay(500);
            epice(0,100);
            delay(500);
            reponse = demandeAutreEpice();
    
        }else if(APPUYER == digitalRead(BOUTONVERT)){
            ecrirelcd("Distribution de: POIVRE (RIP)");
            delay(100);
            rotate(0,180);
            delay(500);
            epice(0,100);
            delay(500);
            reponse = demandeAutreEpice();

        }else if(APPUYER == digitalRead(BOUTONJAUNE)){
            ecrirelcd("Distribution de: ANIS");
            delay(100);
            rotate(1,180);
            delay(500);
            epice(1,100);
            delay(500);
            reponse = demandeAutreEpice();

        }else if(APPUYER == digitalRead(BOUTONBLEU)){
            ecrirelcd("Distribution de: THYM");   
            delay(100);
            rotate(1,180);
            delay(500);
            epice(1,100);
            delay(500);
            reponse = demandeAutreEpice();

        }
    }while(reponse != FIN);
    ecrirelcd("");
}

int demandeAutreEpice(){
    rotate(1,180);
    delay(200);
    ecrirelcd("Plus d'epices?  R = Non  V = Oui");

    reponse = 0;
    do{
        if(APPUYER == digitalRead(BOUTONROUGE)){
            reponse = FIN;
        }else if(APPUYER == digitalRead(BOUTONVERT)){
            ecrirelcd("R:SEL     J:ANISV:POIVRE  B:THYM");
            reponse = RECOMMENCER;
        }
    }while(reponse == 0);

    return reponse;
}