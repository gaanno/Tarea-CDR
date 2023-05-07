#!/bin/bash

# cambia de ubicacion al directorio donde se encuentra el script
clear && 
cd $(dirname $0) && 
cd .. &&
rm cliente;
make cliente &&
./cliente 192.168.0.190 50000
