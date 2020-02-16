#include "zmqpp/zmqpp.hpp"
#include <string>

class SocketHandler {
 public:
    SocketHandler();
    zmqpp::socket_t GetSocket();
    void EstablishConnection(zmqpp::socket_t socket);
    void SendRequest(zmqpp::socket_t socket, std::string request);
    std::string RecieveRequest(zmqpp::socket_t socket);
    std::pair<std::string, double> ParseRequestForData(std::string request);

 private:
    std::string jetsonNanoIP = "10.1.72.4";
    int port = 5555;
};