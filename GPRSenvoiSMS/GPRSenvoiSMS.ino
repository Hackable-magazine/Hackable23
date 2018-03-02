#include <OneWire.h>
#include <DallasTemperature.h>
#include <FastLED.h>
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define ONE_WIRE_BUS 2

#define LED  10
#define NUM_LEDS 1

#define SRX    7
#define STX    8
#define BAUDRATE  19200
#define NUMERO "+33600000000" // mettre votre numéro ici
#define RAPPEL "10:00"
#define TLIMITE 30.0

unsigned long precedentMillis = 0;
unsigned long precedentMillisAlarm = 0;

GPRS gprs(SRX,STX,BAUDRATE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

CRGB leds[NUM_LEDS];

void probleme() {
  leds[0] = CRGB::Red;
  FastLED.show();
}

void noprobleme() {
  leds[0] = CRGB::Green;
  FastLED.show();
}

void setup()
{
  FastLED.addLeds<APA104, LED, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
  leds[0] = CRGB::Orange;
  FastLED.show();

  Serial.begin(19200);
  Serial.println("Go go go");

  gprs.checkPowerUp();

  while(!gprs.init()) {
      delay(1000);
      Serial.println("(ee) Echec de l'initialisation !");
  }
  noprobleme();
}

//           1111111111
// 01234567890123456789
// 18/02/16,10:24:06+04
//          *****

void loop() {
  char buffer[64];
  unsigned long actuelMillis = millis();

  // 1 minute de passée ?
  if(actuelMillis - precedentMillis >= 60000) {
    precedentMillis = actuelMillis;

    // lecture température
    sensors.requestTemperatures();
    delay(200);
    double tempc = sensors.getTempCByIndex(0);
    String txttempc = String(tempc, 2);

    // récupération de date et heure du ME
    if(!gprs.getDateTime(buffer)) {
      Serial.println("(ee) Erreur lecture heure");
      probleme();
    } else {
      noprobleme();

      // Affichage moniteur série
      String dateheure = String(buffer);
      Serial.print(dateheure);
      String moniteurmessage=" : Il fait " + txttempc + " degrés ici";
      Serial.println(moniteurmessage);

      // message de service
      String heure = dateheure.substring(9,14);
      if(heure.equals(RAPPEL)) {
        while(!gprs.isNetworkRegistered()) {
          delay(1000);
          Serial.println("(ww) Pas de connexion au réseau...");
          probleme();
        }
        Serial.println("(ii) Connecté au réseau");
        noprobleme();

        String message="INFO : Il fait " + txttempc + " degres ici";

        Serial.println("(ii) Envoi du message de service...");
        if(gprs.sendSMS(NUMERO,message.c_str())) {
          Serial.println("(ii) SMS envoyé.");
        } else {
          Serial.println("(ee) Echec de l'envoi du SMS !");
          probleme();
        }
      }
      
      // dépassement de température ?
      if(tempc >= TLIMITE) {
        // 5 mn depuis la précédente alarme ?
        if(actuelMillis - precedentMillisAlarm >= 300000) {
          precedentMillisAlarm = actuelMillis;

          while(!gprs.isNetworkRegistered()) {
            delay(1000);
            Serial.println("(ww) Pas de connexion au réseau...");
            probleme();
          }
          Serial.println("(ii) Connecté au réseau");
          noprobleme();

          String Amessage="ALARME : Il fait " + txttempc + " degres ici";

          Serial.println("(ii) Envoi du message d'ALARME...");
          if(gprs.sendSMS(NUMERO,Amessage.c_str())) {
            Serial.println("(ii) SMS envoyé.");
          } else {
            Serial.println("(ee) Echec de l'envoi du SMS !");
            probleme();
          }
        }
      }
    }
  }
}

