/*
Projet S1 2019
Librairie pour le suiveur de ligne.
@auteur Pedro Maria Scoccimarro
@version 1.0 22/10/2019
*/
#ifndef FonctionsSuiveur_H_
#define FonctionsSuiveur_H_

#define PIN_SUIVEUR A7  //À CHANGER POUR LA BONNE PIN

int getIndexByRange (float voltage);

float tensionSuiveurLigne[8] =  //to do  
{
  0,
  0.66, // gauche -> jaune
  1.33, // centre -> mauve
  2.66, // droite -> bleu
  2.00, // G + C
  3.32, // G + D
  3.99, // C + D
  4.66, // G + C + D
};

float getLineValue()
{
    double analog = analogRead(PIN_SUIVEUR);
    return analog * (5.0 / 1023.0 );
}

int getTensionIndex(float voltage) {
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