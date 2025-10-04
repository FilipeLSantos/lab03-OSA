#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <iostream>
#include <string>
#include "Buffer.hpp"

using namespace std;

enum class Formato { 
    FIXO,
    DELIMITADO,
    COMPRIMENTO 
};

class Registro  {
    public:
        Registro() = default;
        virtual ~Registro() = default;

    public:
        virtual void pack (Buffer& buffer, Formato formato) const = 0;
        virtual void unpack (Buffer& buffer, Formato formato) = 0;
        virtual string getChave () const = 0;
        virtual int getTamanhoFixo () const = 0;

};

#endif