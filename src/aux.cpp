#include "aux.h"
#include <iostream>
#include "server.h"

void signalHandler(int signum){
    exit(signum);
};