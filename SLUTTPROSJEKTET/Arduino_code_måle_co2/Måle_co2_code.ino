#include "SparkFun_SGP30_Arduino_Library.h" // Inkluder biblioteket: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // Bredde på OLED-skjermen i piksler
#define SCREEN_HEIGHT 64    // Høyde på OLED-skjermen i piksler
#define OLED_RESET     4    // Reset-pinne # (eller -1 hvis du deler Arduino reset-pinne)
#define SCREEN_ADDRESS 0x3C // 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SGP30 mySensor; // Opprett et objekt av SGP30-klassen

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306-allokering mislyktes"));
    for (;;); // Avslutt, loop for alltid
  }
  display.clearDisplay();

  // Initialiser sensoren
  if (mySensor.begin() == false)
  {
    Serial.println("Ingen SGP30 oppdaget. Sjekk tilkoblingene.");
    while (1);
  }
  // Initialiserer sensoren for luftkvalitetsavlesninger
  // measureAirQuality bør kalles med ett sekunds mellomrom etter et kall til initAirQuality
  mySensor.initAirQuality();
}

void loop()
{
  // De første femten avlesningene vil være
  // CO2: 400 ppm  
  delay(1000); // Vent 1 sekund
  // Mål CO2 nivåer
  mySensor.measureAirQuality();
  Serial.print("CO2: ");
  Serial.print(mySensor.CO2);
 
  Serial.println(" ppb");

  display.clearDisplay(); // Tøm skjermen

  display.setCursor(0, 0); // OLED-skjerm
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Mohamad H "); // Vis "Mohamad H " øverst på skjermen

  display.setCursor(0, 25); // OLED-skjerm
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("CO2: ");
  display.print(mySensor.CO2);
  display.print(" ppm"); // Vis CO2-verdien under prosjektnavnet

  display.display(); // Oppdater skjermen med innholdet som er tegnet
}
