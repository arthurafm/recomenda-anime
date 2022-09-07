#include "..\include\Arquivos.h"
#include <iostream>
#include <fstream>
#include "..\include\Registro.h"


// Fun��o para saber se o arquivo existe ou n�o
short ArquivoExiste(std::string name){
    FILE *file = fopen(name.c_str(), "r");
    if(file){
        fclose(file);
        return 0;
    }
    else{
        return -1;
    }
}

void ProcessaArquivoCSV(){
    // Buffers de leitura de linha
    std::ifstream entrada_anime("anime.csv");
    std::ifstream entrada_manga("manga.csv");
    std::string linha;

    // Declaracao do vetores de registros que contem a database
    std::vector<Anime> dados_entrada_anime;
    std::vector<Manga> dados_entrada_manga;

    // Leitura do arquivo
    while(std::getline(entrada_anime, linha)){
        Anime reg1(linha);
        dados_entrada_anime.push_back(reg1);
    }
    while(std::getline(entrada_manga, linha)){
        Manga reg2(linha);
        dados_entrada_manga.push_back(reg2);
    }

    /* 2. Ap�s coletar ou extrair os dados, o programa dever� usar arquivos bin�rios pr�prios que armazenar�o todos os dados, independentes dos arquivos originais.
          Tais arquivos poder�o ser organizados tanto de forma sequencial, quanto serial. Por�m � obrigat�rio que sejam implementados �ndices de acesso que auxiliem
          na consulta a esses dados. */

    // Manipula��o de arquivos bin�rios
    std::ofstream bin_anime, bin_manga;
    bin_anime.open("bin_anime.bin", std::ios::binary);
    bin_manga.open("bin_manga.bin", std::ios::binary);
    for(unsigned int i = 0; i < dados_entrada_anime.size(); i++){
        bin_anime.write(reinterpret_cast<char *>(&(dados_entrada_anime[i])), sizeof(dados_entrada_anime[i]));
    }
    for(unsigned int i = 0; i < dados_entrada_manga.size(); i++){
        bin_manga.write(reinterpret_cast<char *>(&(dados_entrada_manga[i])), sizeof(dados_entrada_manga[i]));
    }
    bin_anime.close();
    bin_manga.close();
}
