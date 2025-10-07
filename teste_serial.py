import serial
import time

# Configura a porta serial (troque 'COM3' pela porta do seu Arduino/ESP32)
ser = serial.Serial('COM14', 9600, timeout=1)
def enviar_G():
    ser.write(b'G')
    data = ser.readline().decode('ascii').strip()
    return data

def enviar_O():
    ser.write(b'O')
    data = ser.readline().decode('ascii').strip()
    return data

def enviar_T():
    ser.write(b'T')
    data = ser.readline().decode('ascii').strip()
    return data

time.sleep(2)  # espera a conexão estabilizar

# Envia a letra G
#enviar_G()
#enviar_O()
enviar_T()

print("Letra G enviada pela serial!")

ser.close()
