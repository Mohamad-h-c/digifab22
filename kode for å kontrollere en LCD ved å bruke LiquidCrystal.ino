

//Dette er en kode for å kontrollere en LCD ved å bruke "LiquidCrystal"-biblioteket:
//Den første linjen "#include <LiquidCrystal.h>" inkluderer overskriftsfilen for LiquidCrystal-biblioteket,
// som inneholder funksjoner og konstanter for å kontrollere LCD-skjermen.
//Den neste linjen initialiserer variabler med pin-numre som er koblet til LCD-skjermen.
// Nærmere bestemt representerer rs, en, d4, d5, d6 og d7 pinnene for registervalg-, aktiverings- og datalinjene på LCD-skjermen.

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Den første linjen "lcd.begin(16, 2);" initialiserer LCD-skjermen til en 16x2 tegnskjerm med 16 kolonner og 2 rader.
//Den andre linjen "lcd.print("Oblig 3, DIGIFAB");" skriver ut strengen "Oblig 3, DIGIFAB" til LCD-skjermen.
//Den tredje linjen "delay(1000);" forårsaker en 1-sekunds forsinkelse før programmet går 
//videre til neste kodelinje. Dette gjøres ved å bruke "delay"-funksjonen som pauser programmet i 
//det angitte antall millisekunder (i dette tilfellet 1000 millisekunder eller 1 sekund).

void setup() {
  lcd.begin(16, 2);
  lcd.print("Oblig 3 ,DIGIFAB");
  delay(1000);
}

void loop() {
  
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

  
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    lcd.scrollDisplayRight();
    delay(150);
  }

 
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(150);
  }

  delay(1000);

}

//Til slutt er det en forsinkelse på 1000 millisekunder før programmet går 
//tilbake til begynnelsen av loopen og gjentar hele rullesekvensen.
//Totalt sett vil denne løkken rulle teksten på LCD-skjermen til venstre, 
//deretter til høyre og deretter tilbake til venstre, med en forsinkelse 
//på 150 millisekunder mellom hver rulling og en forsinkelse
// på 1000 millisekunder mellom hver sekvens.
