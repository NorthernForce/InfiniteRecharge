#include "Utilities/Communications.h"
#include <sstream>
#include <vector>

SocketHandler::SocketHandler() {}

zmqpp::socket SocketHandler::GetSocket() {
    zmqpp::context socketContext;
    zmqpp::socket_type typeOfSocket = zmqpp::socket_type::pair;
    zmqpp::socket socket (socketContext, typeOfSocket);

    return socket;
}

void SocketHandler::EstablishConnection(zmqpp::socket socket) {
    socket.bind("tcp://" + jetsonIP + ':' + std::to_string(port));
}

void SocketHandler::SendRequest(zmqpp::socket socket, std::string request) {
    zmqpp::message message;
    message << request;
    socket.send(message);
}

std::string SocketHandler::RecieveRequest(zmqpp::socket socket) {
    std::string recievedRequest;
    zmqpp::message request;
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