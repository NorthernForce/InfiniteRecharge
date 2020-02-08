#include <zmqpp.hpp>

class SocketHandler{
    public:

    zmqpp::socket GetSocket(self){
        context = zmq.Context();

        return context.socket(zmq.REQ);
    }
    zmqpp::socket EstablishConnection(self, socket){
        socket.bind("tcp://localhost:5555");
    }
    zmqpp::socket SendRequest(self, socket, request) {
        std::cout << "Sending message: {}..." << std::endl .format(request);
        socket.send_string(request);
    }
    zmqpp::message RecieveMessage(self, socket) {
        recievedMessage = socket.recv_string();                      
        std::cout << "Recieved message: {}" << std::endl .format(recievedMessage);
        return recievedMessage;
    }
    void ParseMessageForData(self, message){
        splitMessage = re.split('[-:]', message);
        key = splitMessage[0];
        data = splitMessage[1];
        return (key, data);
    }
}
