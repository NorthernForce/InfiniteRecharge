#include "zmqpp/zmqpp.hpp"
#include <string>

class SocketHandler {
 public:
    SocketHandler();
    zmqpp::socket GetSocket();
    void EstablishConnection(zmqpp::socket socket);
    void SendRequest(zmqpp::socket socket, std::string request);
    std::string RecieveRequest(zmqpp::socket socket);
    std::pair<std::string, double> ParseRequestForData(std::string request);

 private:
    std::string jetsonNanoIP = "10.1.72.4";
    int port = 5555;
};