
#include <SPI.h>
#include <Ethernet.h>
int ledIr =8;
int ledA=7;
int sensorValue =0;


byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0xB2, 0x46 };

byte ipServer[]={192,168,1,200};  // numeric IP for Google (no DNS)



byte ipClient[]={192,168,1,9};


EthernetClient client;

void setup() {
  
  Serial.begin(9600);
  pinMode(ledIr, OUTPUT);
  pinMode(ledA,OUTPUT);
  digitalWrite(ledIr, HIGH);



  Ethernet.begin(mac, ipClient);
  
 
  delay(1000);
  Serial.println("conectando");
 
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
     digitalWrite(ledA,HIGH);
     if (client.available()) {

      client.println("GET /TESIS/sumar HTTP/1.1");
      client.println("Host:192.168.1.200");
      client.println("Connection: keep-alive");
      client.println();
    }
    
  }else{
    digitalWrite(ledA,LOW);
  }
  delay(400);
 


 
}

