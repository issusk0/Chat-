#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
using std::string;
struct server{
    string ipv4;
    string port;
};

struct message{
    char message[1024];
    char name[12];
};
class Client{
    public:
        Client();
        string prepareNsendMessage(message message); //al momento de enviar un mensaje
        std::vector<server> serversToSend(); //funcion para definir el servidor(o grupo de) a enviar el mensaje 
        ssize_t serializerMessage();
};



#endif