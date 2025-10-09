#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <cstdint> 
#ifndef SERVER_H
#define SERVER_H
class CreateServer{
    public:
        CreateServer();
        std::string createServerPtP(uint32_t IPV4_ADDRESS, uint16_t PORT_ADRRESS, std::string key);
        bool validateKeys(std::string key);
        void runServer(int socketftd);
};
#endif
