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
  Serial.println(" | ");
  
  Serial.print("CO1: ");
  Serial.print(corrente_1);
  Serial.print("A ");
  Serial.print("PO1: ");
  Serial.print(potencia_1);
  Serial.print("W ");
  Serial.print(" | ");
  
  Serial.print("CO2: ");
  Serial.print(corrente_2);
  Serial.print("A ");
  Serial.print("PO2: ");
  Serial.print(potencia_2);
  Serial.print("W ");
  Serial.print(" | ");
  
  Serial.print("CO3: ");
  Serial.print(corrente_3);
  Serial.print("A ");
  Serial.print("PO3: ");
  Serial.print(potencia_3);
  Serial.print("W ");
  Serial.println(" | ");


  
  Serial.print("BANCO DE DADOS: ");
  Serial.println(data);
  }else{}
}
}
