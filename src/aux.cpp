#include "aux.h"
#include <iostream>
#include "server.h"
using namespace std;
void signalHandler(int signum){
    exit(signum);
};


uint16_t transformToU16(std::string port){
            std::uint16_t uint16_value;
            unsigned long templ_ul = std::stoul(port);
            uint16_value = static_cast<uint16_t>(templ_ul);
            return uint16_value;
};

uint32_t transformToU32(std::string ipv4){
    std::uint32_t uint32_t_value;
    unsigned long templ_ul = std::stoul(ipv4);
    uint32_t_value = static_cast<uint32_t>(templ_ul);
    return uint32_t_value;
};