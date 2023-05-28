#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef COMUN_H
#define COMUN_H
namespace comun
{

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
    vector<string> dividir(const string &str, char delim)
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

}
#endif