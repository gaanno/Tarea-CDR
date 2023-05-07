#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>
#include <string>
#include "Conexion.h"

#ifndef CONEXIONSERVIDOR_H
#define CONEXIONSERVIDOR_H

#define TAMANO_BUFFER 1024

class ConexionServidor : private Conexion
{
public:
    ConexionServidor(int puerto);
    void mostrarEstadoConexion();
    void enviarMensaje(string mensaje);
    void cerrarConexion();
    void apagar();

private:
    struct sockaddr_in address;

    int server_fd;
    int newSocket;
    int valread;

    int opt;
    int addrlen;

    void configurarSocket();
    void setSocketOptions();
    void configurarConexion();
    void escucharPuerto();
    void recibirMensaje();
};

ConexionServidor::ConexionServidor(int puerto) : Conexion(puerto)
{
    this->opt = 1;
    this->addrlen = sizeof(address);

    configurarConexion();
    configurarSocket();
    setSocketOptions();
    escucharPuerto();
}
void ConexionServidor::mostrarEstadoConexion()
{
    cout << "IP:" << getIP() << endl;
    cout << "Es IP local: " << (comun::esIPLocal(getIP()) ? "Si" : "No") << endl;
    cout << "Puerto: " << getPuerto() << endl;
    cout << "server_fd: " << server_fd << endl;
    cout << "Valread: " << valread << endl;
    cout << "Serv_addr.sin_family: " << address.sin_family << endl;
}
void ConexionServidor::configurarConexion()
{
    address.sin_family = AF_INET;
    address.sin_port = htons(getPuerto());
    address.sin_addr.s_addr = INADDR_ANY;
}

void ConexionServidor::configurarSocket()
{
    if ((server_fd = socket(address.sin_family, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

void ConexionServidor::enviarMensaje(string mensaje)
{
    mostrarEstadoConexion();
    send(newSocket, mensaje.data(), mensaje.length(), 0);
    cout << "Mensaje enviado" << endl;
    recibirMensaje();
}

void ConexionServidor::recibirMensaje()
{
    char buffer[TAMANO_BUFFER] = {0};
    valread = read(newSocket, buffer, TAMANO_BUFFER);
    cout << buffer << endl;
}

void ConexionServidor::setSocketOptions()
{
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}

void ConexionServidor::escucharPuerto()
{
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failedaaa");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((newSocket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}
void ConexionServidor::cerrarConexion()
{
    close(server_fd);
}

void ConexionServidor::apagar()
{
    shutdown(server_fd, SHUT_RDWR);
}
#endif