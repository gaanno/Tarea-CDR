#include <iostream>

using namespace std;

#ifndef BARCO_H
#define BARCO_H
class Barco
{
    public:
    char getNombre();
    int getLargo();
    Barco(char nombre, int largo);

    private:
    char nombre;
    int largo;
};

Barco::Barco(char nombre, int largo){
    this->nombre = nombre;
    this->largo = largo;
}

char Barco::getNombre(){
    return this->nombre;
}

int Barco::getLargo(){
    return this->largo;
}
#endif

