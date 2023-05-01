#include <iostream>
#include <vector>

#include "clases/Tablero.h"
#include "clases/Barco.h"
#include "clases/Comun.h"

using namespace std;

vector<Barco> inicializarBarcos();

int main(int argc, char *argv[])
{
    if (argc != 2 || !comun::esNumero(argv[1]))
    {
        cout << "ERROR: Parametros invalidos" << endl;
        exit(1);
    }
    const string PUERTO = argv[1];

    // estas cosas meterlas a hebras
    Tablero tablero;
    vector<Barco> barcos = inicializarBarcos();
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