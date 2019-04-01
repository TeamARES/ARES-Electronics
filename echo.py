import serial
import time
if __name__ == "__main__":
    ser = serial.Serial("COM14", 9600, timeout=0.005)
    while True:
        user_input = input("Enter key: ")
        ########## ENTER YOUR CODE HERE ############
        data_to_send = user_input.encode('utf-8')  #encoding string to bytes
        ser.write(data_to_send)                    #sending data over serial port

        ############################################
