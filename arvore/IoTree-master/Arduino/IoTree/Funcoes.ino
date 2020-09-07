unsigned long periodo_luzes = 5000; // 10 minuto = 600000
unsigned long time_luzes    = 0;

void Luzes()
{
  if(millis() >  time_luzes + periodo_luzes)
  {
    time_luzes = millis();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    //if(hora > 6 && (hora <= 21 && minuto <= 30))
    if(hora > 6 && hora <=22)
    {
        if(estado >= 500)
        {
          digitalWrite(pinoRELE,LOW);
          Serial.println("LDR ALTO -> RELE LIGADO -> LUZ LIGADA");
        }
        else if(estado <= 400)
        {
          digitalWrite(pinoRELE,HIGH);
          Serial.println("LDR BAIXO -> RELE DESLIGADO -> LUZ DESLIGADA");
        }

          
    }
    //else if(hora < 25 && (hora <= 6 || (hora >= 21 && minuto > 30)))
    else if(hora < 25 && (hora <= 6 || hora > 22))
    {
        if(pir1 == 1 || pir2 == 1 || pir3 == 1)
        {
          digitalWrite(pinoRELE,LOW);
          Serial.println("MOVIMENTO DETECTADO -> RELE LIGADO -> LUZ LIGADA");
        }
        else
        {
          digitalWrite(pinoRELE,HIGH);
          Serial.println("MOVIMENTO NÃO DETECTADO -> RELE DESLIGADO -> LUZ DESLIGADA");
        }
    }
    else if(hora == 99)
    { // FUNCIONAR SEM HORA
      if(estado >= 500)
        {
          digitalWrite(pinoRELE,LOW);
          Serial.println("LDR ALTO -> RELE LIGADO -> LUZ LIGADA");
          }
          else if(estado <= 400)
          {
          digitalWrite(pinoRELE,HIGH);
          Serial.println("LDR BAIXO -> RELE DESLIGADO -> LUZ DESLIGADA");
          }
    }
  }
}
 
