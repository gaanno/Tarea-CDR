#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "../Comun.h"
#include "Conexion.h"

#define TAMANO_BUFFER 1024

using namespace std;

#ifndef CONEXIONCLIENTE_H
#define CONEXIONCLIENTE_H
class ConexionCliente : private Conexion
{
public:
    ConexionCliente(string IPServidor, int puerto);
    void mostrarEstadoConexion();
    void enviarMensaje(string mensaje);
    void cerrarConexion();

private:
    int status;
    int valread;
    int client_fd;
    struct sockaddr_in serv_addr;

    void configurarServidor();
    void configurarCliente();
    void configurarEstado();
    void validarConexion();
    void recibirMensaje();
};

ConexionCliente::ConexionCliente(string IPServidor, int puerto):Conexion(IPServidor, puerto)
{
    configurarServidor();
    configurarCliente();
    configurarEstado();
    validarConexion();
}

void ConexionCliente::mostrarEstadoConexion()
{
    cout << "IP:" << getIP() << endl;
    cout << "Es IP local: " << (comun::esIPLocal(getIP()) ? "Si" : "No") << endl;
    cout << "Puerto: " << getPuerto() << endl;
    cout << "Client_fd: " << client_fd << endl;
    cout << "Status: " << status << endl;
    cout << "Valread: " << valread << endl;
    cout << "Serv_addr.sin_family: " << serv_addr.sin_family << endl;
}

void ConexionCliente::configurarServidor()
{
    // serv_addr.sin_family = (comun::esIPLocal(this->IPServidor)) ? AF_UNIX : AF_INET; //DEBERIA SER ESTA
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(getPuerto());
}

void ConexionCliente::configurarCliente()
{
    client_fd = socket(serv_addr.sin_family, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        cout << "ERROR: Falla al crear el socket" << endl;
        exit(1);
    }
}

void ConexionCliente::configurarEstado()
{
    status = connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (status < 0)
    {
        cout << "Error: Conexion fallida" << endl;
        exit(1);
    }
}

void ConexionCliente::validarConexion()
{
    if (inet_pton(serv_addr.sin_family, getIP().data(), &serv_addr.sin_addr) <= 0)
    {
        cout << "Error: Direccion invalida o no soportada" << endl;
        exit(1);
    }
}

void ConexionCliente::enviarMensaje(string mensaje)
{
    send(client_fd, mensaje.data(), mensaje.length(), 0);
    recibirMensaje();
}

void ConexionCliente::recibirMensaje()
{
    char buffer[TAMANO_BUFFER] = {0};
    valread = read(client_fd, buffer, TAMANO_BUFFER);
    cout << buffer << endl;
}

void ConexionCliente::cerrarConexion()
{
    close(client_fd);
}
#endif
