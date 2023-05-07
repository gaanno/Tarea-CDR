#!/bin/bash

# cambia de ubicacion al directorio donde se encuentra el script
clear && 
cd $(dirname $0) && 
cd .. &&
rm servidor;
make servidor &&
./servidor 50000

