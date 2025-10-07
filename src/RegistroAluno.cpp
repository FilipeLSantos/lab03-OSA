#include "../include/RegistroAluno.hpp"
#include <sstream>

/* 
Responsabilidade de Serialização toda na classe Concreta
*/

// --- GETTERS ---
string RegistroAluno::getChave() const {
    return to_string(this->matricula);
};

int RegistroAluno::getTamanhoFixo() const {
    return sizeof(int) + NOME + CURSO;
};

// --- SERIALIZAçÃO ---
void RegistroAluno::pack(Buffer& buffer, Formato formato) const {
    buffer.clear(); // SEMPRE É PRECISO LIMPAR O BUFFER ANTES DE INICIAR

    switch (formato){
        //FIXO
        case Formato::FIXO: {
            buffer.pack(this->matricula);
            string nomeFixo = this->nome;
            nomeFixo.resize(NOME, ' '); // GARANTE A QUANTIDADE DE BYTES FIXA DE NOMES 
            buffer.pack(nomeFixo); 

            string cursoFixo = this->curso;
            cursoFixo.resize(CURSO, ' ');
            buffer.pack(cursoFixo); 
            break;
        }

        //DELIMITADO
        case Formato::DELIMITADO: {
            buffer.pack(to_string(this->matricula));
            buffer.pack("|");
            buffer.pack(this->nome);
            buffer.pack("|");
            buffer.pack(this->curso);
            break;
        }
            
        //COMPRIMENTO
        case Formato::COMPRIMENTO: {
            buffer.pack(this->matricula);

            int tamNome = this->nome.length();
            buffer.pack(tamNome);
            buffer.pack(this->nome);
   
            int tamCurso = this->curso.length();
            buffer.pack(tamCurso);
            buffer.pack(this->curso);
   
            break;
        }
            
        default:
            throw runtime_error("ERRO EM PACK - REGISTROALUNO: Formato de serialização inválido");
            break;
    }
}

void RegistroAluno::unpack(Buffer& buffer, Formato formato) {
    switch (formato) {
        case Formato::FIXO: {
            break;
    }
        case Formato::DELIMITADO: {

            string linha = buffer.unpack(buffer.tamTotal());

            stringstream linhaBuffer(linha);
            string campo;

            getline(linhaBuffer,campo,'|');
            this->matricula = stoi(campo);
            
            getline(linhaBuffer, campo, '|');
            this->nome = campo;

            getline(linhaBuffer,campo);
            this->curso = campo;

            break;
    }
        case Formato::COMPRIMENTO: {
            this->matricula = buffer.unpackInt();

            int tamNome = buffer.unpackInt();
            this->nome = buffer.unpack(tamNome);
        
            // falta o curso
            int tamCurso = buffer.unpackInt();
            this->curso = buffer.unpack(tamCurso);
            break;
    }
        
    default:
        break;
    }


};

