#include <stdio.h>
#include <iostream>
#include <format>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/socket.h> //para poder manipular los sockets
#include <netinet/in.h>
#include <arpa/inet.h> // para poder manipular los tipo de protocolo
#include <cstdint> //para definir los tipo de dato a la hora de crear el servidor con la funcion createServer
using namespace std;

class CreateServer{
    public:
        std::string createServerPtP(uint32_t IPV4_ADDRESS, uint16_t PORT_ADRRESS, std::string key){
            //AF_INET = ipv4, SOCK_DGRAM = UDP


            if(validateKeys(key)){

                //creacion del socket en udp y protocolo udp
                int server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


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
                bind(server_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
                std:: string formatted_string = format("UDP Server is up on: {}, {}, {}", static_cast<int>(IPV4_ADDRESS),static_cast<int>(PORT_ADRRESS),key)
            }else{
                return "Problema al crear el socket o el archivo donde se encuentran las keys tiene error!";
            };


        };

        bool validateKeys(std::string key){
            std:: string filepath = "./src/keys/private.txt";
            std:: ifstream file;
            std::string key_file;

            file.open(filepath);
            if(file.is_open()){
           
                while(getline(file, key_file)){
                        if(key_file == key){
                            file.close();
                            return true;
                        }
                };
                file.close();
                return false;
                

            }else{
                return false;
            };

        };
};