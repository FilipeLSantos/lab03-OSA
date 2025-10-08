#include "../include/Buffer.hpp"

Buffer::~Buffer() {}
Buffer::Buffer() : ponteiro(0) {}

// ---------------- IMPLEMENTAçÃO DE PACK -----------------
void Buffer::pack(const char* bytes, size_t tamanho){
    data.insert(data.end(), bytes, bytes + tamanho);
}

void Buffer::pack(const string& str) {
    pack(str.c_str(), str.length()); // obtém o ponteiro para os char da string e seu tam, e insere os bytes da string sem '\0' 
    // para incluir o '\0' é necessário "strng.length() + 1"
}

void Buffer::pack(int valor) {
    pack(reinterpret_cast<const char*>(&valor), sizeof(int));
}

void Buffer::pack(char delim) {
    data.push_back(delim);
}

// ----------------- IMPLEMENTAçÃO DE UNPACK ----------------- 
int Buffer::unpackInt() {
    if(ponteiro + sizeof(int) > data.size()){
        throw runtime_error("ERRO EM UNPACK: Buffer Underflow, falha ao tentar ler uma string, o buffer não têm bytes suficientes.");
    }

    int valor;
    memcpy(&valor, &data[ponteiro], sizeof(int));
    ponteiro += sizeof(int);

    return valor;
}

string Buffer::unpack(int tamanho){
    if(ponteiro + tamanho > data.size()) {
        throw runtime_error("ERRO EM UNPACK: Buffer Underflow, falha ao tentar ler uma string, o buffer não têm bytes suficientes.");
    }
    
    string field(&data[ponteiro], tamanho);
    ponteiro += tamanho;
    // remove os espaços (\0) à direita
    while(!field.empty() && field.back() == '\0') {
        field.pop_back();
    }
    
    return field;
}

// string Buffer::unpackComprimento() {}
// string Buffer::unpackDelimitado(char delim) {}


// ----------------- IMPLEMENTAÇÃO DO I/O -----------------
bool Buffer::write(ostream& stream) {
    size_t tamanho = data.size();
    stream.write(reinterpret_cast<const char*>(&tamanho), sizeof(tamanho));
    stream.write(data.data(), tamanho);
    return stream.good();
}

bool Buffer::writeFixo(ostream& stream) {
    stream.write(data.data(), data.size());
    return stream.good();
}

bool Buffer::read(istream& stream, int tamanho) {
    clear();
    data.resize(tamanho);
    stream.read(data.data(), tamanho);
    return stream.gcount() == tamanho;
}

bool Buffer::read(istream& stream) {
    clear();
    size_t tamanho;
    stream.read(reinterpret_cast<char*>(&tamanho), sizeof(tamanho));
    if(stream.gcount() == 0) return false; // fim do arquivo, retorno 0 na ultima operação de input nao-formatada

    data.resize(tamanho);
    stream.read(data.data(), tamanho);
    return stream.gcount() == tamanho; // retorna se a qtd de chars da ultima operação de input é igual ao tam de leitura
}


// ----------------- IMPLEMENTAÇÃO DA LIMPEZA DO BUFFER -----------------
void Buffer::clear() {
    data.clear();
    ponteiro = 0;
}

size_t Buffer::tamTotal() {
    return this->data.size();
}
