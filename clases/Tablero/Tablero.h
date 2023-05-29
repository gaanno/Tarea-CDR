#include <array>
#include <iostream>
#include <vector>
#include <string>
#include "clases/Barco/Barco.h"

#define LARGO_TABLERO 15
// #define RANURA_VACIA '\0'
#define RANURA_VACIA '.'

using namespace std;

class Tablero
{
private:
    char tablero[LARGO_TABLERO][LARGO_TABLERO];
     vector<Barco> barcos; //Para almacenar los barcos

public:
    Tablero();
    void imprimirTablero();
    void iniciarTableroManual();
    void iniciarTableroAutomatico();
    string getTableroComoMensaje();
    void disparar(int fila, int columna);
    bool esPosibleColocarBarco(const Barco& barco, int fila, int columna, char direccion);
    void colocarBarco(const Barco& barco, int fila, int columna, char direccion);

};
