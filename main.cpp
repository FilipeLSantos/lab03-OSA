#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Dependecias
#include "include/RegistroAluno.hpp"
#include "include/Buffer.hpp"
#include "include/Arquivo.hpp"

using namespace std;

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

    return 0;
}