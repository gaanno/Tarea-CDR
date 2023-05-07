#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#include <netdb.h>

#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>


using namespace std;

#ifndef COMUN_H
#define COMUN_H
namespace comun
{
    bool esIPLocal(string ip)
    {
    char host[256];
    int hostname = gethostname(host, sizeof(host)); 
    struct hostent *host_entry = gethostbyname(host); 
    char* IPLocal = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
    return ip == IPLocal;
        
    }
    // verifica si el string es de tipo entero
    bool esNumero(const std::string &str)
    {
        for (char const &val : str)
        {
            if (std::isdigit(val) == 0)
            {
                return false;
            }
        }
        return (str.length() > 0) ? true : false;
    }

    // Función para dividir la string `str` usando un delimitador dado
    vector<string> split(const string &str, char delim)
    {
        auto i = 0;
        vector<string> list;

        auto pos = str.find(delim);

        while (pos != string::npos)
        {
            list.push_back(str.substr(i, pos - i));
            i = ++pos;
            pos = str.find(delim, pos);
        }

        list.push_back(str.substr(i, str.length()));

        return list;
    }

    // Función para validar una dirección IP
    bool esIPValida(string ip)
    {
        if (esIPLocal(ip))
        {
            return true;
        }

        // dividir la string en tokens
        vector<string> list = split(ip, '.');

        // si el tamaño del token no es igual a cuatro
        if (list.size() != 4)
        {
            return false;
        }

        // validar cada ficha
        for (string str : list)
        {
            // verifica que la string sea un número o no, y los números
            // están en el rango válido
            if (!esNumero(str) || stoi(str) > 255 || stoi(str) < 0)
            {
                return false;
            }
        }

        return true;
    }
}
#endif