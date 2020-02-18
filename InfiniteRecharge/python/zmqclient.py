import zmq
import time
import re

class SocketHandler:
    def GetSocket(self):
        context = zmq.Context()
        return context.socket(zmq.REQ)

    def EstablishConnection(self, socket):
        socket.connect("tcp://localhost:5555")

    def SendRequest(self, socket, request):
        print("Sending message: {}...".format(request))
        socket.send_string(request)

    def RecieveMessage(self, socket):
        recievedMessage = socket.recv_string()
        print("Recieved message: {}".format(recievedMessage))
        return recievedMessage

    def ParseMessageForData(self, message):
        splitMessage = re.split('[-:]', message)
        key = splitMessage[0]
        data = splitMessage[1]
        return (key, data)