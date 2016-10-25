#include <SPI.h>
#include <Ethernet.h>
int ledA=2;
int sensorValue=0;

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0xB2, 0x46 };
byte ipServer[]={192,168,1,200};  
byte ipClient[]={192,168,1,9};

EthernetClient client;

void setup() {  
  Serial.begin(9600);
  pinMode(ledA,OUTPUT);
  digitalWrite(ledA, HIGH);
  Ethernet.begin(mac, ipClient);
  delay(1000);
  if (client.connect(ipServer, 8080)) {
    Serial.println("conectado");
    client.println("GET /TESIS/ HTTP/1.1");
    client.println("Host:192.168.1.200");
    client.println("Connection: keep-alive");
    client.println();
  }
  else {
    Serial.println("connection failed");
  }
}

void loop()
{
    sensorValue = analogRead(A0);
    if(sensorValue < 300)
    {
     if (client.available()) {
      client.println("GET /TESIS/sumar HTTP/1.1");
      client.println("Host:192.168.1.200");
      client.println("Connection: keep-alive");
      client.println();
      }
  }
  delay(400);
}

