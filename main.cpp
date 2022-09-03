#include <iostream>
#include <fstream>
#include "include/Registro.h"

int main()
{
     // Buffers de leitura de linha
    std::ifstream entrada_anime("anime.csv");
    std::ifstream entrada_manga("manga.csv");
    std::string linha;

    std::vector<Anime> dados_entrada_anime; // Declaracao do vetor de registros que contem a database
    std::vector<Manga> dados_entrada_manga;

    // Leitura do arquivo
    while(std::getline(entrada_anime, linha)){ // Pega linha do arquivo
        Anime reg1(linha); // Cria registro com dados da linha
        dados_entrada_anime.push_back(reg1); // Insere novo registro no vetor de registros
    }
    while(std::getline(entrada_manga, linha)){
        Manga reg2(linha);
        dados_entrada_manga.push_back(reg2);
    }
    std::cout << dados_entrada_manga[0].getTitle() << std::endl;
    std::cout << dados_entrada_manga[0].getRanked() << std::endl;
    std::cout << dados_entrada_manga[0].getGenres() << std::endl;
    return 0;
}
