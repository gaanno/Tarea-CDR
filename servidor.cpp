#include <iostream>
#include <vector>
#include "Tablero.h"
#include "Barco.h"

using namespace std;

vector<Barco> inicializarBarcos();

int main()
{
    // estas cosas meterlas a hebras
    vector<Barco> barcos = inicializarBarcos();
    Tablero tablero;
    tablero.imprimirTablero();
    return 0;
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