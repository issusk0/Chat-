#include <stdio.h>
#include <iostream>
#include "server.h"
#include <vector>
#include <sys/socket.h>
#include <cstdint>
#include <csignal>
using namespace std;

struct parameters{
    uint32_t ipv4;
    uint16_t port;
    std::string key;
};
struct in_addr addr;
int main (int argc, char *argv[]) {
    CreateServer cs;
    parameters pam;
    for(int i = 1; i < argc; i++){
        if(std::string (argv[i]) == "-S" && i + 1 < argc){
            if(inet_pton(AF_INET, argv[i+ 1], &addr) == 1){
                pam.ipv4 = addr.s_addr;
            }else{
                cout<<"Need an IPV4 Address!\n";
                return 1;
            };
            
        };

        if(std::string (argv[i]) == "-P" && i + 1 < argc){
            std::string str_port_value = argv[i+1];
            std::uint16_t uint16_value;
            unsigned long templ_ul = std::stoul(str_port_value);
            uint16_value = static_cast<uint16_t>(templ_ul);
            pam.port = uint16_value;
        };
    };
    cs.createServerPtP(pam.ipv4, pam.port);
    
};


