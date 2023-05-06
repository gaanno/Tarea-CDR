#include <iostream>
#include <cctype>
#include <string>
#include <bits/stdc++.h>

#define DELIM "."
using namespace std;

namespace comun
{

    // verifica si el string es de tipo entero
    bool esNumero(const std::string &str)
    {
        if (str.length() == 0)
        {
            return false;
        }
        for (char const &val : str)
        {
            if (std::isdigit(val) == 0)
            {
                return false;
            }
        }
        return true;
    }

    // verifica si la ip es valida
    // https://www.geeksforgeeks.org/program-to-validate-an-ip-address/
    /* function to check whether the
       string passed is valid or not */
    bool parteValida(char *s)
    {
        int n = strlen(s);

        // if length of passed string is
        // more than 3 then it is not valid
        if (n > 3)
            return false;

        // check if the string only contains digits
        // if not then return false
        for (int i = 0; i < n; i++)
            if ((s[i] >= '0' && s[i] <= '9') == false)
                return false;
        string str(s);

        // if the string is "00" or "001" or
        // "05" etc then it is not valid
        if (str.find('0') == 0 && n > 1)
            return false;
        stringstream geek(str);
        int x;
        geek >> x;

        // the string is valid if the number
        // generated is between 0 to 255
        return (x >= 0 && x <= 255);
    }

    /* return 1 if IP string is
    valid, else return 0 */
    int esIPValida(char *ip_str)
    {
        if (strcmp(ip_str, "localhost") == 0 || strcmp(ip_str, "127.0.0.1") == 0)
        {
            string localhost = "127.0.0.1";
            strcpy(ip_str, localhost.c_str());
            return true;
        }
        // if empty string then return false
        if (ip_str == NULL)
            return 0;
        int i, num, dots = 0;
        int len = strlen(ip_str);
        int count = 0;

        // the number dots in the original
        // string should be 3
        // for it to be valid
        for (int i = 0; i < len; i++)
            if (ip_str[i] == '.')
                count++;
        if (count != 3)
            return false;

        // See following link for strtok()

        char *ptr = strtok(ip_str, DELIM);
        if (ptr == NULL)
            return 0;

        while (ptr)
        {

            /* after parsing string, it must be valid */
            if (parteValida(ptr))
            {
                /* parse remaining string */
                ptr = strtok(NULL, ".");
                if (ptr != NULL)
                    ++dots;
            }
            else
                return 0;
        }

        /* valid IP string must contain 3 dots */
        // this is for the cases such as 1...1 where
        // originally the no. of dots is three but
        // after iteration of the string we find
        // it is not valid
        if (dots != 3)
            return 0;
        return 1;
    }
}
