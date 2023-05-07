#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "clases/Tablero/Tablero.h"
#include "clases/Barco/Barco.h"
#include "clases/Comun.h"

using namespace std;

vector<Barco> inicializarBarcos();
void verificarArgumentosServidor(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    verificarArgumentosServidor(argc, argv);

    int puerto;
    sscanf(argv[1], "%d", &puerto);

    int server_fd, new_socket, valread;

    // estas cosas meterlas a hebras
    Tablero tablero;
    vector<Barco> barcos = inicializarBarcos();
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    string mensaje = tablero.getTableroComoMensaje();

    char *hello = new char[mensaje.length() + 1];
    strcpy(hello, mensaje.c_str());

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(puerto);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    
    return 0;
}

void verificarArgumentosServidor(int argc, char *argv[])
{
    if (argc != 2 || !comun::esNumero(argv[1]))
    {
        cout << "ERROR: Parametros invalidos" << endl;
        exit(1);
    }
}

vector<Barco> inicializarBarcos()
{
    vector<Barco> barcos;
    barcos.push_back(Barco('P', 5));
    barcos.push_back(Barco('B', 4));
    barcos.push_back(Barco('B', 4));
    barcos.push_back(Barco('S', 3));
    barcos.push_back(Barco('S', 3));
    barcos.push_back(Barco('L', 1));
    barcos.push_back(Barco('L', 1));
    barcos.push_back(Barco('L', 1));
    return barcos;
}