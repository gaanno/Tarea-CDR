CC = g++
CFLAGS = -std=c++17
CLASESSERVIDOR = clases/Tablero/Tablero.h clases/Barco/Barco.h clases/Comun.h clases/Conexiones/ConexionServidor.h
CLASESCLIENTE = clases/Comun.h clases/Conexiones/ConexionCliente.h

all: cliente servidor

cliente: cliente.cpp $(CLASESCLIENTE)
	$(CC) $(CFLAGS) -o cliente cliente.cpp

servidor: servidor.cpp $(CLASESSERVIDOR)
	$(CC) $(CFLAGS) -o servidor servidor.cpp  -lpthread -fopenmp

clean:
	rm -f cliente servidor
