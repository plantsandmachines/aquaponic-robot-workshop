/*
       Automatic Aquaponic Robot, 2015, Innovative Citizen, plants & machines
       
       ----------------------------------------------------------------------------
       "THE BEER-WARE LICENSE" (Revision 42):
       <martin@plantsandmachines.de> wrote this file. As long as you retain this notice you
       can do whatever you want with this stuff. If we meet some day, and you think
       this stuff is worth it, you can buy me a beer in return Martin Breuer
       ----------------------------------------------------------------------------

*/
#include "DHT.h"                    // Einbinden der DHT sensor library

#define tempSensorPin 3     // Bitte die 3 durch die Nummer des Pins ersetzen, an dem die Datenleitung eures Temperatur/Feuchtigkeits Sensors haengt
#define lightSensorPin 9       // Bitte die 9 durch die Nummer des analog Pins ersetzen, an dem die Datenleitung eures Temperatur/Feuchtigkeits Sensors haengt
#define relayChA 5                // Bitte die 5 durch die Nummer des Pins ersetzen, an dem die Steuerleitungen eures relayboards haengt, welche die Pumpe schaltet
#define relayChB 6                // Bitte die 6 durch die Nummer des Pins ersetzen, an dem die andere der beiden Steuerleitungen eures relayboards haengt

#define intervall 30                 // Zeit in Minuten zwischen dem Giessen
#define duration 10                // Zeit in Sekunden in der die Pumpe an ist. Wenn der Wasserstand am ende des Giessens zu niedrig ist - erhoeht diese Zahl (vorsicht, dass nichts ueberlaeuft)
#define lichtNacht 10             // Die Lichtmenge unter welcher mit dem Giessen aufgehoert werden soll. Schau dir an, welche Lichtmenge dein Roboter Nachts misst und
                                                 // ersetze die 10 mit der Gemessenen Lichtmenge

#define sensorTyp DHT11    // Wir benutzen einen Temperatursensor des Typs DHT11

DHT dht(tempSensorPin, sensorTyp);

float temperatur, luftfeuchte = 0;
int licht = 0;
unsigned long counter = 0;

void setup ()
{
  // Setup wird genau einmal Ausgefuehrt, wenn ihr den Micro Controller mit Strom versorgt
  pinMode(relayChA, OUTPUT);
  pinMode(relayChB, OUTPUT);
  pinMode(tempSensorPin, INPUT);
  pinMode(lightSensorPin, INPUT);
  digitalWrite(lightSensorPin, HIGH); // pullup resistor anschalten
   
  Serial.begin(9600);
  Serial.println("Hello, anybody there? I am Robot, I will keep your plants happy!");
  Serial.println(); // zeilenumbruch fuer bessere lesbarkeit
  
  dht.begin();
}

void loop ()
{
  // Loop wird staendig wiederholt, solange der Micro Controller Strom hat
  
  // Sensoren Auslesen und ueber Serial ausgeben
  temperatur = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperatur);
 
  luftfeuchte = dht.readHumidity();
  Serial.print("Luftfeuchte: ");
  Serial.println(luftfeuchte);
  
  licht  = analogRead(lightSensorPin);
  Serial.print("Lichtmenge: ");
  Serial.println(licht);
  
  // Fluten des Growbeds, wenn Tag und letztes Giessen so lange her wie in intervall gesetzt
  if (licht > lichtNacht && counter >= intervall*60)
  {
    Serial.println("Starting Flood Cycle");
    digitalWrite(relayChA, HIGH); 
    for (int i = 0; i <= duration; i++)
    {
      Serial.print("Flooding done in: ");
      Serial.print(duration-i);
      Serial.println(" sec");
      delay(1000);
    }
    digitalWrite(relayChA, LOW);
    Serial.println("Draining Growbed");
    counter = 0;   
  }
  
  // Resetten des Counters in der Nacht
  else if (licht <= lichtNacht && counter >= intervall*60)
  {
    counter = 0;
  }
  
  // In jedem loop in dem nicht Gegossen wird, den Counter erhoehen
  else
  {
    ++counter;
  }
  
  delay(1000); // nach jedem loop eine sec warten... wir haben zeit, pflanzen sind nicht so schnell
                         // unbedingt auf einer sec lassen, sonst stimmt der pumpen intervall nicht mehr
                         
  Serial.println(); // Zeilenumbruch fuer bessere lesbarkeit
}
