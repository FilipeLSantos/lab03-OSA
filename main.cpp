#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Dependecias
#include "include/RegistroAluno.hpp"
#include "include/Buffer.hpp"
#include "include/Arquivo.hpp"

using namespace std;

bool comaparaRegistros(const vector<RegistroAluno>& vec01, const vector <RegistroAluno>& vec02){
    if(vec01.size() != vec02.size()){
        cerr << "ERRO: Quanitidades de registos incompátiveis" << endl;
        return false;
    }

    for(size_t i = 0; i < vec01.size(); i++){
        string nome01 = vec01[i].nome, nome02 = vec02[i].nome;

        nome01.erase(nome01.find_last_not_of(" \t\n\r\f\v") + 1);
        nome01.erase(0, nome01.find_first_not_of(" \t\n\r\f\v"));
        nome02.erase(nome02.find_last_not_of(" \t\n\r\f\v") + 1);
        nome02.erase(0, nome02.find_first_not_of(" \t\n\r\f\v"));

        if(nome01 != nome02 && vec01[i].matricula != vec02[i].matricula && 
            vec01[i].curso != vec02[i].curso){
                cerr << "ERRO DE DADOS: Divergencia no registro " << i << endl;
                cerr << "Esperado: Nome: " << nome01 << ", Matricula: " << vec01[i].matricula << ", Curso: " << vec01[i].curso << endl;
                cerr << "Esperado: Nome: " << nome01 << ", Matricula: " << vec02[i].matricula << ", Curso: " << vec02[i].curso << endl;
                return false;
        }

    }

    return true;
}

void testReadFile(const string& nameFile, Formato formato){
    Arquivo<RegistroAluno> arquivo(nameFile, formato);
    vector<RegistroAluno> registros = arquivo.lerRegistros();

    cout << "Lendo: " << registros.size() << " registros de " << nameFile << ": " << endl;
    
    for(const RegistroAluno& aluno : registros){
        cout << aluno.matricula << " | " << aluno.nome << " | " << aluno.curso << endl;
    }

    cout << "--------------------------------------------------" << endl;
}

vector<RegistroAluno> readCSV(const string& path){
    ifstream fileCSV("data/dados.csv");
    vector <RegistroAluno> alunos;
    
    if(!fileCSV.is_open()){
        cerr << "Erro ao abrir: " << path << " !" << endl;
        return alunos;
    }

    string line;
    getline(fileCSV, line); // pula o cabeçalho

    while (getline(fileCSV, line)){
        stringstream ss(line);
        string nomeCSV, matriculaCSV, cursoCSV;
        RegistroAluno aluno;

        getline(ss, nomeCSV, ';');
        getline(ss, matriculaCSV, ';');
        getline(ss, cursoCSV);

        aluno.nome = nomeCSV;
        aluno.matricula = stoi(matriculaCSV);
        aluno.curso = cursoCSV;

        alunos.push_back(aluno);
    }

    return alunos;
}

int main(){
    
    vector<RegistroAluno> alunos = readCSV("data/dados.csv");
    
    Arquivo<RegistroAluno> arquivoFIXO("alunosFIXO.bin", Formato::FIXO);
    Arquivo<RegistroAluno> arquivoDELIMITADO("alunosDELIMITADO.bin", Formato::DELIMITADO);
    Arquivo<RegistroAluno> arquivoCOMPRIMENTO("alunosCOMPRIMENTO.bin", Formato::COMPRIMENTO);

    for(const RegistroAluno& aluno : alunos){
        arquivoFIXO.adicionarRegistros(aluno);
        arquivoDELIMITADO.adicionarRegistros(aluno);
        arquivoCOMPRIMENTO.adicionarRegistros(aluno);
    }

    testReadFile("alunosFIXO.bin", Formato::FIXO);
    testReadFile("alunosDELIMITADO.bin", Formato::DELIMITADO);
    testReadFile("alunosCOMPRIMENTO.bin", Formato::COMPRIMENTO);

    vector<RegistroAluno> lidosFIXO = arquivoFIXO.lerRegistros();
    vector<RegistroAluno> lidosDELIMITADO = arquivoDELIMITADO.lerRegistros();
    vector<RegistroAluno> lidosCOMPRIMENTO = arquivoCOMPRIMENTO.lerRegistros();

    // Verificação de FIXO
    if(comaparaRegistros(alunos, lidosFIXO))
        cout << "Registros FIXO conferem com o CSV!" << endl;
    else
        cout << "Registros FIXO NÃO conferem com o CSV!" << endl;
    
    // Verificação de DELIMITADO
    if(comaparaRegistros(alunos, lidosDELIMITADO))
        cout << "Registros DELIMITADO conferem com o CSV!" << endl;
    else
        cout << "Registros DELIMITADO NÃO conferem com o CSV!" << endl;
    
    // Verificação de COMPRIMENTO    
    if(comaparaRegistros(alunos, lidosCOMPRIMENTO))
        cout << "Registros COMPRIMENTO conferem com o CSV!" << endl;
    else
        cout << "Registros COMPRIMENTO NÃO conferem com o CSV!" << endl;
    

    return 0;
}