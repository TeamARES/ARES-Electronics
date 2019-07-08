import socket
import time
import serial
host = ''
port = 5560
ser = serial.Serial('/dev/ttyACM0', 9600)

#storedValue = "Yo, what's up?"


def usb(data,conn):
      print(data)
      conn.sendall(str.encode('a1 selected '))
      #ser = serial.Serial('/dev/ttyACM0', 9600)
      print(data)
      ser.write(data.encode())
      #print(data.encode())
      return
def setupServer():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print("Socket created.")
    try:
        s.bind((host, port))
    except socket.error as msg:
        print(msg)
    print("Socket bind comlete.")
    return s

def setupConnection():
    s.listen(1) # Allows one connection at a time.
    conn, address = s.accept()
    print("Connected to: " + address[0] + ":" + str(address[1]))
    return conn


def dataTransfer(conn):
    while True:
        # Receive the data
        #print('bye')
        data = conn.recv(1024) # receive the data
        data = data.decode('utf-8')
        #print(data)
        # Split the data such that you separate the command
        # from the rest of the data.
        usb(data,conn)





s = setupServer()

while True:
    try:
        conn = setupConnection()
        dataTransfer(conn)
    except:
        break
