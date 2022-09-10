#include "../include/Operacoes.h"

void buscaAnimePorID(int id){
    Anime buffer_anime;
    BPTree buffer_bpt;
    int buffer_ch, buffer_in;
    std::ifstream arq, arq_bpt;
    arq_bpt.open("bpt_anime.bin", std::ios::binary);
    while(!(arq_bpt.eof())){
        arq_bpt.read((char *) &buffer_ch, sizeof(int));
        arq_bpt.read((char *) &buffer_in, sizeof(int));
        buffer_bpt.insereBPTree(buffer_ch, buffer_in);
    }
    buffer_in = buffer_bpt.procuraBPTree(id);
    arq_bpt.close();
    if(buffer_in == -1){
        std::cout << "ID invalido" << std::endl << std::endl;
    }
    else{
        arq.open("anime.bin", std::ios::binary);
        for(int i = 0; i <= buffer_in; i++){
            arq.read((char *) &buffer_anime, sizeof(Anime));
        }
        arq.close();
        buffer_anime.printaAnime();
    }
}

void buscaMangaPorID(int id){
    Manga buffer_manga;
    BPTree buffer_bpt;
    int buffer_ch, buffer_in;
    std::ifstream arq, arq_bpt;
    arq_bpt.open("bpt_manga.bin", std::ios::binary);
    while(!(arq_bpt.eof())){
        arq_bpt.read((char *) &buffer_ch, sizeof(int));
        arq_bpt.read((char *) &buffer_in, sizeof(int));
        buffer_bpt.insereBPTree(buffer_ch, buffer_in);
    }
    buffer_in = buffer_bpt.procuraBPTree(id);
    arq_bpt.close();
    if(buffer_in == -1){
        std::cout << "ID invalido" << std::endl << std::endl;
    }
    else{
        arq.open("manga.bin", std::ios::binary);
        for(int i = 0; i <= buffer_in; i++){
            arq.read((char *) &buffer_manga, sizeof(Manga));
        }
        arq.close();
        buffer_manga.printaManga();
    }
}

void ordenaAnime(){
    // Leitura do arquivo
    std::vector<Anime> dados_entrada_anime;
    Anime buffer_anime;
    std::ifstream arq_entrada;
    arq_entrada.open("anime.bin", std::ios::binary);
    while(!(arq_entrada.eof())){
        arq_entrada.read((char *) &buffer_anime, sizeof(Anime));
        dados_entrada_anime.push_back(buffer_anime);
    }
    arq_entrada.close();

    // Ordenação via shellSort usando o ranking como parametro
    int tamanhogaps;
    int n = dados_entrada_anime.size();
    int i = 0, j, k, l, h = 1;
    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(n);
    tamanhogaps = sequenciaDeGaps.size();
    do{
        i++;
    }while(i < tamanhogaps);
    i = i - 2;
    h = sequenciaDeGaps[i];
    while(h >= 1){
        for(j = 0; j < h; j++){
            for(k = j + h; k < n; k = k + h){
                if((dados_entrada_anime[k].ranked == -1) || (dados_entrada_anime[k].ranked == 0)){ // Caso a informação for desconhecida, joga para o fim
                    dados_entrada_anime[k].ranked = 99999;
                }
                buffer_anime = dados_entrada_anime[k];
                l = k - h;
                while((l >= 0) && (dados_entrada_anime[l].ranked > buffer_anime.ranked)){
                    dados_entrada_anime[l + h] = dados_entrada_anime[l];
                    l = l - h;
                }
                dados_entrada_anime[l + h] = buffer_anime;
            }
        }
        if(i != 0){
            i--;
            h = sequenciaDeGaps[i];
        }
        else{
            h = 0;
        }
    }

    // Escrita no arquivo binario
    BPTree bpt_anime;
    std::ofstream bin_anime;
    bin_anime.open("anime.bin", std::ios::binary);
    for(unsigned int i = 0; i < dados_entrada_anime.size(); i++){
        if(dados_entrada_anime[i].ranked == 99999){ // Correção
            dados_entrada_anime[i].ranked = -1;
        }
        bpt_anime.insereBPTree(dados_entrada_anime[i].id, i);
        bin_anime.write(reinterpret_cast<char *>(&(dados_entrada_anime[i])), sizeof(dados_entrada_anime[i]));
    }
    bin_anime.close();
    char bpt_anime_arq[] = "bpt_anime.bin", writeb[] = "wb";
    FILE *bin_bpt_anime = NULL;
    AbreArquivo(&bin_bpt_anime, bpt_anime_arq, writeb);
    bpt_anime.armazenaBPTree(bpt_anime.getRaiz(), bin_bpt_anime);
    fclose(bin_bpt_anime);
    std::cout << std::endl << "TOP 3 ANIMES:" << std::endl;
    dados_entrada_anime[0].printaAnime();
    dados_entrada_anime[1].printaAnime();
    dados_entrada_anime[2].printaAnime();
}

void ordenaAnimeInverso(){
    // Leitura do arquivo
    std::vector<Anime> dados_entrada_anime;
    Anime buffer_anime;
    std::ifstream arq_entrada;
    arq_entrada.open("anime.bin", std::ios::binary);
    while(!(arq_entrada.eof())){
        arq_entrada.read((char *) &buffer_anime, sizeof(Anime));
        dados_entrada_anime.push_back(buffer_anime);
    }
    arq_entrada.close();

    // Ordenação via shellSort usando o ranking como parametro
    int tamanhogaps;
    int n = dados_entrada_anime.size();
    int i = 0, j, k, l, h = 1;
    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(n);
    tamanhogaps = sequenciaDeGaps.size();
    do{
        i++;
    }while(i < tamanhogaps);
    i = i - 2;
    h = sequenciaDeGaps[i];
    while(h >= 1){
        for(j = 0; j < h; j++){
            for(k = j + h; k < n; k = k + h){
                buffer_anime = dados_entrada_anime[k];
                l = k - h;
                while((l >= 0) && (dados_entrada_anime[l].ranked < buffer_anime.ranked)){
                    dados_entrada_anime[l + h] = dados_entrada_anime[l];
                    l = l - h;
                }
                dados_entrada_anime[l + h] = buffer_anime;
            }
        }
        if(i != 0){
            i--;
            h = sequenciaDeGaps[i];
        }
        else{
            h = 0;
        }
    }

    // Escrita no arquivo binario
    BPTree bpt_anime;
    std::ofstream bin_anime;
    bin_anime.open("anime.bin", std::ios::binary);
    for(unsigned int i = 0; i < dados_entrada_anime.size(); i++){
        bpt_anime.insereBPTree(dados_entrada_anime[i].id, i);
        bin_anime.write(reinterpret_cast<char *>(&(dados_entrada_anime[i])), sizeof(dados_entrada_anime[i]));
    }
    bin_anime.close();
    char bpt_anime_arq[] = "bpt_anime.bin", writeb[] = "wb";
    FILE *bin_bpt_anime = NULL;
    AbreArquivo(&bin_bpt_anime, bpt_anime_arq, writeb);
    bpt_anime.armazenaBPTree(bpt_anime.getRaiz(), bin_bpt_anime);
    fclose(bin_bpt_anime);
    std::cout << std::endl << "BOTTOM 3 ANIMES :" << std::endl;
    dados_entrada_anime[0].printaAnime();
    dados_entrada_anime[1].printaAnime();
    dados_entrada_anime[2].printaAnime();
}

void ordenaManga(){
    // Leitura do arquivo
    std::vector<Manga> dados_entrada_manga;
    Manga buffer_manga;
    std::ifstream arq_entrada;
    arq_entrada.open("manga.bin", std::ios::binary);
    while(!(arq_entrada.eof())){
        arq_entrada.read((char *) &buffer_manga, sizeof(Manga));
        dados_entrada_manga.push_back(buffer_manga);
    }
    arq_entrada.close();

    // Ordenação via shellSort usando o ranking como parametro
    int tamanhogaps;
    int n = dados_entrada_manga.size();
    int i = 0, j, k, l, h = 1;
    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(n);
    tamanhogaps = sequenciaDeGaps.size();
    do{
        i++;
    }while(i < tamanhogaps);
    i = i - 2;
    h = sequenciaDeGaps[i];
    while(h >= 1){
        for(j = 0; j < h; j++){
            for(k = j + h; k < n; k = k + h){
                if((dados_entrada_manga[k].ranked == -1) || (dados_entrada_manga[k].ranked == 0)){ // Caso a informação for desconhecida, joga para o fim
                    dados_entrada_manga[k].ranked = 99999;
                }
                buffer_manga = dados_entrada_manga[k];
                l = k - h;
                while((l >= 0) && (dados_entrada_manga[l].ranked > buffer_manga.ranked)){
                    dados_entrada_manga[l + h] = dados_entrada_manga[l];
                    l = l - h;
                }
                dados_entrada_manga[l + h] = buffer_manga;
            }
        }
        if(i != 0){
            i--;
            h = sequenciaDeGaps[i];
        }
        else{
            h = 0;
        }
    }

    // Escrita no arquivo binario
    BPTree bpt_manga;
    std::ofstream bin_manga;
    bin_manga.open("manga.bin", std::ios::binary);
    for(unsigned int i = 0; i < dados_entrada_manga.size(); i++){
        if(dados_entrada_manga[i].ranked == 99999){ // Correção
            dados_entrada_manga[i].ranked = -1;
        }
        bpt_manga.insereBPTree(dados_entrada_manga[i].id, i);
        bin_manga.write(reinterpret_cast<char *>(&(dados_entrada_manga[i])), sizeof(dados_entrada_manga[i]));
    }
    bin_manga.close();
    char bpt_manga_arq[] = "bpt_manga.bin", writeb[] = "wb";
    FILE *bin_bpt_manga = NULL;
    AbreArquivo(&bin_bpt_manga, bpt_manga_arq, writeb);
    bpt_manga.armazenaBPTree(bpt_manga.getRaiz(), bin_bpt_manga);
    fclose(bin_bpt_manga);
    std::cout << std::endl << "TOP 3 MANGA:" << std::endl;
    dados_entrada_manga[0].printaManga();
    dados_entrada_manga[1].printaManga();
    dados_entrada_manga[2].printaManga();
}

void ordenaMangaInverso(){
    // Leitura do arquivo
    std::vector<Manga> dados_entrada_manga;
    Manga buffer_manga;
    std::ifstream arq_entrada;
    arq_entrada.open("manga.bin", std::ios::binary);
    while(!(arq_entrada.eof())){
        arq_entrada.read((char *) &buffer_manga, sizeof(Manga));
        dados_entrada_manga.push_back(buffer_manga);
    }
    arq_entrada.close();

    // Ordenação via shellSort usando o ranking como parametro
    int tamanhogaps;
    int n = dados_entrada_manga.size();
    int i = 0, j, k, l, h = 1;
    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(n);
    tamanhogaps = sequenciaDeGaps.size();
    do{
        i++;
    }while(i < tamanhogaps);
    i = i - 2;
    h = sequenciaDeGaps[i];
    while(h >= 1){
        for(j = 0; j < h; j++){
            for(k = j + h; k < n; k = k + h){
                buffer_manga = dados_entrada_manga[k];
                l = k - h;
                while((l >= 0) && (dados_entrada_manga[l].ranked < buffer_manga.ranked)){
                    dados_entrada_manga[l + h] = dados_entrada_manga[l];
                    l = l - h;
                }
                dados_entrada_manga[l + h] = buffer_manga;
            }
        }
        if(i != 0){
            i--;
            h = sequenciaDeGaps[i];
        }
        else{
            h = 0;
        }
    }

    // Escrita no arquivo binario
    BPTree bpt_manga;
    std::ofstream bin_manga;
    bin_manga.open("manga.bin", std::ios::binary);
    for(unsigned int i = 0; i < dados_entrada_manga.size(); i++){
        bpt_manga.insereBPTree(dados_entrada_manga[i].id, i);
        bin_manga.write(reinterpret_cast<char *>(&(dados_entrada_manga[i])), sizeof(dados_entrada_manga[i]));
    }
    bin_manga.close();
    char bpt_manga_arq[] = "bpt_manga.bin", writeb[] = "wb";
    FILE *bin_bpt_manga = NULL;
    AbreArquivo(&bin_bpt_manga, bpt_manga_arq, writeb);
    bpt_manga.armazenaBPTree(bpt_manga.getRaiz(), bin_bpt_manga);
    fclose(bin_bpt_manga);
    std::cout << std::endl << "TOP 3 MANGA:" << std::endl;
    dados_entrada_manga[0].printaManga();
    dados_entrada_manga[1].printaManga();
    dados_entrada_manga[2].printaManga();
}

// Geração de sequência de gaps para utilização na ordenação shellSort via CIURA
std::vector<int> geraSequenciaDeGaps(int tam){
    std::vector<int> v;
    int e = 1;
    v.push_back(e);
    int seq[8] = {1, 4, 10, 23, 57, 132, 301, 701};
    int i = 1;
    while((i < 8) && (seq[i] < tam)){
        v.push_back(seq[i]);
        i++;
    }
    e = 701;
    while((e = floor(2.25*(float)e)) < tam){
        v.push_back(e);
    }
    return v;
}
