#include "zmqpp/zmqpp.hpp"
#include <string>

class SocketHandler {
 public:
    static zmqpp::socket_t MakeSocket(zmqpp::socket_type typeOfSocket);
    void EstablishConnection();
    void Send(std::string request);
    std::string Recieve();
    std::pair<std::string, double> ParseForData(std::string request);
    static zmqpp::socket_t masterSocket;

 private:
    std::string jetsonNanoIP = "10.1.72.4";
    int port = 5800;
};