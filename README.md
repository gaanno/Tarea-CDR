# Tarea-CDR
Tarea de comunicación de datos y redes


AUTORES:

- Gabriel Norambuena
- René Sánchez

Descripción:

Se desarrolló un juego de battleship en un entorno de cliente-servidor, con la finalidad de ejecutar múltiples instancias de este juego al mismo tiempo. Entre las carácterísticas que permiten que esto sea posible, se encuentra el uso de un vector de barcos, de modo que cada instancia del juego tenga su propio conjuto de barcos que se puedan gestionar de manera independiente.

Uso Makefile:

Para compilar cliente y servidor
- make

Compilar solo servidor
- make servidor

Compilar solo cliente
- make cliente

Eliminar archivos cliente y servidor
- Make clean

Instucciones de uso:

- ./servidor PUERTO

- ./cliente IP PUERTO

En donde < IP > es la direccion ip que se quiere usar.
En donde < PUERTO > es el puerto que se quiere usar.

- Ejemplo de uso

./servidor 50000
./cliente 0.0.0.0 50000