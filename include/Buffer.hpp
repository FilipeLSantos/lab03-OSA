#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Registro.hpp"
using namespace std;

class Buffer {
    private:
        vector<char> data;
        int ponteiro;

    public:
        Buffer(/* args */);
        ~Buffer();

    public:        
        void packFixo (string str, int tamanho);
        string unpackFixo (int tamanho);

        void packDelimitado (char delim);
        string unpackDelimitado (char delim);
        
        void packComprimento (string str);
        string unpackComprimento ();

        void pack (int valor);
        int unpackInt();

        bool read (istream stream, int tamanho);
        bool read (istream stream);
        void write (ostream stream);

        void clear();

};

#endif