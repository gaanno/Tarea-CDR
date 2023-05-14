#include <iostream>
#include <vector>

#include "clases/Tablero/Tablero.h"
#include "clases/Barco/Barco.h"
#include "clases/Comun.h"
#include "clases/Conexiones/ConexionServidor.h"

using namespace std;

vector<Barco> inicializarBarcos();
void verificarArgumentosServidor(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    verificarArgumentosServidor(argc, argv);

    Tablero tablero = Tablero();
    ConexionServidor servidor(atoi(argv[1]));
    servidor.mostrarEstadoConexion();
    servidor.escucharPuerto();
    servidor.enviarMensaje(tablero.getTableroComoMensaje());
    servidor.cerrarConexion();
    servidor.apagar();

    return 0;
}

void verificarArgumentosServidor(int argc, char *argv[])
{
    if (argc != 2 || !comun::esNumero(argv[1]))
    {
        cout << "ERROR: Parametros invalidos" << endl;
        exit(1);
    }
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