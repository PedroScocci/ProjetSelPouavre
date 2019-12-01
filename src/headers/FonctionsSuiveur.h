/*
Projet S1 2019
Librairie pour le suiveur de ligne.
@auteur Maxime Archer
@version 1.0 22/10/2019
*/
#ifndef FonctionsSuiveur_H_
#define FonctionsSuiveur_H_

#define PIN_SUIVEUR A7

int getIndexByRange (float voltage);

float tensionSuiveurLigne[8] =  //to do  
{
  0,
  0.65, // droite -> jaune
  1.31, // centre -> turquoise
  2.66, // gauche -> mauve
  1.97, // D + C
  3.32, // G + D
  3.99, // C + D
  4.66, // G + C + D
};

int testcount = 0; // a enlever

//Prototype des fonctions
float getLineValue();
int getTensionIndex(float voltage);
int getIndexByRange (float voltage);

//Fonctions
float getLineValue()
{
    double analog = analogRead(PIN_SUIVEUR);
    return analog * (5.0 / 1023.0 );
}

int getTensionIndex(float voltage) {
    // a enlever quand le suiveur est correct
    if(testcount < 100) {
        delay(20);
        testcount++;
        return 5;
    }else {
        testcount = 0;
        return 7;
    }


    for (int i = 0; i < 8; i++) {
        if(tensionSuiveurLigne[i] == voltage) {
            return i;
        } 
    }
    return getIndexByRange(voltage);
}

int getIndexByRange (float voltage) {
    if(voltage < 0 && voltage <= 0.33) {
        return 0;
    }
    if(voltage > 0.33 && voltage <= 0.995) {
        return 1;
    }
    if(voltage > 0.995 && voltage <= 1.325) {
        return 2;
    }
    if(voltage > 1.325 && voltage <= 2.33) {
        return 4;
    }
    if(voltage > 2.33 && voltage <= 2.99) {
        return 3;
    }
    if(voltage > 2.99 && voltage <= 3.65) {
        return 5;
    }
    if(voltage > 3.65 && voltage <= 4.32) {
        return 5;
    }
    return 7;
};

#endif 