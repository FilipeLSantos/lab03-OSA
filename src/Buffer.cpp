#include "include\Buffer.hpp"

// Registro FIXO
void Buffer::pack(string str, int tamanho){
    if(str.size() < tamanho)
        str.append(tamanho - str.size(), '\0');
    else if(str.size() > tamanho)
        str = str.substr(0, tamanho);
    //data.append(str); Precisa consertar
}

string Buffer::unpack(int tamanho){
    if(ponteiro + tamanho > data.size())
        return "";
    
    //string field = data.substr(ponteiro, tamanho); preciso saber como faz essa mesma coisa para um vector de char
    ponteiro += tamanho;

    field.erase(field.find('\0')); // remove os espaços (\0) à direita
    
    return field;
}

// Registro DELIMITADO
void Buffer::pack(char delim) {}
string Buffer::unpackDelimitado(char delim) {}

// Registro COMPRIMENTO
void Buffer::pack(string str) {}
string Buffer::unpackComprimento() {}

void Buffer::pack(int valor) {}
int Buffer::unpackInt() {}

void Buffer::write(ostream stream) {
    size_t tamanho = data.size();
    stream.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    stream.write(data.data(), tamanho);
    return stream.good();
}

bool Buffer::writeFixo(ostream stream) {
    stream.write(data.data(), data.size());
    return stream.good();
}

bool Buffer::read(istream stream, int tamanho) {
    clear();
    data.resize(tamanho);
    stream.read(data.data(), tamanho);
    return stream.gcount() == tamanho;
}

bool Buffer::read(istream stream) {
    clear();
    size_t tamanho;
    stream.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    if(stream.gcount() == 0) return false; // fim do arquivo, retorno 0 na ultima operação de input nao-formatada

    data.resize(tamanho);
    stream.read(data.data(), tamanho);
    return stream.gcount() == tamanho; // retorna se a qtd de chars da ultima operação de input é igual ao tam de leitura
}

void Buffer::clear() {
    data.clear();
    ponteiro = 0;
}
