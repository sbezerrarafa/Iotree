int valor;

unsigned long periodo_debug = 5000; // 1 minuto = 60000
unsigned long time_debug    = 0;

void debug(int valor){
  if(millis() >  time_debug + periodo_debug){
    time_debug = millis();
  if(valor == 1){
  Serial.println("--------------------------//---------------------------");
  Serial.print("VALOR LDR: ");
  Serial.print(estado);
  Serial.print(" | ");
  Serial.print("UMIDADE: ");
  Serial.print(h);
  Serial.print(" | ");
  Serial.print("TEMPERATURA: ");
  Serial.print(t);
  Serial.print(" | ");
  Serial.print("HORA: ");
  Serial.print(hora);
  Serial.print(" | ");
  Serial.print("MINUTO: ");
  Serial.print(minuto);
  Serial.print(" | ");
  Serial.print("MOVIMENTO1: ");
  Serial.print(pir1);
  Serial.print(" | ");
  Serial.print("MOVIMENTO2: ");
  Serial.print(pir2);
  Serial.print(" | ");
  Serial.print("MOVIMENTO3: ");
  Serial.print(pir3);
  Serial.println(" | ");

  Serial.print("ENERGIA SOLAR: ");
 // Serial.print("CO1: ");
  Serial.print(corrente_1);
  Serial.print("A ");
  Serial.print("ABSORVENDO: ");
  Serial.print(potencia_1);
  Serial.print("W ");
  Serial.print(" | ");
  
  Serial.print("USB-PETALA MENOR: ");
  //Serial.print("CO2: ");
  Serial.print(corrente_2);
  Serial.print("A ");
  Serial.print("CONSUMO: ");
  Serial.print(potencia_2);
  Serial.print("W ");
  Serial.print(" | ");

  Serial.print("USB-PETALA MEDIA: ");
  //Serial.print("CO3: ");
  Serial.print(corrente_3);
  Serial.print("A ");
  Serial.print("CONSUMO: ");
  Serial.print(potencia_3);
  Serial.print("W ");

  Serial.print("USB-PETALA MAIOR: ");
  //Serial.print("CO4: ");
  Serial.print(corrente_4);
  Serial.print("A ");
  Serial.print("CONSUMO: ");
  Serial.print(potencia_4);
  Serial.print("W ");
  Serial.println(" | ");
  /*
    Serial.print("CO5: ");
  Serial.print(corrente_5);
  Serial.print("A ");
  Serial.print("PO5: ");
  Serial.print(potencia_5);
  Serial.print("W ");
  Serial.println(" | ");
  */
  Serial.print("RAW: ");
  
  //Serial.print("BANCO DE DADOS: ");
  //Serial.println(data);
  }else{}
}
}
