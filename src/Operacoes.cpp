#include "../include/Operacoes.h"

void buscaAnimePorID(int id){
    Anime buffer_anime;
    BPTree buffer_bpt(GRAU);
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
    BPTree buffer_bpt(GRAU);
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

void buscaAnimePorPrefixo(char* nome)
{
    Anime buffer_anime;
    NodoTrie* raiz = cria_NodoTrie('\0');
    NodoTrie* raiz_original = raiz;
    FILE *arqAnime, *arqTrie;
    AbreArquivo(&arqTrie, "trie_anime.bin", "rb");
    recuperaTRIE(raiz, arqTrie);
    fclose(arqTrie);

    for(int i=0; nome[i]!='\0'; i++)
    {
        if (nome[i] <= 'Z' && nome[i] >= 'A')
        {
            nome[i] += 32;
        }
        if(nome[i] <= 'z' && nome[i] >= 'a'){
            int j = nome[i] - 'a';
            if (raiz->filhos[j] != NULL){
                raiz = raiz->filhos[j];
            }
            else
            {
                std::cout << "Erro, nao ha animes que iniciam com " << nome << std::endl;
                free_NodoTrie(raiz_original);
                return;
            }
        }
    }

    std::vector<Anime> dados_entrada_anime;
    std::vector<int> ids;
    AbreArquivo(&arqAnime, "anime.bin", "rb");
    while(!feof(arqAnime)){
        fread(&buffer_anime, sizeof(buffer_anime), 1, arqAnime);
        dados_entrada_anime.push_back(buffer_anime);
    }
    fclose(arqAnime);
    pega_ids(raiz, ids);

    for (unsigned int i = 0; i < ids.size(); i++)
    {
        if (ids[i] != -1)
            std::cout << "Encontrado: " << dados_entrada_anime[ids[i]].name << std::endl << "E seu ID: " << dados_entrada_anime[ids[i]].id << std::endl;
    }
    free_NodoTrie(raiz_original);
}

void buscaMangaPorPrefixo(char* nome)
{
    Manga buffer_manga;
    NodoTrie* raiz = cria_NodoTrie('\0');
    NodoTrie* raiz_original = raiz;
    FILE *arqManga, *arqTrie;
    AbreArquivo(&arqTrie, "trie_manga.bin", "rb");
    recuperaTRIE(raiz, arqTrie);
    fclose(arqTrie);

    for(int i=0; nome[i]!='\0'; i++)
    {
        if (nome[i] <= 'Z' && nome[i] >= 'A')
        {
            nome[i] += 32;
        }
        if(nome[i] <= 'z' && nome[i] >= 'a'){
            int j = nome[i] - 'a';
            if (raiz->filhos[j] != NULL){
                raiz = raiz->filhos[j];
            }
            else
            {
                std::cout << "Erro, nao ha mangas que iniciam com " << nome << std::endl;
                free_NodoTrie(raiz_original);
                return;
            }
        }
    }

    std::vector<Manga> dados_entrada_manga;
    std::vector<int> ids;
    AbreArquivo(&arqManga, "manga.bin", "rb");
    while(!feof(arqManga)){
        fread(&buffer_manga, sizeof(buffer_manga), 1, arqManga);
        dados_entrada_manga.push_back(buffer_manga);
    }
    fclose(arqManga);
    pega_ids(raiz, ids);

    for (long long unsigned int i = 0; i < ids.size(); i++)
    {
        if (ids[i] != -1)
            std::cout << "Encontrado: " << dados_entrada_manga[ids[i]].title << std::endl << "E seu ID: " << dados_entrada_manga[ids[i]].id << std::endl;
    }
    free_NodoTrie(raiz_original);
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
    BPTree bpt_anime(GRAU);
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

    // Update da TRIE
    NodoTrie* raiz_trie = cria_NodoTrie('\0');
    FILE *arq_trie_leitura = NULL;
    AbreArquivo(&arq_trie_leitura, "trie_anime.bin", "rb");
    raiz_trie = recuperaTRIE(raiz_trie, arq_trie_leitura);
    fclose(arq_trie_leitura);
    for (unsigned int i = 0; i < dados_entrada_anime.size(); i++)
    {
        raiz_trie = atualiza_ids(raiz_trie, dados_entrada_anime[i].name, i);
    }
    FILE *arq_trie_escrita = NULL;
    AbreArquivo(&arq_trie_escrita, "trie_anime.bin", "wb");
    armazenaTRIE(raiz_trie, arq_trie_escrita);
    fclose(arq_trie_escrita);
    free_NodoTrie(raiz_trie);
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
    BPTree bpt_anime(GRAU);
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

    // Update da TRIE
    NodoTrie* raiz_trie = cria_NodoTrie('\0');
    FILE *arq_trie_leitura = NULL;
    AbreArquivo(&arq_trie_leitura, "trie_anime.bin", "rb");
    raiz_trie = recuperaTRIE(raiz_trie, arq_trie_leitura);
    fclose(arq_trie_leitura);
    for (unsigned int i = 0; i < dados_entrada_anime.size(); i++)
    {
        raiz_trie = atualiza_ids(raiz_trie, dados_entrada_anime[i].name, i);
    }
    FILE *arq_trie_escrita = NULL;
    AbreArquivo(&arq_trie_escrita, "trie_anime.bin", "wb");
    armazenaTRIE(raiz_trie, arq_trie_escrita);
    fclose(arq_trie_escrita);
    free_NodoTrie(raiz_trie);
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
    BPTree bpt_manga(GRAU);
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

    // Update da TRIE
    NodoTrie* raiz_trie = cria_NodoTrie('\0');
    FILE *arq_trie_leitura = NULL;
    AbreArquivo(&arq_trie_leitura, "trie_manga.bin", "rb");
    raiz_trie = recuperaTRIE(raiz_trie, arq_trie_leitura);
    fclose(arq_trie_leitura);
    for (unsigned int i = 0; i < dados_entrada_manga.size(); i++)
    {
        raiz_trie = atualiza_ids(raiz_trie, dados_entrada_manga[i].title, i);
    }
    FILE *arq_trie_escrita = NULL;
    AbreArquivo(&arq_trie_escrita, "trie_manga.bin", "wb");
    armazenaTRIE(raiz_trie, arq_trie_escrita);
    fclose(arq_trie_escrita);
    free_NodoTrie(raiz_trie);
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
    BPTree bpt_manga(GRAU);
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

    // Update da TRIE
    NodoTrie* raiz_trie = cria_NodoTrie('\0');
    FILE *arq_trie_leitura = NULL;
    AbreArquivo(&arq_trie_leitura, "trie_manga.bin", "rb");
    raiz_trie = recuperaTRIE(raiz_trie, arq_trie_leitura);
    fclose(arq_trie_leitura);
    for (unsigned int i = 0; i < dados_entrada_manga.size(); i++)
    {
        raiz_trie = atualiza_ids(raiz_trie, dados_entrada_manga[i].title, i);
    }
    FILE *arq_trie_escrita = NULL;
    AbreArquivo(&arq_trie_escrita, "trie_manga.bin", "wb");
    armazenaTRIE(raiz_trie, arq_trie_escrita);
    fclose(arq_trie_escrita);
    free_NodoTrie(raiz_trie);
}

void deletaAnime(int id){
    std::vector<Anime> dados_entrada_anime;
    Anime buffer_anime;
    BPTree bpt_anime(GRAU);
    std::ifstream arq_entrada;
    unsigned int i = 0;
    arq_entrada.open("anime.bin", std::ios::binary);
    while(!(arq_entrada.eof())){
        arq_entrada.read((char *) &buffer_anime, sizeof(Anime));
        if(buffer_anime.id != id){
            dados_entrada_anime.push_back(buffer_anime);
            bpt_anime.insereBPTree(buffer_anime.id, i);
            i++;
        }
    }
    arq_entrada.close();
    std::ofstream bin_anime;
    bin_anime.open("anime.bin");
    for(i = 0; i < dados_entrada_anime.size(); i++){
        bin_anime.write(reinterpret_cast<char *>(&(dados_entrada_anime[i])), sizeof(dados_entrada_anime[i]));
    }
    bin_anime.close();
    FILE *bpt = nullptr;
    char bpt_anime_arq[] = "bpt_anime.bin", writeb[] = "wb";
    AbreArquivo(&bpt, bpt_anime_arq, writeb);
    bpt_anime.armazenaBPTree(bpt_anime.getRaiz(), bpt);
    fclose(bpt);

    /*NodoTrie* raiztrie_anime = cria_NodoTrie('\0');
    for (unsigned int i = 0; i < dados_entrada_anime.size(); i++)
    {
        char* nome = (char*) calloc (strlen(dados_entrada_anime[i].name) + 1, sizeof(char));
        for (unsigned int j = 0; j < strlen(dados_entrada_anime[i].name); j++)
        {
            nome[j] = dados_entrada_anime[i].name[j];
        }
        raiztrie_anime = insert_trie(raiztrie_anime, nome, i);
        free(nome);
    }

    char bin_trie_arq[] = "trie_anime.bin";
    FILE *bin_trie = NULL;
    AbreArquivo(&bin_trie, bin_trie_arq, writeb);
    armazenaTRIE(raiztrie_anime, bin_trie);
    fclose(bin_trie);
    free_NodoTrie(raiztrie_anime);*/
}

void deletaManga(int id){
    std::vector<Manga> dados_entrada_manga;
    Manga buffer_manga;
    BPTree bpt_manga(GRAU);
    std::ifstream arq_entrada;
    unsigned int i = 0;
    arq_entrada.open("manga.bin", std::ios::binary);
    while(!(arq_entrada.eof())){
        arq_entrada.read((char *) &buffer_manga, sizeof(Manga));
        if(buffer_manga.id != id){
            dados_entrada_manga.push_back(buffer_manga);
            bpt_manga.insereBPTree(buffer_manga.id, i);
            i++;
        }
    }
    arq_entrada.close();
    std::ofstream bin_manga;
    bin_manga.open("manga.bin");
    for(i = 0; i < dados_entrada_manga.size(); i++){
        bin_manga.write(reinterpret_cast<char *>(&(dados_entrada_manga[i])), sizeof(dados_entrada_manga[i]));
    }
    bin_manga.close();
    FILE *bpt = nullptr;
    char bpt_manga_arq[] = "bpt_manga.bin", writeb[] = "wb";
    AbreArquivo(&bpt, bpt_manga_arq, writeb);
    bpt_manga.armazenaBPTree(bpt_manga.getRaiz(), bpt);
    fclose(bpt);
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

trie_string* cria_arq_inv(trie_string* raiz, int tipo)
{
    FILE *arq_anime = NULL;
    Anime buffer_anime;
    std::vector<Anime> dados_entrada_anime;
    AbreArquivo(&arq_anime, "anime.bin", "rb");
    while(!feof(arq_anime)){
        fread(&buffer_anime, sizeof(buffer_anime), 1, arq_anime);
        dados_entrada_anime.push_back(buffer_anime);
    }
    fclose(arq_anime);

    if (tipo == GENRES)
    {
        for (unsigned int i = 0; i < dados_entrada_anime.size(); i++)
        {
            raiz = insert_trie_string(raiz, dados_entrada_anime[i].genres, i);
        }
    }
    else if (tipo == LICENSORS)
    {
        for (unsigned int i = 0; i < dados_entrada_anime.size(); i++)
        {
            raiz = insert_trie_string(raiz, dados_entrada_anime[i].licensors, i);
        }
    }
    else if (tipo == STUDIOS)
    {
        for (unsigned int i = 0; i < dados_entrada_anime.size(); i++)
        {
            raiz = insert_trie_string(raiz, dados_entrada_anime[i].studios, i);
        }
    }

    return raiz;
}

void Busca_Dois_Campos(char* nome1, char* nome2, trie_string* raiz1, trie_string* raiz2)
{
    FILE* arq_anime = NULL;
    Anime buffer_anime;
    std::vector<Anime> dados_entrada_anime;
    std::vector<int> ids1 = {};
    std::vector<int> ids2 = {};
    std::vector<int> ids_conjunto = {};

    ids1 = busca_trie_string(raiz1, nome1);
    ids2 = busca_trie_string(raiz2, nome2);
    AbreArquivo(&arq_anime, "anime.bin", "rb");

    while(!feof(arq_anime)){
        fread(&buffer_anime, sizeof(buffer_anime), 1, arq_anime);
        dados_entrada_anime.push_back(buffer_anime);
    }
    fclose(arq_anime);

    for (unsigned int i = 0; i < ids1.size(); i++)
    {
        for (unsigned int j = 0; j < ids2.size(); j++)
        {
            if (ids1[i] == ids2[j])
            {
                ids_conjunto.push_back(ids1[i]);
            }
        }
    }

    for (unsigned int i = 0; i < ids_conjunto.size(); i++)
    {
        dados_entrada_anime[ids_conjunto[i]].printaAnime();
    }
}

void Busca_Dois_Mesmo_Campo(char* nome1, char* nome2, trie_string* raiz1)
{
    FILE* arq_anime = NULL;
    Anime buffer_anime;
    std::vector<Anime> dados_entrada_anime;
    std::vector<int> ids1 = {};
    std::vector<int> ids2 = {};
    std::vector<int> ids_conjunto = {};

    ids1 = busca_trie_string(raiz1, nome1);
    ids2 = busca_trie_string(raiz1, nome2);
    AbreArquivo(&arq_anime, "anime.bin", "rb");

    while(!feof(arq_anime)){
        fread(&buffer_anime, sizeof(buffer_anime), 1, arq_anime);
        dados_entrada_anime.push_back(buffer_anime);
    }
    fclose(arq_anime);

    for (unsigned int i = 0; i < ids1.size(); i++)
    {
        ids_conjunto.push_back(ids1[i]);
    }

    for (unsigned int i = 0; i < ids2.size(); i++)
    {
        ids_conjunto.push_back(ids2[i]);
    }

    unsigned int tam = ids_conjunto.size();
    for (unsigned int i = 0; i < tam; i++)
    {
        for (unsigned j = i + 1; j < tam; j++)
        {
            if (ids_conjunto[i] == ids_conjunto[j])
            {
                for (unsigned k = j; k < tam - 1; k++)
                {
                    ids_conjunto[k] = ids_conjunto[k+1];
                }
                tam--;
                j--;
            }
        }
    }

    for (unsigned int i = 0; i < ids_conjunto.size(); i++)
    {
        dados_entrada_anime[ids_conjunto[i]].printaAnime();
    }
}
