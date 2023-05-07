#include <iostream>
#include <string>

using namespace std;

#ifndef CONEXION_H
#define CONEXION_H
class Conexion
{
public:
    Conexion(string ip,int puerto);
    string getIP();
    int getPuerto();

private:
    string IP;
    int p;
};

Conexion::Conexion(string IP, int puerto)
{
    this->IP = IP;
    this->p = puerto;
}

string Conexion::getIP()
{
    return IP;
}

int Conexion::getPuerto()
{
    return p;
}
#endif