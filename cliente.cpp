#include <iostream>
#include "clases/Comun.h"
#include "clases/ConexionCliente.h"

using namespace std;
void verificarArgumentosCliente(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    verificarArgumentosCliente(argc, argv);
    ConexionCliente enlace(argv[1], atoi(argv[2]));


    enlace.mostrarEstadoConexion();
    enlace.enviarMensaje("soy un mensaje de prueba");
    enlace.recibirMensaje();
    return 0;
}

void verificarArgumentosCliente(int argc, char *argv[])
{
    if (argc != 3 || !comun::esNumero(argv[2]) || !comun::esIPValida(argv[1]))
    {
        cout << "ERROR: Parametros invalidos" << endl;
        exit(1);
    }
}


