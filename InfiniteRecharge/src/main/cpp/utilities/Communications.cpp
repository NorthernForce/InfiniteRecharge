#include "utilities/Communications.h"
#include <sstream>
#include <vector>

zmqpp::socket_t SocketHandler::MakeSocket(zmqpp::socket_type typeOfSocket=zmqpp::socket_type::pair) {
    zmqpp::context_t socketContext;
    zmqpp::socket_t socket (socketContext, typeOfSocket);
    return socket;
}

zmqpp::socket_t SocketHandler::masterSocket = MakeSocket();

void SocketHandler::EstablishConnection() {
    masterSocket.bind("tcp://" + jetsonNanoIP + ':' + std::to_string(port));
}

void SocketHandler::Send(std::string request) {
    zmqpp::message_t message;
    message << request;
    masterSocket.send(message);
}

std::string SocketHandler::Recieve() {
    std::string recievedRequest;
    zmqpp::message_t request;
    masterSocket.receive(request);
    request >> recievedRequest;

    return recievedRequest;
}

std::pair<std::string, double> SocketHandler::ParseForData(std::string request) {
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