#include <stdio.h>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <cstdint>
#include <csignal>
#include "client.h"
#include "server.h"
#include "aux.h"
using namespace std;

struct parameters {
    uint16_t port = 8080; // Valor predeterminado
};

int main(int argc, char *argv[]) {
    Client cl;
    CreateServer cs;
    parameters pam;

    bool run_client = false;
    string message;

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-P" && i + 1 < argc) {
            try {
                pam.port = transformToU16(argv[i + 1]);
                if (pam.port == 0) {
                    cerr << "Error: Puerto inválido: " << argv[i + 1] << endl;
                    return 1;
                }
                i++;
            } catch (const std::exception& e) {
                cerr << "Error al convertir puerto " << argv[i + 1] << ": " << e.what() << endl;
                return 1;
            }
        } else if (string(argv[i]) == "-m" && i + 1 < argc) {
            run_client = true;
            for (int j = i + 1; j < argc; ++j) {
                message += argv[j];
                if (j < argc - 1) message += " ";
            }
            i = argc;
        } else {
            cerr << "Argumento desconocido: " << argv[i] << endl;
            return 1;
        }
    }

    if (run_client) {
        cout << "Ejecutando cliente, enviando mensaje: " << message << endl;
        string result = cl.prepareNsendMessage(message);
        cout << result << endl;
        return 0;
    } else {
        cout << "Ejecutando servidor en el puerto " << pam.port << endl;
        cs.createServerPtP(pam.port);
        return 0;
    }
}