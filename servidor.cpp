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
    const string mensajeInicial = "Bienvenido al juego de batalla naval";
    const string mensajeTablero = "1.Rellenar tablero de forma automatica\n2.Rellenar tablero de forma manual\n";

    Tablero tablero = Tablero();
    ConexionServidor servidor(atoi(argv[1]));
    servidor.mostrarEstadoConexion();


    try
    {
        servidor.enviarMensaje(mensajeInicial);
        servidor.enviarMensaje(mensajeTablero);
        servidor.recibirMensaje();
        while (true)
        {
            cout << "msg: " << servidor.getUltimoMensaje() << endl;
            servidor.enviarMensaje(tablero.getTableroComoMensaje());
            servidor.recibirMensaje();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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