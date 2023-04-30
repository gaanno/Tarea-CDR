#include <array>
#include <iostream>
#include <Barco.h>

#define LARGO_TABLERO 15
#define RANURA_VACIA '-'

using namespace std;

class Tablero
{
public:
    Tablero();
    void imprimirTablero();
    void iniciarTableroManual();
    void iniciarTableroAutomatico();
    void disparar();

private:
    char tablero[LARGO_TABLERO][LARGO_TABLERO];
};

/**
 * Constructor
 * Crea un tablero nuevo y lo inicializa con ranuras vacias
 */
Tablero::Tablero()
{
    for (int fila = 0; fila < LARGO_TABLERO; fila++)
    {
        for (int columna = 0; columna < LARGO_TABLERO; columna++)
        {
            this->tablero[fila][columna] = RANURA_VACIA;
        }
    }
}

void Tablero::imprimirTablero()
{
    for (int fila = 0; fila < LARGO_TABLERO; fila++)
    {
        for (int columna = 0; columna < LARGO_TABLERO; columna++)
        {
            cout << this->tablero[fila][columna] << "\t";
        }
        cout << endl;
    }
}

void Tablero::iniciarTableroManual(){

}

void Tablero::iniciarTableroAutomatico(){

}