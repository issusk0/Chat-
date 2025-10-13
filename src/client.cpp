#include<iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client.h"
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <fstream>
#include "aux.h"
#include <cstdlib>
#include <filesystem>
using json = nlohmann::json;
using namespace std;



Client::Client(){};

std::vector<server> Client::serversToSend(){
    std::vector<server> errors;
    //abrimos el archivo y verificamos si esta abierto
    std::ifstream file("servers/server_to_send.json");
    if(!file.is_open()){
        cerr<< "Error al abrir el archivo JSON"<<endl;
        return errors;
    };


    //intentamos parsear el json para utilizarlo
    try{
        nlohmann::json json_file = json::parse(file);
        //creamos la estructura del vector para guardar los servidores como objetos
        std::vector<server> servers;

        //iniciamos el ciclo sobre el JSON y validamos su estructura
        //para poder guardar los valores en la estructura y posteriormente en el vector
        if(json_file.empty()){
            return errors;
        };
        if(json_file.contains("server") && json_file["server"].is_array()){
            for(const auto& el: json_file["server"]){
                //inicalizamos el objeto vacio para rellenarlo con los datos del JSON
                server sdata;
                sdata.ipv4 = el.value("ip","");
                sdata.port = el.value("port","");
                //verificamos que los datos no esten vacios
                if(!sdata.ipv4.empty() && !sdata.port.empty()){
                    cout<<"Servidor encontrado IP: "<<sdata.ipv4<<" puerto: "<<sdata.port<<endl;
                    servers.push_back(sdata);
                }else{
                    cerr<<"Servidores vacios u inexistentes en el JSON"<<endl;
                };
            };
        }else{
            cerr<<"El archivo JSON no contiene campo de servidores"<<endl;
        };

    //retornamos el vector con los servidores guardados
    return servers;
    }catch(const nlohmann::json::exception& e){
        cout<<"Error con el JSON: "<<e.what()<<endl;
        return errors;
    };

};


std::string Client::prepareNsendMessage(std::string json_string){

    std::vector<server> servers = serversToSend(); //obtenemos la lista de los servidores y los guardamos en un vector
    int socket_sender = socket(AF_INET, SOCK_DGRAM, 0); //punto envio datagramas


    if(servers.empty()){
        close(socket_sender);
        return "No hay servidores para enviar el mensaje!";
    };
    if (socket_sender == -1) {
        perror("socket");
        return "error: socket";
    };

    std::string message = serializerMessage(json_string);

    for (const server& el : servers) {
        in_addr addr{}; //lugar para almacenar la ip
        struct sockaddr_in sender_structure{}; //estructura de datos para almacenar los datos de los servidores a enviar
        socklen_t sender_len = sizeof(sender_structure); //longitud de tamaño que ocupa en memoria la estructura de los server

        if (inet_pton(AF_INET, el.ipv4.c_str(), &addr) == 1) {
            sender_structure.sin_addr.s_addr = addr.s_addr;
            sender_structure.sin_family = AF_INET;
            sender_structure.sin_port = htons(transformToU16(el.port));
            ssize_t numb_bytes = sendto(
                socket_sender,
                message.data(),
                message.size(),
                0,
                (struct sockaddr *)&sender_structure,
                sender_len
            );

            if (numb_bytes == -1) {
                perror("Error al enviar el datagrama");
            };
        }else{
            return "Error con la direccion IP, tiene que ser una IPV4";
        };
    };

    close(socket_sender);
    return "mensajes enviados!";

};


std::string Client::serializerMessage(std::string message){

    std::ifstream file("servers/server_to_send.json");
    if(!file.is_open()){
        cerr<<"Error al abrir el archivo JSON"<<endl;
        return "La funcion no ha podido continuar";
    };

    if(message.empty()){
        cerr<<"No hay mensaje a enviar";
        return "";
    };
    try{
        std::filesystem::path filepath = "servers/server_to_send.json";
        if(std::filesystem::is_empty(filepath)){
            cerr<<"Error, el archivo está vacio"<<endl;
            return "";
       };

       nlohmann::json config = json::parse(file);
       if(config.empty()){
            cerr<<"Error, el archivo JSON está vacio"<<endl;
            return "";
       };
       nlohmann::json message_structure;

       if(config.contains("username")){message_structure["username"] = config["username"];};
       message_structure["message"] = message;

       std::string serialized_message = message_structure.dump();
        return serialized_message;


    }catch(const nlohmann::json::exception &e){
        cerr<<"Error al operar con el archivo JSON: "<<e.what()<<endl;
        return "No se ha podido terminar la operacion";
    };

    return"Funcion no ha cumplido su proposito";


};