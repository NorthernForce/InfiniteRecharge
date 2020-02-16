#include "utilities/Communications.h"
#include <sstream>
#include <vector>

SocketHandler::SocketHandler() {}

zmqpp::socket_t SocketHandler::GetSocket() {
    zmqpp::context_t socketContext;
    zmqpp::socket_type typeOfSocket = zmqpp::socket_type::pair;
    zmqpp::socket_t socket (socketContext, typeOfSocket);

    return socket;
}

void SocketHandler::EstablishConnection(zmqpp::socket_t socket) {
    socket.bind("tcp://" + jetsonNanoIP + ':' + std::to_string(port));
}

void SocketHandler::SendRequest(zmqpp::socket_t socket, std::string request) {
    zmqpp::message_t message;
    message << request;
    socket.send(message);
}

std::string SocketHandler::RecieveRequest(zmqpp::socket_t socket) {
    std::string recievedRequest;
    zmqpp::message_t request;
    socket.receive(request);
    request >> recievedRequest;

    return recievedRequest;
}

std::pair<std::string, double> SocketHandler::ParseRequestForData(std::string request) {
    std::vector<std::string> splitRequest;
    std::stringstream parseString(request);
    std::string aParsedValue;

    while (getline(parseString, aParsedValue, ':')) {
        splitRequest.push_back(aParsedValue);
    }
    std::string key = splitRequest[0];
    double data = atof(splitRequest[1].c_str());

    return std::make_pair(key, data);
}