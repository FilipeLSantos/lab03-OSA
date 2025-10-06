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
        void pack(Buffer& buffer, Formato formato) const override;
        void unpack(Buffer& buffer, Formato formato) override;
        string getChave() const override;
        int getTamanhoFixo() const override;

};

#endif