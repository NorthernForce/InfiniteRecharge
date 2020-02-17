import zmq
import time
import re

class SocketHandler:
    def GetSocket(self):
        context = zmq.Context()
        return context.socket(zmq.REP)

    def EstablishConnection(self, socket):
        socket.bind("tcp://*:5800")

    def RecieveThenSend(self, socket, message):
        recievedMessage = socket.recv_string()
        socket.send_string(message)
        return recievedMessage        

    def ParseForData(self, message):
        splitMessage = re.split('[-:]', message)
        key = splitMessage[0]
        data = splitMessage[1]
        return (key, data)