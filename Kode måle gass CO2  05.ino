
//koden importerer Wire-biblioteket og Adafruit_SGP30-biblioteket, 
//og lager deretter en forekomst av Adafruit_SGP30-klassen kalt sgp.
//Wire-biblioteket brukes til å kommunisere med I2C-enheter, mens Adafruit_SGP30-biblioteket 
//gir et sett med funksjoner for å kommunisere med SGP30-luftkvalitetssensoren, som
 //kan måle nivåene av karbondioksid (CO2) .

#include <Wire.h>
#include "Adafruit_SGP30.h"
Adafruit_SGP30 sgp;


//GetAbsoluteHumidity-funksjonen tar to flytepunktsargumenter,
// temperatur og fuktighet, og beregner den absolutte fuktigheten 
//i gram vanndamp per kubikkmeter luft. Funksjonen returnerer deretter
// den absolutte fuktigheten som et 32-bits fortegnet heltall.

//Beregningen av absolutt fuktighet er basert på
// gjeldende temperatur og 
//relativ fuktighet, og utføres i henhold til formelen:


uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) /
     (243.12f + temperature)) / (273.15f + temperature)); 
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); 
    return absoluteHumidityScaled;
}

void setup() {
  Serial.begin(9600);
  Serial.println("SGP30 et enkelt test til sensor ");

  if (! sgp.begin()){
    Serial.println("finnes ikke sensor :(");
    while (1);
  }
  Serial.print("finns nå  SGP30 serial #");
  
  // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
  //sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
}//etup()-funksjonen til en Arduino-skisse,
Serial.begin(9600); initialiserer den serielle kommunikasjonen mellom 
//Arduino og en datamaskin med en overføringshastighet på 9600 bits per sekund. //
//Dette lar skissen sende meldinger til datamaskinen for feilsøkingsformål,
 //ved å skrive ut tekst til seriemonitoren i Arduino IDE.
//(! sgp.begin()) {...} sjekker om SGP30-sensoren er til stede og fungerer som den skal. Metoden sgp.begin() initialiserer
// sensoren og setter den opp for bruk i skissen. Hvis sensoren ikke blir funnet, skriver skissen ut en feilmelding til seriemonitoren 
//og går inn i en uendelig sløyfe ved å kjøre while(1);, som får skissen til å slutte å utføre ytterligere kode.

//Hvis sensoren er vellykket initialisert, skriver skissen ut en melding til seriemonitoren som 
//indikerer at sensoren er tilkoblet og fungerer. Den siste linjen med kode Serial.print("finns nå SGP30 serienummer");
// skriver ut en melding til seriellmonitoren som indikerer at serienummeret til SGP30-sensoren er tilgjengelig. 
//Det faktiske serienummeret er ikke skrevet ut i denne kodebiten, da det er utelatt i koden.

int counter = 0;
void loop() {


  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  Serial.print("male til gass CO2 na er : "); Serial.print(sgp.eCO2); Serial.println(" ppm");

  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return;
  }
   Serial.print(" \t");
 
  delay(10000);

  counter++;
  if (counter == 30) {
    counter = 0;

   // De to første linjene erklærer to uint16_t-variabler kalt TVOC_base og eCO2_base. 
   //Disse variablene vil bli brukt til å lagre grunnlinjeavlesningene av totale flyktige 
   //organiske forbindelser (TVOC) og ekvivalente karbondioksid (eCO2)-nivåer målt av SGP30-sensoren.

Koden bruker deretter sgp.getIAQBaseline()-metoden for å hente grunnlinjeavlesningene fra SGP30-sensoren.

    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get baseline readings");
      return;
    }
    Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
    Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
  }
}
