#include <iostream>
#include <string>

#include "clases/Comun.h"
#include "clases/Conexiones/ConexionCliente.h"

using namespace std;

void verificarArgumentosCliente(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    verificarArgumentosCliente(argc, argv);
    ConexionCliente cliente = ConexionCliente(atoi(argv[2]), argv[1]);
    string mensaje;

    

    try
    {
        cliente.recibirMensaje();
        cliente.recibirMensaje();
        while (true)
        {
            cout << "Ingrese su mensaje: " << endl;
            if (getline(cin, mensaje))
            {
                if (mensaje.empty())
                {
                    continue;
                }
                cliente.enviarMensaje(mensaje);
                cliente.recibirMensaje();
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

void verificarArgumentosCliente(int argc, char *argv[])
{
    if (argc != 3 || !comun::esNumero(argv[2]))
    {
        cout << "ERROR: Parametros invalidos" << endl;
        exit(1);
    }
}
