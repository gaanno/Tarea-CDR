#include <iostream>
#include <string>

using namespace std;

#ifndef CONEXION_H
#define CONEXION_H
class Conexion
{
public:
    Conexion(int puerto, string ip = "127.0.0.1");
    string getIP();
    int getPuerto();

private:
    string IP;
    int puerto;
};

Conexion::Conexion(int puerto, string IP)
{
    this->IP = IP;
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
#endif