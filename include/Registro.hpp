#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include "Buffer.hpp"

using namespace std;

const int TAM_NOME = 25; // tamanho fixo do campo nome
const int TAM_REGISTRO = 29; // tamanho fixo do registro (nome + idade)

enum Formato { FIXO, DELIMITADO, COMPRIMENTO };

class Registro  {
    public:
        Registro() = default;
        ~Registro();

    public:
        virtual void pack (Buffer& buffer, Formato formato) const = 0;
        virtual void unpack (Buffer& buffer, Formato formato) = 0;
        string getChave ();
        int getTamanhoFixo ();

};

#endif