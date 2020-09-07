#define BLYNK_PRINT Serial
#include "DHT.h"
#include <NTPClient.h>
#include <Ethernet.h>
#include <SPI.h>
#include <BlynkSimpleEthernet.h>
#include <EthernetUdp.h>
#define W5100_CS  10
#define SDCARD_CS 4

byte mac[] = {  0x90, 0xA2, 0xDA, 0x00, 0x73, 0xE4 }; //ethernet mac
IPAddress Ip(30,10,10,250);         
IPAddress Gateway(30,10,10,1);    
IPAddress Subnet(254, 255, 255, 0); 
EthernetClient client;
EthernetUDP Udp;
NTPClient ntp(Udp, "b.st1.ntp.br", -3 * 3600, 60000);
DHT dht = DHT(7, DHT11);
BlynkTimer timer;
unsigned int localPort = 8888; 
String a = "IoTree001";
int hora;
int minuto;
int pinoLDR = A15;   
int pinoPIR1 = 23, pinoPIR2 = 25, pinoPIR3 = 27;
int pinoRELE = 8;
int estado = analogRead(pinoLDR); 
int pir1 = 0, pir2 = 0, pir3 = 0;
float h, t;
char auth[] = "Bv_Rvrl0cYOihAEe3-piEPydia-l-IzJ";
bool bypass;

int pinoCorrente_1 = A8;  //luzes
int pinoCorrente_2 = A9;  //usb-bar
int pinoCorrente_3 = A10; //usb-bike
int pinoCorrente_4 = A11; //usb-praça
//int pinoCorrente_5 = A12; 
double corrente_1 = 0;  
double corrente_2 = 0;  
double corrente_3 = 0;  
double corrente_4 = 0;  
//double corrente_5 = 0;  
float potencia_1 = 0;
float potencia_2 = 0;
float potencia_3 = 0;
float potencia_4 = 0;
//float potencia_5 = 0;


void enviar_Blynk(){
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, estado);
  Blynk.virtualWrite(V8, corrente_1); //
  Blynk.virtualWrite(V9, potencia_1); //
  Blynk.virtualWrite(V10, corrente_2); //
  Blynk.virtualWrite(V11, potencia_2); //
  Blynk.virtualWrite(V12, corrente_3); //
  Blynk.virtualWrite(V13, potencia_3); //
  Blynk.virtualWrite(V14, corrente_4); //
  Blynk.virtualWrite(V15, potencia_4); //
 // Blynk.virtualWrite(V12, corrente_5); //
 // Blynk.virtualWrite(V13, potencia_5); //
}


BLYNK_WRITE(V1){
 int pinValue = param.asInt();
  if(pinValue == 0){
    bypass = true;
    digitalWrite(pinoRELE,HIGH);
    Serial.println("BYPASS - RELE DESLIGADO");
  }else if(pinValue == 1){
    bypass = false;
    Serial.println("bypass falso");
  }else{
    bypass = true;
    digitalWrite(pinoRELE,LOW);
    Serial.println("BYPASS - RELE LIGADO");
    }
  Serial.println(pinValue);
}

void checagemBlynk(){
  //if(Ethernet.Link){
  Serial.print("Checagem de conexão com o Blynk -> ");
  bool result = Blynk.connected();
  if(result == false){
    Serial.println("Blynk não está connectado!");
     Blynk.connect();
  }else{
    Serial.println("Blynk está conectado!");
  }
}
 
void setup(){ 
  Serial.begin(9600);
  Serial.println("IoTree 0.12");
  Ethernet.begin(mac, Ip, Gateway, Subnet);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
  }
  pinMode(SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH);
  Serial.println(Ethernet.localIP());
  Blynk.config(auth);
  Blynk.connect();
  timer.setInterval(2000L, MonitoramentoEnergia);
  timer.setInterval(5000L, enviar_Blynk);
  timer.setInterval(300000L, checagemBlynk);
  dht.begin();
  pinMode(pinoRELE, OUTPUT); 
  pinMode(pinoCorrente_1, INPUT);
  pinMode(pinoCorrente_2, INPUT);
  pinMode(pinoCorrente_3, INPUT);
  pinMode(pinoCorrente_4, INPUT);
//  pinMode(pinoCorrente_5, INPUT);
  
  bypass = false;
  Udp.begin(localPort);
  ntp.begin();//Inicia o NTP.
  ntp.forceUpdate();//Força o Update.
}                                                                                                      

void loop() {   
  debug(1);
  if(Blynk.connected()){
   Blynk.run();
  }else{}    
                                                                                                                                                                                                                                                                                                                                                                      
   hora = ntp.getHours(); 
   minuto = ntp.getMinutes(); 
  
  if (ntp.forceUpdate() == false){
   hora = 99;
   minuto = 99;
  }

  MonitoramentoEnergia();
  timer.run();
  estado = analogRead(pinoLDR);  
  h = dht.readHumidity(); 
  t = dht.readTemperature(); 
  pir1 = digitalRead(pinoPIR1);
  pir2 = digitalRead(pinoPIR2);
  pir3 = digitalRead(pinoPIR3);
  bancoEnviar();
  if(bypass == false){
    Luzes();
    } 
}
