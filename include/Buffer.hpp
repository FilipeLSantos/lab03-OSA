#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
//#include "Registro.hpp"

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
        responsabilidade da serialização
        na implementação concreta de registro
        */

        // PACK
        void pack (const char* bytes, size_t tamanho) ;
        void pack (const string& str);
        void pack (int valor);
        void pack (char delim);
        
        // UNPACK
        string unpack (int tamanho);
        int unpackInt();

        // void pack (char delim);
        // string unpackDelimitado (char delim);
        // string unpackComprimento ();

        // I/O 
        bool write (ostream& stream);
        bool writeFixo(ostream& stream); 
        bool read (istream& stream, int tamanho);
        bool read (istream& stream);

        // CLEAR
        void clear();

        // FUNçÕES AUXILIARES
        size_t tamTotal();
};

#endif