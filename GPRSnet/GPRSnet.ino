
#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SRX    7
#define STX    8
//make sure that the baud rate of SIM900 is 9600!
//you can use the AT Command(AT+IPR=9600) to set it through SerialDebug
#define BAUDRATE  19200

char http_cmd[] = "GET /robots.txt HTTP/1.1\r\nHost: httpbin.org\r\nConnection: close\r\n\r\n";
char buffer[512];

GPRS gprs(SRX, STX, BAUDRATE);

void setup(){
  int ret=0;
  gprs.checkPowerUp();
  Serial.begin(19200);
  Serial.print("(ii) Start TCP demonstration...\r\n");

  // use DHCP
  while(!gprs.init()) {
      delay(1000);
      Serial.print("(ww) Initializing...\r\n");
  }
  
  while(!gprs.isNetworkRegistered())
  {
    delay(1000);
    Serial.println("(ee) Network has not registered yet!");
  }

  delay(3000);    
  // attempt DHCP
  while(!gprs.join(F("free"))) {
      Serial.println("(ee) gprs join network error");
      delay(2000);
  }

  // successful DHCP
  Serial.print("(ii) IP Address is ");
  Serial.println(gprs.getIPAddress());

  if(!gprs.connect(TCP,"httpbin.org", 80)) {
      Serial.println("(ee) connect error");
  }else{
      Serial.println("(ii) connect server success");
  }

  Serial.println("(ii) send request...");
  ret = gprs.send(http_cmd, sizeof(http_cmd)-1);
  if(ret) {
    Serial.println("(ii) done. Now fetch");
  } else {
    Serial.println("(ee) request failed. Now fetch");
  }
  
  while (true) {
      int ret = gprs.recv(buffer, sizeof(buffer)-1);
      if (ret <= 0){
          Serial.println("(ww) gprs.recv, ret <=0...");
          break; 
      }
      buffer[ret] = '\0';
      Serial.print("(ii) Recv: ");
      Serial.print(ret);
      Serial.println(" bytes: ");
      Serial.println("(ii) response: ");
      Serial.println(buffer);
  }

  Serial.println("(ii) closing");
  gprs.close();
  Serial.println("(ii) disconnect");
  gprs.disconnect();
}

void loop(){

}
