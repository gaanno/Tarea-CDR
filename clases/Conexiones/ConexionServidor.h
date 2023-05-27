#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>
#include <string>
#include <cstring>
#include "Conexion.h"

#ifndef CONEXIONSERVIDOR_H
#define CONEXIONSERVIDOR_H

#define TAMANO_BUFFER 1024

class ConexionServidor : private Conexion
{
public:
    ConexionServidor(int puerto);
    void escucharPuerto();

    void recibirMensaje();
    void mostrarEstadoConexion();
    void enviarMensaje(string mensaje);
    void cerrarConexion();
    void apagar();
    string getUltimoMensaje();

private:
    struct sockaddr_in address;

    int server_fd;
    int newSocket;
    int valread;
    int opt;
    int addrlen;

    char buffer[TAMANO_BUFFER] = {0};

    void configurarSocket();
    void setSocketOptions();
    void configurarConexion();
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
    Conexion::mostrarEstadoConexion();
    cout << "server_fd: " << server_fd << endl;
    cout << "Valread: " << valread << endl;
    cout << "Serv_addr.sin_family: " << address.sin_family << endl;
}
void ConexionServidor::configurarConexion()
{
    // ver tipo de conexion
    // ----
    // ----
    // arreglar esto
    // address.sin_family = Conexion::esIntraconexion() ? AF_UNIX : AF_INET;
    // deberia ser <sys/un.h>

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
    try
    {
        if (send(newSocket, mensaje.data(), mensaje.size(), 0) < 0)
            throw std::runtime_error("Error al enviar mensaje");
    }
    catch (const std::exception &e)
    {
        perror("Conexion abortada");
        exit(1);
    };
}

void ConexionServidor::recibirMensaje()
{
    // vacia todo el buffer
    memset(buffer, 0, TAMANO_BUFFER);
    valread = read(newSocket, buffer, TAMANO_BUFFER);
    //cout << "Mensaje desde el cliente: " << buffer << endl;
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
        perror("bind failed");
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

string ConexionServidor::getUltimoMensaje()
{
    string mensaje = buffer;
    return mensaje;
}
#endif