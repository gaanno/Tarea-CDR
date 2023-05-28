CC = g++
CFLAGS = -fopenmp
CLASESSERVIDOR = clases/Tablero/Tablero.h clases/Barco/Barco.h clases/Comun.h clases/Conexiones/ConexionServidor.h
CLASESCLIENTE = clases/Comun.h clases/Conexiones/ConexionCliente.h

all: cliente servidor

cliente: cliente.cpp $(CLASESCLIENTE)
	$(CC)  -o cliente cliente.cpp

servidor: servidor.cpp $(CLASESSERVIDOR)
	export CFLAGS
	$(CC) $(CFLAGS) -o servidor servidor.cpp  -lpthread

clean:
	rm -f cliente servidor
