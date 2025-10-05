#include "../include/RegistroAluno.hpp"

void RegistroAluno::pack(Buffer buffer, Formato formato){

    int opFormato = (int)formato;

    switch (opFormato){
        //FIXO
        case 0:
            break;
        //DELIMITADO
        case 1:
            break;
        //COMPRIMENTO
        case 2:
            break;
        
        default:
            cerr << "Formato invalido !";
            break;
    }
};

void RegistroAluno::unpack(Buffer buffer, Formato formato){};

string RegistroAluno::getChave(){};

int RegistroAluno::getTamanhoFixo(){};