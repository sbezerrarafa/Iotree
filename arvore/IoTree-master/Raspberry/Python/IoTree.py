import serial
import time
#import datetime
#import ipapi
import json
import schedule
#import requests
#from threading import Timer

cod = -1
temperatura = -1
umidade = -1

def receber_dados_arduino():
    global serialArduino
    global cod
    global temperatura
    global umidade

    try:
        # port = "/dev/ttyACM0"
        # s1 = serial.Serial(port, 9600)
        # s1.flush()
        # if s1.inWaiting() > 0:
        #     serialArduino = s1.readline()
        resp = json.loads(serialArduino)
        cod = resp['cod']
        temperatura = resp['temperatura']
        umidade = resp['umidade']

    except:
        print("Erro de comunicação com o arduino")

#def enviar_dados_arduino(mensagem):
def enviar_dados_arduino():
    try:
        port = "/dev/ttyACM0"
        s1 = serial.Serial(port, 9600)
        msgarduino = '{"mensagem":%s}' %mensagem
        s1.write(str(msgarduino))
        print("foi enviado para o arduino: " + str(msgarduino))
    except:
        print("Erro de comunicação com o arduino")

def enviar_servidor_iotree():
    URL = ""

serialArduino = '''dawda{
  "cod": "1",
  "temperatura": "29.3",
  "umidade": "85.5",
  "ldr": "34",
  "corrente1": "5",
  "corrente2": "9",
  "corrente3": "12"
}'''

schedule.every(1).days.at("05:00").do(enviar_dados_arduino) #'modonoturnodesligado'
schedule.every(1).days.at("22:00").do(enviar_dados_arduino) #'modonoturnoligado'

while True:
    #schedule.run_pending() # executa os eventos marcados

    receber_dados_arduino() # o tempo de envio de uma informação do arduino para o rasp depende do código do arduino.

    time.sleep(1)
    print(cod)
    print(temperatura)
    print(umidade)
    while True:
        pass