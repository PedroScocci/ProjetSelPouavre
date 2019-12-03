/*
Projet S1 2019
Librairie pour le suiveur de ligne.
@auteur Maxime Archer
@version 1.0 22/10/2019
*/
#ifndef FonctionsSuiveur_H_
#define FonctionsSuiveur_H_

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
/*
[0,0,0] = 0,0042
[X,0,0] = 2.811 (mauve)
[0,0,X] = 0.705 (Jaune)
[0,x,0] = 1.410(turquoise)
[X,X,0] = 4.213 
[0,X,X] = 2.111
[X,0,X] = 3,5
[X,X,X] = 4.908
*/

//Prototype des fonctions
float getLineValue();
int getTensionIndex(float voltage);
int getIndexByRange (float voltage);

//Fonctions
float getLineValue(int pinAnal)
{
    double analog = analogRead(pinAnal);
    return analog * (5.0 / 1023.0);
}

int getTensionIndex(float voltage)
{
    
    /*for (int i = 0; i < 8; i++) {
        if(tensionSuiveurLigne[i] == voltage) {
            return i;
        } 
    }
    */
    int iOui = 0;
    int IndexVolt = 0;
    int IndexVolt2 = 0;
    while(iOui == 0)
    {
        IndexVolt = getIndexByRange(voltage);
        delay(100);
        IndexVolt2 = getIndexByRange(voltage);
        if(IndexVolt == IndexVolt2)
        {
         iOui = 1;   
        }
    }

    return IndexVolt;
}

int getIndexByRange (float voltage) 
{
    if(voltage <= 0.33) {
        //[0,0,0]
        return 0;
    }
    else if(voltage > 0.33 && voltage <= 0.995) {
        //[0,0,X]
        return 1;
    }
    else if(voltage > 0.995 && voltage <= 1.325) {
        //[0,X,0]
        return 2;
    }
    else if(voltage > 1.325 && voltage <= 2.33) {
        //[0,X,X]
        return 3;
    }
    else if(voltage > 2.33 && voltage <= 2.99) {
        //[X,0,0]
        return 4;
    }
    else if(voltage > 2.99 && voltage <= 3.65) {
        //[X,0,X]
        return 5;
    }
    else if(voltage > 3.65 && voltage <= 4.3) {
        //[X,X,0]
        return 6;
    }
    else if(voltage > 4.3) {
        //[X,X,X]
        return 7;
    }
    else
    {
        return 8;
    }
};

#endif 