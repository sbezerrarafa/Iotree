float vetCorrente_1[30];
float vetCorrente_2[30];
float vetCorrente_3[30];
float vetCorrente_4[30];
//float vetCorrente_5[30];

void MonitoramentoEnergia()
{
  double maior_Valor_1 = 0;
  double maior_Valor_2 = 0;
  double maior_Valor_3 = 0;
  double maior_Valor_4 = 0;
  //double maior_Valor_5 = 0;
  int tensao = 12;

 
  for(int i = 0; i < 30; i++)
  {
    vetCorrente_1[i] = analogRead(pinoCorrente_1);
    vetCorrente_2[i] = analogRead(pinoCorrente_2);
    vetCorrente_3[i] = analogRead(pinoCorrente_3);
    vetCorrente_4[i] = analogRead(pinoCorrente_4);
    //vetCorrente_5[i] = analogRead(pinoCorrente_5);
    delayMicroseconds(60);
  }  
 
  for(int i = 0; i < 30; i++)
  {
    if(maior_Valor_1 < vetCorrente_1[i])
    {
      maior_Valor_1 = vetCorrente_1[i];
    }
    
        if(maior_Valor_2 < vetCorrente_2[i])
    {
      maior_Valor_2 = vetCorrente_2[i];
    }
    
        if(maior_Valor_3 < vetCorrente_3[i])
    {
      maior_Valor_3 = vetCorrente_3[i];
    }
    
        if(maior_Valor_4 < vetCorrente_4[i])
    {
      maior_Valor_4 = vetCorrente_4[i];
    }
    
//        if(maior_Valor_5 < vetCorrente_5[i])
//    {
//      maior_Valor_5 = vetCorrente_5[i];
//    }
  }
  /*
  maior_Valor_1 = maior_Valor_1 * 0.004882812;
  corrente_1 = maior_Valor_1 - 2.5;
  corrente_1 = corrente_1 * 10.7138;
  corrente_1 = corrente_1 / 66;         //sensibilidade : 66mV/A para ACS712 30A / 185mV/A para ACS712 5A
  corrente_1 = corrente_1 / 1.41421356;
  corrente_1 = corrente_1 - 0.65;      //testar e mudar caso problema! <3
  */
  corrente_1 = (((((((maior_Valor_1 * 0.004882812)-2.5)*1000)/66)/1.41421356) -0.65)*-1); //ultimo valor correção, refazer na IoT
  corrente_2 = (((((((maior_Valor_2 * 0.004882812)-2.5)*1000)/66)/1.41421356) -0.65)*-1);
  corrente_3 = (((((((maior_Valor_3 * 0.004882812)-2.5)*1000)/66)/1.41421356) -0.65)*-1);
  corrente_4 = (((((((maior_Valor_4 * 0.004882812)-2.5)*1000)/66)/1.41421356) -0.65)*-1);
  //corrente_5 = (((((((maior_Valor_5 * 0.004882812)-2.5)*1000)/66)/1.41421356) -0.65*-1));
 
  potencia_1 = corrente_1 * tensao;
  potencia_2 = corrente_2 * tensao;
  potencia_3 = corrente_3 * tensao;
  potencia_4 = corrente_4 * tensao;

  if(potencia_1 < 0)
  {
    potencia_1 = potencia_1*-1;
  }
  if(potencia_2 < 0)
  {
    potencia_2 = potencia_2*-1;
  }
  if(potencia_3 < 0)
  {
    potencia_3 = potencia_3*-1;
  }
  if(potencia_4 < 0)
  {
    potencia_4 = potencia_4*-1;
  }


}
