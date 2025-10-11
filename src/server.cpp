#include <stdio.h>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>  
#include <iostream>
#include "aux.h"
#include "server.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/socket.h> //para poder manipular los sockets
#include <netinet/in.h>
#include <arpa/inet.h> // para poder manipular los tipo de protocolo
#include <cstdint> //para definir los tipo de dato a la hora de crear el servidor con la funcion createServer
using namespace std;




//estructura para poder almacenar en memoria el sockaddress y no recrear otro innecesariamente
//esto con la finalidad de poder, en la funcion de setDatagram, rellenar el sendto() con la estructura
//de datos almacenada en memoria, luego, limpiarla


//el ipv_4 tiene que existir dentro de la maquina sino dara error

std::string CreateServer::createServerPtP(uint32_t IPV4_ADDRESS, uint16_t PORT_ADRRESS){
            //AF_INET = ipv4, SOCK_DGRAM = UDP


     

                //creacion del socket en udp y protocolo udp
                int server_socket = socket(AF_INET, SOCK_DGRAM, 0);


                //asignacion a las atribuciones del socket para su utilizacion
                sockaddr_in serverAddress;
                serverAddress.sin_family = AF_INET;
                serverAddress.sin_port = htons(PORT_ADRRESS);
                serverAddress.sin_addr.s_addr = IPV4_ADDRESS;

                /*
                    asignado la estructura del serverAddresss al server_socket, a través del puntero,
                    es decir que, primero se asigna al server_socket la estructura en memoria, aquella estructura
                    se le asigna un lugar en la memoria, y cuyo espacio a asignar es el del tamaño de la estructura
                    de serverAddress, ya que sizeof devuelve en bytes el tamaño de una clase u estructura u dato

                    Al ser un server UDP utilizamos, solo recvfrom y sendto
                    no usamos listen ni accepts
                
                */
                if(bind(server_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) != 0){
                    perror("Error al crear socket!");
                }else{ 
                    cout<<"Servidor creado exitosamente";
                    while (true)
                    {   
                        signal(SIGINT, signalHandler);
                        runServer(server_socket);
                    };
                    
                    
                };
            return "";
};




void CreateServer::runServer(int socketftd){
    
    char buffer [1024];
    struct sockaddr_in cliaddr;
    socklen_t clilen= sizeof(cliaddr);


    ssize_t numb_bytes = recvfrom(socketftd, buffer,sizeof(buffer),0, 
                            (struct sockaddr*)&cliaddr, &clilen);
    
    if(numb_bytes == -1){
        perror("Error al transmitir el mensaje del cliente al sevidor!");

    }else{
        buffer[numb_bytes]= '\0';
        cout<<buffer<< "\n";
    };

};


