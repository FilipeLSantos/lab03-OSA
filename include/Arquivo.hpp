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

    public:
        Arquivo(const string& nome, Formato fmt, char delim = '|') : nomeDoArquivo(nome), formato(fmt), delimitador(delim);
        Arquivo() = default;
        ~Arquivo();
    
        void adicionarRegistros (T reg){
            // abre o arquivo em modo append e binário para todos os tipos
            ofstream arquivoSaida(nomeDoArquivo, ios::app | ios::binary);
                if(!outfile){
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

            if(formato == Formato::FIXO) {
                T reg;
                size_t tamanhoFixoRegistro = reg.getTamanhoFixo();
                Buffer buffer;
                while (buffer.read(nomeDoArquivo,tamanhoFixoRegistro)) {
                    T registroLido;
                    registroLido.unpack(buffer,formato);
                    registros.push_back(registroLido); 
                }
            }
            else {
                Buffer buffer;
                while(buffer.read(nomeDoArquivo)) {
                    T registroLido;
                    registroLido.unpack(buffer,formato);
                    registros.push_back(registroLido);
                }
            }
             
            return registros;
        }
};


#endif