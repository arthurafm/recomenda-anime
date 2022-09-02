#include <iostream>
#include <fstream>
#include "include/Registro.h"

int main()
{
     // Buffers de leitura de linha
    std::ifstream entrada("anime.csv");
    std::string linha;

    std::vector<Anime> dados_entrada; // Declaracao do vetor de registros que contem a database

    // Leitura do arquivo
    while(std::getline(entrada, linha)){ // Pega linha do arquivo
        Anime reg(linha); // Cria registro com dados da linha
        dados_entrada.push_back(reg); // Insere novo registro no vetor de registros
    }
    return 0;
}
