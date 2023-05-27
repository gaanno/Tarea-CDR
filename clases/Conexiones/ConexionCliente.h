#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <string>

#include "Conexion.h"

#define TAMANO_BUFFER 1024

using namespace std;

#ifndef CONEXIONCLIENTE_H
#define CONEXIONCLIENTE_H
class ConexionCliente : private Conexion
{
public:
    ConexionCliente(int puerto, string IPServidor);
    void mostrarEstadoConexion();
    void enviarMensaje(string mensaje);
    void cerrarConexion();
    void recibirMensaje();
    bool estaConectado();

private:
    int status;
    int valread;
    int client_fd;
    struct sockaddr_in serv_addr;

    void configurarConexion();
    void configurarSocket();
    void configurarEstado();
    void validarConexion();
};

ConexionCliente::ConexionCliente(int puerto, string IPServidor) : Conexion(puerto, IPServidor)
{
    configurarConexion();
    configurarSocket();
    configurarEstado();
    validarConexion();

}

void ConexionCliente::mostrarEstadoConexion()
{
    Conexion::mostrarEstadoConexion();
    cout << "Client_fd: " << client_fd << endl;
    cout << "Status: " << status << endl;
    cout << "Valread: " << valread << endl;
    cout << "Serv_addr.sin_family: " << serv_addr.sin_family << endl;
}

void ConexionCliente::configurarConexion()
{
    // serv_addr.sin_family = (comun::esIPLocal(this->IPServidor)) ? AF_UNIX : AF_INET; //DEBERIA SER ESTA
    // ----
    // ----
    // arreglar esto
    serv_addr.sin_family = Conexion::esIntraconexion() ? AF_UNIX : AF_INET;
    serv_addr.sin_port = htons(getPuerto());
    serv_addr.sin_addr.s_addr = inet_addr(getIP().data());
}

void ConexionCliente::configurarSocket()
{
    client_fd = socket(serv_addr.sin_family, Conexion::esIntraconexion() ? SOCK_DGRAM : SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        cout << "ERROR: Falla al crear el socket" << endl;
        exit(1);
    }
}

void ConexionCliente::configurarEstado()
{
    
   //verifica si se conecto al puerto especificado
    if ((status = connect(client_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) < 0 )
    {
        cout << "Error: Conexion fallida" << endl;
        exit(1);
    }
}

void ConexionCliente::validarConexion()
{
    cout << inet_pton(serv_addr.sin_family, getIP().data(), &serv_addr.sin_addr) << endl;
    if (inet_pton(serv_addr.sin_family, getIP().data(), &serv_addr.sin_addr) <= 0)
    {
        cout << "Error: Direccion invalida o no soportada" << endl;
        exit(1);
    }
}

void ConexionCliente::enviarMensaje(string mensaje)
{
    send(client_fd, mensaje.data(), mensaje.length(), 0);
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

bool ConexionCliente::estaConectado()
{
    return status >= 0;
}

#endif
