import socket
import time
import serial
#ser = serial.Serial('/dev/ttyUSB0', 9600)

host = '192.168.10.10'
port = 9999

s= socket.socket()
s.connect((host,port))
count = 1
while True:
     # ser = serial.Serial('/dev/ttyUSB1', 9600)

      #input=ser.readline()
      #data=input.decode("utf-8")
      #print(data)
      #print(input)
      #command=input('enter your command: ')
      s.send (str.encode(str(count)))
      count += 1
      time.sleep(1)
      data = s.recv(1024)
      print(data)
      #s.send(data)
      #reply=s.recv(1024)
      #print(reply.decode('utf-8'))

s.close()
