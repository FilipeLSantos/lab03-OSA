#include "include\Buffer.hpp"

void Buffer::pack(string str, int tamanho) {}
string Buffer::unpack(int tamanho) {}

void Buffer::pack(char delim) {}
string Buffer::unpackDelimitado(char delim) {}

void Buffer::pack(string str) {}
string Buffer::unpackComprimento() {}

void Buffer::pack(int valor) {}
int Buffer::unpackInt() {}

bool Buffer::write(ostream stream) {
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
