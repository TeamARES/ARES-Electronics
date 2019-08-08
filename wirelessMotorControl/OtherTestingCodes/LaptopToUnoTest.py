import serial
import time
###################ARDUINO SERIAL OBJECT#################################################
serialPortMac = '/dev/tty.usbmodem14101'
serialPortPi = '/dev/ttyACM0'
arduinoSerial = serial.Serial(serialPortMac, 9600, timeout = 1)

def processDataToArduino(data):
    arduinoSerial.write(str(data).encode())

def makeDataWhatArduinoSent(data):
    return data[2:len(data)-5]

gotPrevData = 1

#First time send now:
processDataToArduino('1,1001,1002,1003,1004,1005,1006');
time.sleep(2)
processDataToArduino('1,1001,1002,1003,1004,1005,1006');

while True:
    data1 = '1,1001,1002,1003,1004,1005,1006'
    data2 = '1'
    data3 = '1,2'
    print("Sending:" + data1)

    #print(gotPrevData)
    processDataToArduino(data1)
    #gotPrevData = 0;

    while arduinoSerial.inWaiting() < 1:
        pass
    
    serialData = str(arduinoSerial.readline())
    if(len(serialData) > 2):
        print(serialData+" length = "+str(len(serialData)))
        print(makeDataWhatArduinoSent(serialData))
        #gotPrevData = 1;



