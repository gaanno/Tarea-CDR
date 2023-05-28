#include <array>
#include <iostream>
#include <vector>
#include <string>
#include "../Barco/Barco.h"

#define LARGO_TABLERO 15
// #define RANURA_VACIA '\0'
#define RANURA_VACIA '.'

using namespace std;

class Tablero
{
private:
    char tablero[LARGO_TABLERO][LARGO_TABLERO];
    vector<Barco> barcos; // Para almacenar los barcos
    int vidasBarcos = 22;

public:
    Tablero();
    void imprimirTablero();
    void iniciarTableroManual();
    void iniciarTableroAutomatico();
    string getTableroComoMensaje();
    void disparar(int fila, int columna);
    bool esPosibleColocarBarco(Barco &barco, int fila, int columna, char direccion);
    void colocarBarco(Barco &barco, int fila, int columna, char direccion);
    string getTableroOcultoComoMensaje();
    int getVidasBarcos();
    void disparoAleatorio();
};

std::vector<Barco> inicializarBarcos(); // Declaración de la función inicializarBarcos()

/** ructor
    Crea un tablero nuevo y lo inicializa con ranuras vacias */
Tablero::Tablero()
{

    for (int fila = 0; fila < LARGO_TABLERO; fila++)
    {
        for (int columna = 0; columna < LARGO_TABLERO; columna++)
        {
            tablero[fila][columna] = RANURA_VACIA;
        }
    }

    barcos = inicializarBarcos();
    iniciarTableroAutomatico();
}

int Tablero::getVidasBarcos()
{
    return vidasBarcos;
}

void Tablero::disparoAleatorio()
{
    int fila;
    int columna;
    do
    {
        fila = rand() % LARGO_TABLERO;
        columna = rand() % LARGO_TABLERO;
    } while (tablero[fila][columna] != RANURA_VACIA);
    disparar(fila, columna);
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

string Tablero::getTableroOcultoComoMensaje()
{
    string mensaje;
    char letraFila = 'A';
    for (int fila = 0; fila < LARGO_TABLERO + 2; fila++)
    {
        mensaje.append(fila < LARGO_TABLERO ? string(1, letraFila++) + "\t|\t" : "\t\t");
        for (int columna = 0; columna < LARGO_TABLERO; columna++)
        {
            // si la celda es X, O o ranura vacia se muestra
            // si no, se muestra un espacio en blanco
            if (fila < LARGO_TABLERO)
            {
                if (tablero[fila][columna] == 'X' || tablero[fila][columna] == 'O' || tablero[fila][columna] == RANURA_VACIA)
                {
                    mensaje.append(string(1, tablero[fila][columna]));
                }
                else
                {
                    mensaje.append(string(1, RANURA_VACIA));
                }
            }
            else
            {
                mensaje.append(fila == LARGO_TABLERO ? "-" : to_string(columna));
            }
            mensaje.append("\t");
        }
        mensaje.append("\n");
    }
    return mensaje;
}

void Tablero::imprimirTablero()
{
    cout << getTableroComoMensaje();
}

/** Inicia el tablero pidiendo las coordenadas de los barcos */
void Tablero::iniciarTableroManual()
{
    cout << "Bienvenido a la creacion manual de tablero" << endl;
    cout << "Las coordenadas se ingresan en el formato \"fila,columna,direccion\"" << endl;
    cout << "Donde direccion puede ser \"H\" para horizontal o \"V\" para vertical." << endl;

    for (int i = 0; i < barcos.size(); i++)
    {
        Barco barco = barcos[i];
        cout << "Ingrese las coordenadas para el barco de longitud " << barco.getLargo() << endl;
        bool coordenadasValidas = false;
        while (!coordenadasValidas)
        {
            string entrada;
            getline(cin, entrada);

            // Validar la entrada del usuario
            if (entrada.length() != 5)
            {
                cout << "Entrada invalida. Debe ingresar tres caracteres separados por comas." << endl;
                continue;
            }

            char letraFila = entrada[0];
            char letraColumna = entrada[2];
            char direccion = entrada[4];

            if (!isdigit(letraColumna))
            {
                cout << "Entrada invalida. La columna debe ser un numero." << endl;
                continue;
            }

            int fila = letraFila - 'A';
            int columna = letraColumna - '0' - 1;

            if (fila < 0 || fila >= LARGO_TABLERO || columna < 0 || columna >= LARGO_TABLERO)
            {
                cout << "Entrada invalida. Las coordenadas estan fuera del tablero." << endl;
                continue;
            }

            if (direccion != 'H' && direccion != 'V')
            {
                cout << "Entrada invalida. La direccion debe ser \"H\" o \"V\"." << endl;
                continue;
            }

            if (!esPosibleColocarBarco(barco, fila, columna, direccion))
            {
                cout << "No se puede colocar el barco en esas coordenadas. Por favor, ingrese otras." << endl;
                continue;
            }

            // Colocar el barco en el tablero
            colocarBarco(barco, fila, columna, direccion);
            coordenadasValidas = true;
        }
    }
}

void Tablero::iniciarTableroAutomatico()
{
    for (int i = 0; i < barcos.size(); i++)
    {
        Barco barco = barcos[i];
        bool coordenadasValidas = false;
        while (!coordenadasValidas)
        {
            // Generar coordenadas aleatorias
            int fila = rand() % LARGO_TABLERO;
            int columna = rand() % LARGO_TABLERO;
            char direccion = (rand() % 2 == 0) ? 'H' : 'V';

            if (esPosibleColocarBarco(barco, fila, columna, direccion))
            {
                // Colocar el barco en el tablero
                colocarBarco(barco, fila, columna, direccion);
                coordenadasValidas = true;
            }
        }
    }
}

void Tablero::disparar(int fila, int columna)
{
    if (fila < 0 || fila >= LARGO_TABLERO || columna < 0 || columna >= LARGO_TABLERO)
    {
        cout << "Coordenadas de disparo inválidas." << endl;
        return;
    }

    char &celda = tablero[fila][columna];

    if (celda == RANURA_VACIA)
    {
        celda = 'X'; // Se marca un disparo fallido en el tablero con una 'X'
        cout << "Disparo fallido en fila " << (char)(fila + 'A') << ", columna " << (columna) << "." << endl;
    }
    else if (celda == 'X' || celda == 'O')
    {
        cout << "Ya has disparado a esta ubicación anteriormente." << endl;
    }
    else
    {
        celda = 'O'; // Se marca un disparo exitoso con una 'O'
        cout << "Disparo exitoso en fila " << (char)(fila + 'A') << ", columna " << (columna) << "." << endl;
        vidasBarcos--;
    }
}

bool Tablero::esPosibleColocarBarco(Barco &barco, int fila, int columna, char direccion)
{
    int largo = barco.getLargo();
    int filaFin = fila;
    int columnaFin = columna;

    if (direccion == 'H')
        columnaFin += largo - 1;
    else if (direccion == 'V')
        filaFin += largo - 1;
    else
        return false;

    // Verificar si las coordenadas están dentro del tablero
    if (fila < 0 || fila >= LARGO_TABLERO || columna < 0 || columna >= LARGO_TABLERO ||
        filaFin < 0 || filaFin >= LARGO_TABLERO || columnaFin < 0 || columnaFin >= LARGO_TABLERO)
    {
        return false;
    }

    // Verificar si las ranuras están vacías
    for (int i = fila; i <= filaFin; i++)
    {
        for (int j = columna; j <= columnaFin; j++)
        {
            if (tablero[i][j] != RANURA_VACIA)
            {
                return false;
            }
        }
    }

    return true;
}

void Tablero::colocarBarco(Barco &barco, int fila, int columna, char direccion)
{
    int largo = barco.getLargo();

    if (direccion == 'H')
    {
        for (int j = columna; j < columna + largo; j++)
        {
            tablero[fila][j] = barco.getNombre();
        }
    }
    else if (direccion == 'V')
    {
        for (int i = fila; i < fila + largo; i++)
        {
            tablero[i][columna] = barco.getNombre();
        }
    }
}