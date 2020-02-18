#include "zmqpp/zmqpp.hpp"
#include <string>

class SocketHandler {
 public:
    SocketHandler();
    zmqpp::socket_t MakeSocket();
    void EstablishConnection(zmqpp::socket_t socket);
    void Send(zmqpp::socket_t socket, std::string request);
    std::string Recieve(zmqpp::socket_t socket);
    std::pair<std::string, double> ParseForData(std::string request);

 private:
    std::string jetsonNanoIP = "10.1.72.4";
    int port = 5800;
};