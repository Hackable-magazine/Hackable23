#include <SoftwareSerial.h>

#define SRX  7
#define STX  8
#define PWR  9

SoftwareSerial GPRS(SRX, STX);

// Tampon pour la réception
unsigned char buffer[64];
// Compteur de données à traiter
int count=0;

// mise en marche Sim900
// (nécessite soudure R13)
void powerUpOrDown()
{
  digitalWrite(PWR,LOW);
  delay(1000);
  digitalWrite(PWR,HIGH);
  delay(2000);
  digitalWrite(PWR,LOW);
  //delay(3000);
}

void setup()
{
  pinMode(PWR, OUTPUT);
  GPRS.begin(19200);
  Serial.begin(19200);
  //powerUpOrDown();
}

void loop()
{
  // module vers moniteur
  if (GPRS.available()) {
    while(GPRS.available()) {
      buffer[count++]=GPRS.read();
      if(count == 64)break;
    }
    Serial.write(buffer,count);
    // mise à zéro du buffer
    memset(buffer,0,sizeof(buffer)*sizeof(unsigned char));
    count = 0;
  }
  
  // Moniteur vers module
  unsigned char tmp;
  if (Serial.available()) {
    tmp=Serial.read();
      if(tmp=='#')
        tmp=0x1A;    
    GPRS.write(tmp);
  }
}


