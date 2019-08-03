import serial
import time
import struct

ser = serial.Serial('/dev/ttyACM0', 9600, timeout = 1) # ttyACM1 for Arduino board
ser.flushInput()

while True:
    try:
        ser_bytes = ser.readline()
        decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
        print(decoded_bytes)
    except:
        print("Keyboard Interrupt")
        break

data=49
print(str(data))

while True:
    ser.write(str(data).encode())
    ser.flush()
    time.sleep(1)
