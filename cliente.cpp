#include <iostream>
#include <string>
#include "clases/Comun.h"

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 3 || !comun::esNumero(argv[2]) || !comun::esIPValida(argv[1])){
        cout << "ERROR: Parametros invalidos" << endl;
        exit(1);
    }
    const string IP = argv[1];
    const string PUERTO = argv[2];
    return 0;
}