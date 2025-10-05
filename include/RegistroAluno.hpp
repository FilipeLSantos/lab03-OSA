#ifndef REGISTROALUNO_HPP
#define REGISTROALUNO_HPP

#include "../include/Registro.hpp"

#include <string>

using namespace std;
const int NOME = 25;
const int MATRICULA = 8;
const int CURSO = 4;

class RegistroAluno : public Registro{
    public:
        int matricula;
        string nome;
        string curso;

    public:
        void pack(Buffer buffer, Formato formato);
        void unpack(Buffer buffer, Formato formato);
        string getChave();
        int getTamanhoFixo();

};

#endif