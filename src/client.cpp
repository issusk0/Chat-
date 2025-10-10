#include<iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "client.h"
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <fstream>
using json = nlohmann::json;
using namespace std;


struct server{
    std::string ipv4;
    std::string port;
    std::string key;
    std::string name;
};

Client::Client(){};

void Client::serversToSend(){
    //abrimos el archivo
    std::ifstream f("server_to_send.json");
    if(!f.is_open()){
        cout<<"Error al abrir el archivo, asegurate de no haber cambiado el nombre";
    };

    //lo parseamos a json
    json json_file = json::parse(f);

    //preparamos el vector para almacenar los distintos objetos
    std::vector<server> ips = {};

    //iniciamos ciclo para cada objeto dentro del archivo json
    for(auto& el : json_file.object()){
        server sdata{};
        for(auto& server: el["server"]){
            sdata.ipv4 = server["ip"];
            sdata.port = server["port"];
            sdata.key = json_file["key"];
            sdata.name = json_file["username"];   
            ips.push_back(sdata);
        };
    };



};


std::string Client::sendMessage(std::string ipv4, std::string port,message msg){
    int socket_client = socket(AF_INET, SOCK_DGRAM, 0);
    in_addr addr;
    std::uint16_t unit16_value;
    struct sockaddr_in socket_cli;
    socklen_t clilen = sizeof(socket_cli);


    if(inet_pton(AF_INET, ipv4.c_str(), &addr) > 0){
        socket_cli.sin_addr.s_addr = addr.s_addr;
    };


    unsigned long templ_ul = std::stoul(port);
    socket_cli.sin_family = AF_INET;
    unit16_value = static_cast<uint16_t>(templ_ul);
    socket_cli.sin_port = htons(unit16_value);



    ssize_t numb_bytes = sendto(socket_client, &msg, sizeof(msg), 0, (struct sockaddr *)&socket_cli,clilen);

    if(numb_bytes == -1 ){
        return "Error al enviar datagrama";
    };


    return "mensaje enviado!";

};
