/*
Projet S1 2019
Librairie pour l'affichage de l'écran LCD.
@auteur Jean-Christophe Perreault
@version 2.0 28/11/2019
*/
#ifndef LCD_H_
#define LCD_H_
#include <string.h>
#include <LiquidCrystal_I2C\LiquidCrystal_I2C.h>
#include "headers/Servomoteur.h"

LiquidCrystal_I2C lcd(0x27,16,2);
#define MAX_TAILLE_TEXTE 17

//Prototypes des fonctions
void ecrirelcd(char messagelcd[]);
void initialisationLCD();
void affichage();

//Fonctions
void ecrirelcd(char messagelcd[])
{
  lcd.init();
  lcd.backlight();
  lcd.clear();

  int i=0;
  int k=16;

  if (strlen(messagelcd)<17)
  {
    lcd.setCursor(0,0);
    while(messagelcd[i]!='\0')
    {
      lcd.print(messagelcd[i]);
      i++;
    }
  } else if (strlen(messagelcd)>17 && strlen(messagelcd)<33){

    lcd.setCursor(0,0);
    for(int j=0;j<16;j++){
      lcd.print(messagelcd[j]);
    }
    
    lcd.setCursor(0,1);
    while(messagelcd[k]!='\0')
    {
      lcd.print(messagelcd[k]);
      k++;
    }

  } else{
    lcd.setCursor(0,0);
    lcd.print("ERREUR DE TAILLE");
  }
}

void initialisationLCD()
{
  lcd.init();
  lcd.noBacklight();
  lcd.clear();
}

//menu principal
void affichage()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();

  ecrirelcd("Veuillez choisir l'epice voulue");
}
#endif