#include <iostream>
#include <vector>
#include <time.h>
#include <omp.h>

#include "clases/Tablero/Tablero.h"
#include "clases/Barco/Barco.h"
#include "clases/Comun.h"
#include "clases/Conexiones/ConexionServidor.h"

using namespace std;

vector<Barco> inicializarBarcos();
void verificarArgumentosServidor(int argc, char *argv[]);
string getResultadoParcial(Tablero cliente, Tablero servidor);

int main(int argc, char *argv[])
{

    while (true)
    {
#pragma omp parallel
        {
            srand(time(0)); // para random
            verificarArgumentosServidor(argc, argv);

            ConexionServidor servidor(atoi(argv[1]));
            string mensajeAnterior = "";
            Tablero tableroServidor; // tablero que sera del servidor
            Tablero tableroCliente;  // tablero que sera del cliente

            const bool comienzaServidor = rand() % 2;

            const string mensajeInicial = "Bienvenido al juego de batalla naval\n";
            const string formatoDisparo = "Para disparar por favor primero ingrese la fila y luego la columna separados por un espacio\n";
            const string ejemploDisparo = "Ejemplo de disparo: A 1\n\n";
            const string mensajeTablero = "Su tablero se ha llenado de forma automatica:\n";
            string usuarioInicial = "Comienza: ";
            usuarioInicial += comienzaServidor ? "Servidor\n" : "Cliente\n";
            const string mensajeTurno = "\nSu turno, ingrese coordenadas:";
            int fila, columna;
            cout << usuarioInicial << endl;

            // tableroServidor.imprimirTablero();
            // tableroCliente.imprimirTablero();

            try
            {
                servidor.enviarMensaje(mensajeInicial + formatoDisparo + ejemploDisparo + usuarioInicial + mensajeTablero + tableroCliente.getTableroComoMensaje() + mensajeTurno);
                servidor.recibirMensaje();
                cout << "Nueva conexion: " << servidor.getUltimoMensaje() << endl;
                mensajeAnterior = servidor.getUltimoMensaje();
                while (true)
                {
                    if (servidor.getUltimoMensaje() != mensajeAnterior)
                    {
                        mensajeAnterior = servidor.getUltimoMensaje();
                        cout << "msg: " << servidor.getUltimoMensaje() << endl;

                        // divide las coordenadas obtenidasdel cliente
                        vector<string> coordenadas = comun::dividir(servidor.getUltimoMensaje(), ' ');

                        if (coordenadas.size() == 2)
                        {
                            if (coordenadas.size() == 2 && !comun::esNumero(coordenadas[0]) && coordenadas[0].length() == 1 && comun::esNumero(coordenadas[1]))
                            {
                                fila = toupper(coordenadas[0].c_str()[0]) - 'A';
                                columna = stoi(coordenadas[1]);
                            }
                            else
                            {
                                servidor.enviarMensaje("Coordenadas invalidas");
                                cout << "Coordenadas invalidas: " << coordenadas[0] << endl;
                                continue;
                            }

                            if (fila < 0 || fila > LARGO_TABLERO || columna < 0 || columna > LARGO_TABLERO)
                            {
                                servidor.enviarMensaje("Coordenadas invalidas");
                                cout << "Coordenadas invalidas: " << coordenadas[0] << endl;
                                continue;
                            }
                            if (comienzaServidor)
                            {
                                tableroCliente.disparoAleatorio();
                                tableroServidor.disparar(fila, columna);
                            }
                            else
                            {
                                tableroServidor.disparar(fila, columna);
                                tableroCliente.disparoAleatorio();
                            }
                        }
                        if (tableroCliente.getVidasBarcos() == 0)
                        {
                            servidor.enviarMensaje("Perdiste");
                            exit(0);
                        }
                        else if (tableroServidor.getVidasBarcos() == 0)
                        {
                            servidor.enviarMensaje("Ganaste");
                            exit(0);
                        }
                        servidor.enviarMensaje(getResultadoParcial(tableroServidor, tableroCliente));
                    }
                    servidor.recibirMensaje();
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
            cout << "Fin del juego, saliendo..." << endl;
            servidor.cerrarConexion();
            servidor.apagar();
        }
    }

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

string getResultadoParcial(Tablero servidor, Tablero cliente)
{
    string resultado;
    resultado = "Resultados parciales: \n";
    resultado += "Tablero del servidor: \n" + servidor.getTableroOcultoComoMensaje();
    resultado += "\n-------------------\n";
    resultado += "Su tablero: \n" + cliente.getTableroComoMensaje();
    resultado += "\n-------------------\n";
    resultado += "Ingrese coordenadas para atacar: \n";
    return resultado;
}

int disparoAleatorio()
{
    return rand() % 15;
}