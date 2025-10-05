#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Registro.hpp"

using namespace std;

class Buffer {
    private:
        vector<char> data;
        int ponteiro = 0;

    public:
        Buffer(/* args */);
        ~Buffer();

    public:      
        /* Métodos sobrecarregados, 
        responsabilidade da corretude da serialização
        na implementação concreta de registro
        */
        void pack (string str, int tamanho) ;
        string unpack (int tamanho);

        void pack (char delim);
        string unpackDelimitado (char delim);
        
        void pack (string str);
        string unpackComprimento ();

        void pack (int valor);
        int unpackInt();
        
        void write (ostream stream);
        bool writeFixo(ostream stream); 

        bool read (istream stream, int tamanho);
        bool read (istream stream);

        void clear();

};

#endif