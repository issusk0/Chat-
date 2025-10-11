#ifndef CLIENT_H
#define CLIENT_H


class Client{
    public:
        Client();
        string prepareNsendMessage(message message); //al momento de enviar un mensaje
        std::vector<server> serversToSend(); //funcion para definir el servidor(o grupo de) a enviar el mensaje 
        ssize_t serializerMessage();
};


export struct server{
    std::string ipv4;
    std::string port;
};

export struct message{
    char message[1024];
    char key[12];
    char name[12];
};
#endif