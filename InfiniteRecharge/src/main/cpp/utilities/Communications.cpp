#include "utilities/Communications.h"
#include <sstream>
#include <vector>

SocketHandler::SocketHandler() {}

zmqpp::socket_t SocketHandler::MakeSocket() {
    zmqpp::context_t socketContext;
    zmqpp::socket_type typeOfSocket = zmqpp::socket_type::pair;
    zmqpp::socket_t socket (socketContext, typeOfSocket);

    return socket;
}

void SocketHandler::EstablishConnection(zmqpp::socket_t socket) {
    socket.bind("tcp://" + jetsonNanoIP + ':' + std::to_string(port));
}

void SocketHandler::Send(zmqpp::socket_t socket, std::string request) {
    zmqpp::message_t message;
    message << request;
    socket.send(message);
}

std::string SocketHandler::Recieve(zmqpp::socket_t socket) {
    std::string recievedRequest;
    zmqpp::message_t request;
    socket.receive(request);
    request >> recievedRequest;

    return recievedRequest;
}

std::pair<std::string, double> SocketHandler::ParseForData(std::string message) {
    std::vector<std::string> splitMessage;
    std::stringstream parseString(message);
    std::string aParsedValue;

    while (getline(parseString, aParsedValue, ':')) {
        splitMessage.push_back(aParsedValue);
    }
    std::string key = splitMessage[0];
    double data = atof(splitMessage[1].c_str());

    return std::make_pair(key, data);
}