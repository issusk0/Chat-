#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
using std::string;
struct server{
    string ipv4;
    string port;
};
class Client{
    public:
        Client();
        string prepareNsendMessage(std::string json_string); //al momento de enviar un mensaje
        std::vector<server> serversToSend(); //funcion para definir el servidor(o grupo de) a enviar el mensaje 
        std::string serializerMessage();
};



#endif