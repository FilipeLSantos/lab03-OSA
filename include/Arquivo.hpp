#ifndef ARQUIVO_HPP
#define ARQUIVO_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Buffer.hpp"
#include "Registro.hpp"
#include <type_traits> // para is_base_of

/*  As implementações foram realizadas no header
para evitar erro de linkagem da classe especializada
*/
template <typename T>
class Arquivo   {

    static_assert(is_base_of<Registro,T>::value, "T deve herdar de Registro."); // is_base_of <Tipo, Derivado>
    private:
        string nomeDoArquivo;
        Formato formato;
        char delimitador;

    public:
        Arquivo(const string& nome, Formato fmt, char delim = '|') : nomeDoArquivo(nome), formato(fmt), delimitador(delim) {}
        Arquivo() = default;
        ~Arquivo() = default;
    
        void adicionarRegistros (T reg){
            // abre o arquivo em modo append e binário para todos os tipos
            ofstream arquivoSaida(nomeDoArquivo, ios::app | ios::binary);
                if(!arquivoSaida){
                    cerr << "Não foi possível abrir o arquivo." << endl;
                }

            Buffer buffer;
            reg.pack(buffer, formato);
            buffer.write(arquivoSaida);
        }
        
        vector<T> lerRegistros () {
            vector<T> registros;
            ifstream arquivoEntrada(nomeDoArquivo, ios::binary);
            if(!arquivoEntrada) {
                cerr << "ERRO: Nâo foi possível ler o arquivo. Erro lançado em arquivo::lerRegistros." << endl;
                return registros;
            }

            /*
            Buffer buffer;
            switch (formato) {

                case Formato::FIXO: {
                    T regTemporario;
                    int tamanhoFixo = regTemporario.getTamanhoFixo();
                    while (buffer.read(arquivoEntrada,tamanhoFixo)) {
                        T reg;
                        reg.unpack(buffer, formato);
                        registros.push_back(reg);
                    }
                    break;
                }

                case Formato::DELIMITADO:
                case Formato::COMPRIMENTO: {
                    while (buffer.read(arquivoEntrada)) {
                        T reg;
                        reg.unpack(buffer, formato);
                        registros.push_back(reg);
                    }
                    break;
                }
            
            default:
                throw runtime_error("ERRO EM ARQUIVO: lerRegistros, formato inválido.");
                break;
            }
            */


            if(formato == Formato::DELIMITADO) {
                string linha;
                while (getline(arquivoEntrada,linha)){
                    if (linha.empty()) continue; 

                    Buffer buffer;
                    buffer.pack(linha);

                    T registroLido;
                    registroLido.unpack(buffer,formato);
                    registros.push_back(registroLido);
                }
            }
            else if(formato == Formato::FIXO) {
                T reg;
                size_t tamanhoFixoRegistro = reg.getTamanhoFixo();
                Buffer buffer;
                while (buffer.read(arquivoEntrada,tamanhoFixoRegistro)) {
                    T registroLido;
                    registroLido.unpack(buffer,formato);
                    registros.push_back(registroLido); 
                }
            }
            else {
                Buffer buffer;
                while(buffer.read(arquivoEntrada)) {
                    T registroLido;
                    registroLido.unpack(buffer,formato);
                    registros.push_back(registroLido);
                }
            }
             
            return registros;
        }
};


#endif