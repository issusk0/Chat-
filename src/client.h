#ifndef CLIENT_H
#define CLIENT_H


class  Client{
    public:
        string sendMessage(std::string ipv4, std::string port,message message); //al momento de enviar un mensaje
        void serversToSend(); //funcion para definir el servidor(o grupo de) a enviar el mensaje 
        ssize_t serializerMessage();
};

export struct message{
    char message[1024];
    char key[12];
};
#endif