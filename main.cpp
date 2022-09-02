#include <iostream>
#include <fstream>
#include "include/Registro.h"

int main()
{
     // Buffers de leitura de linha
    std::ifstream entrada("anime.csv");
    std::string linha;

    std::vector<Registro> dados_entrada; // Declara��o do vetor de registros que cont�m a database

    // Leitura do arquivo
    while(std::getline(entrada, linha)){ // Pega linha do arquivo
        Registro reg(linha); // Cria registro com dados da linha
        dados_entrada.push_back(reg); // Insere novo registro no vetor de registros
    }

    return 0;
}
