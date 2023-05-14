#include <iostream>
#include <string>
#include <netdb.h>
#include <unistd.h>

#include "../Comun.h"

using namespace std;

#ifndef CONEXION_H
#define CONEXION_H
class Conexion
{
public:
    Conexion(int puerto, string ip = "");
    string getIP();
    int getPuerto();
    void mostrarEstadoConexion();
    string getIPLocal();
    bool esIPLocal();

private:
    string IP;
    int puerto;
    bool IPLocal = false;
    bool esIPValida(string IPTemporal);
};

Conexion::Conexion(int puerto, string IP)
{
    if (IP == "" || IP  == getIPLocal())
    {
        this->IP = getIPLocal();
        IPLocal = true;
    }
    else
    {
        if (!esIPValida(IP))
        {
            perror("--IP invalida");
            exit(1);
        }
        this->IP = IP;
    }
    this->puerto = puerto;
}

string Conexion::getIP()
{
    return IP;
}

int Conexion::getPuerto()
{
    return puerto;
}

void Conexion::mostrarEstadoConexion()
{
    cout << "IP:" << getIP() << endl;
    cout << "Es IP local: " << (IPLocal ? "Si" : "No") << endl;
    cout << "Puerto: " << getPuerto() << endl;
}

string Conexion::getIPLocal()
{
    char host[256];
    int hostname = gethostname(host, sizeof(host));
    struct hostent *host_entry = gethostbyname(host);
    char *IPLocal = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));
    return IPLocal;
}



// Función para validar una dirección IP
bool Conexion::esIPValida(string IPTemporal)
{
    // dividir la string en tokens
    vector<string> list = comun::dividir(IPTemporal, '.');
    // si el tamaño del token no es igual a cuatro
    if (list.size() != 4)
    {
        return false;
    }

    // validar cada ficha
    for (string str : list)
    {
        // verifica que la string sea un número o no, y los números
        // están en el rango válido
        if (!comun::esNumero(str) || stoi(str) > 255 || stoi(str) < 0)
        {
            return false;
        }
    }
    return true;
}

bool Conexion::esIPLocal()
{
    return IPLocal;
}
#endif