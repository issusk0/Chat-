#ifndef CLIENT_H
#define CLIENT_H


class  ClientSide{
    public:
        void setCredentials(); //al momento de iniciar el programa como cliente(para enviar mensajes)
        void sendMessage(); //al momento de enviar un mensaje
        void setServersToSend(); //funcion para definir el servidor(o grupo de) a enviar el mensaje 
};


#endif