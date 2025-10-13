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
using json = nlohmann::json;
using namespace std;



Client::Client(){}

std::vector<server> Client::serversToSend(){
    //abrimos el archivo
    std::ifstream f("server_to_send.json");
    if(!f.is_open()){
        cout<<"Error al abrir el archivo, asegurate de no haber cambiado el nombre!";
        return false;
    };

    //lo parseamos a json
    json json_file = json::parse(f);

    //preparamos el vector para almacenar los distintos objetos
    std::vector<server> ips = {};

    //iniciamos ciclo para cada objeto dentro del archivo json
    for (auto& el : json_file) {
        server sdata{};
        if (el.contains("server")) {
            for (auto& srv : el["server"]) {
                sdata.ipv4 = srv.value("ip", "");
                sdata.port = srv.value("port", "");
                ips.push_back(sdata);
            }
        }
    }
    return ips;


};


std::string Client::prepareNsendMessage(std::string json_string){

    std::vector<server> servers = serversToSend(); //obtenemos la lista de los servidores y los guardamos en un vector
    int socket_sender = socket(AF_INET, SOCK_DGRAM, 0); //punto envio datagramas
    if (socket_sender == -1) {
        perror("socket");
        return "error: socket";
    }

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
            }
        }
    }

    close(socket_sender);
    return "mensajes enviados!";

}


std::string Client::serializerMessage(std::string message){



    nlohmann::json data;

    std::ifstream f("server_to_send.json");
    if (!f.is_open()) {
        cout << "Error al abrir el archivo, asegurate de no haber cambiado el nombre!";
        return std::string();
    }

    json config = json::parse(f);

    data["message"] = message;
    if (config.contains("username")) data["username"] = config["username"];

    std::string json_string = data.dump(); //dump permite transformar json a strings

    return json_string;
}