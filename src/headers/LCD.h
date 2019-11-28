/*
Projet S1 2019
Librairie pour l'affichage de l'écran LCD.
@auteur Jean-Christophe Perreault
@version 1.0 14/11/2019
*/

#include <LiquidCrystal_I2C/LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define MAX_TAILLE_TEXTE 17

void ecrirelcd(char messagelcd1[], char messagelcd2[])
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0,0);

  for(int i=0;i<16;i++)
  {
    lcd.print(messagelcd1[i]);
  }
  
  lcd.setCursor(0,1);

  for(int j=0;j<16;j++)
  {
    lcd.print(messagelcd2[j]);
  }
}

void initialisationLCD()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();

  ecrirelcd("Bonjour         ","Mon nom est Sel ");
  delay(3000);
}

void affichage()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();

  ecrirelcd("Veuillez choisir","InfraR SL Epice ");
}