#include <array>
#include <iostream>

#define LARGO_TABLERO 15
// #define RANURA_VACIA '\0'
#define RANURA_VACIA '?'

using namespace std;

class Tablero
{
private:
    char tablero[LARGO_TABLERO][LARGO_TABLERO];

public:
    Tablero();
    void imprimirTablero();
    void iniciarTableroManual();
    void iniciarTableroAutomatico();
    string getTableroComoMensaje();
    void disparar(int fila, int columna);
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
string Tablero::getTableroComoMensaje()
{
    string mensaje;
    char letraFila = 'A';
    for (int fila = 0; fila < LARGO_TABLERO + 2; fila++)
    {
        mensaje.append(fila < LARGO_TABLERO ? string(1, letraFila++) + "\t|\t" : "\t\t");
        for (int columna = 0; columna < LARGO_TABLERO; columna++)
        {
            mensaje.append(fila < LARGO_TABLERO ? string(1, tablero[fila][columna]) : (fila == LARGO_TABLERO ? "-" : to_string(columna)));
            mensaje.append("\t");
        }
        mensaje.append("\n");
    }
    return mensaje;
}
void Tablero::imprimirTablero()
{
    char letraFila = 'A';
    for (int fila = 0; fila < LARGO_TABLERO + 2; fila++)
    {
        cout << (fila < LARGO_TABLERO ? letraFila++ : '\0') << (fila < LARGO_TABLERO ? "\t|\t" : "\t\t");
        for (int columna = 0; columna < LARGO_TABLERO; columna++)
        {
            cout << (fila < LARGO_TABLERO ? (string(1, tablero[fila][columna])) : (fila == LARGO_TABLERO ? "-" : to_string(columna))) << "\t";
        }
        cout << endl;
    }
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