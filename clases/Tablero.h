#include <array>
#include <iostream>

#define LARGO_TABLERO 15
#define RANURA_VACIA '\0'

using namespace std;

class Tablero
{
public:
    Tablero();
    void imprimirTablero();
    void iniciarTableroManual();
    void iniciarTableroAutomatico();
    void disparar(int fila, int columna);

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
    char letraFila = 'A';

    for (int fila = 0; fila < LARGO_TABLERO; fila++)
    {
        cout << letraFila++ << "\t|\t";
        for (int columna = 0; columna < LARGO_TABLERO; columna++)
        {
            cout << this->tablero[fila][columna] << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < LARGO_TABLERO + 2; i++)
    {
        cout << "-\t";
    }
    cout << endl;
    for (int i = 0; i < LARGO_TABLERO + 2; i++)
    {
        if (i == 0 || i == 1)
        {
            cout << "\t";
        }else{
        cout << i - 2 << "\t";
        }
    }
    cout << endl;
}

void Tablero::iniciarTableroManual()
{
}

void Tablero::iniciarTableroAutomatico()
{
}

void Tablero::disparar(int fila, int columna)
{
}