#ifndef REGISTROALUNO_HPP
#define REGISTROALUNO_HPP

#include <string>

using namespace std;

class RegistroAluno{
    public:
        int matricula;
        string nome;
        string curso;

    public:
        void pack();
        void unpack();
        string getChave();
        int getTamanhoFixo();

};

#endif