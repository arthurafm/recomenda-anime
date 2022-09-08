#include "..\include\Arquivos.h"
#include <iostream>
#include <fstream>
#include "..\include\Registro.h"

// Função para abrir arquivos pela stdio.h
short AbreArquivo(FILE **arq, char *nome_arq, char *modo){
    *arq = fopen(nome_arq, modo);
    if(*arq == NULL){
        return 0;
    }
    else{
        return 1;
    }
}

// Função para saber se o arquivo existe ou não
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

// Função que lê CSVs e cria arquivos binarios
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

    /* 2. Após coletar ou extrair os dados, o programa deverá usar arquivos binários próprios que armazenarão todos os dados, independentes dos arquivos originais.
          Tais arquivos poderão ser organizados tanto de forma sequencial, quanto serial. Porém é obrigatório que sejam implementados índices de acesso que auxiliem
          na consulta a esses dados. */

    // Criação das árvores B+
    BPTree bpt_anime, bpt_manga;
    for(unsigned int i = 0; i < dados_entrada_anime.size(); i++){
        bpt_anime.insereBPTree(dados_entrada_anime[i].getID(), i);
    }
    for(unsigned int i = 0; i < dados_entrada_manga.size(); i++){
        bpt_manga.insereBPTree(dados_entrada_manga[i].getID(), i);
    }

    // Manipulação de arquivos binários
    std::ofstream bin_anime, bin_manga;
    bin_anime.open("anime.bin", std::ios::binary);
    bin_manga.open("manga.bin", std::ios::binary);
    for(unsigned int i = 0; i < dados_entrada_anime.size(); i++){
        bin_anime.write(reinterpret_cast<char *>(&(dados_entrada_anime[i])), sizeof(dados_entrada_anime[i]));
    }
    for(unsigned int i = 0; i < dados_entrada_manga.size(); i++){
        bin_manga.write(reinterpret_cast<char *>(&(dados_entrada_manga[i])), sizeof(dados_entrada_manga[i]));
    }
    bin_anime.close();
    bin_manga.close();

    char bpt_anime_arq[] = "bpt_anime.bin", bpt_manga_arq[] = "bpt_manga.bin", write[] = "w";
    FILE *bin_bpt_anime = NULL, *bin_bpt_manga;
    AbreArquivo(&bin_bpt_anime, bpt_anime_arq, write);
    bpt_anime.armazenaBPTree(bpt_anime.getRaiz(), bin_bpt_anime);
    fclose(bin_bpt_anime);
    AbreArquivo(&bin_bpt_manga, bpt_manga_arq, write);
    bpt_manga.armazenaBPTree(bpt_manga.getRaiz(), bin_bpt_manga);
    fclose(bin_bpt_manga);
}

// Construtor para nodos da árvore B+ Tree
Nodo::Nodo(){
    chaves = new int[MAX];
    index = new int[MAX];
    pChaves = new Nodo *[MAX + 1];
}

// Construtor para a árvore B+ Tree
BPTree::BPTree(){
    raiz = NULL;
}

// Procura na árvore B+
int BPTree::procuraBPTree(int chave){
    if(raiz == NULL){ // Se árvore for vazia, devolve -1
        return -1;
    }
    else{
        Nodo *cursor = raiz;
        while(cursor->ehFolha == false){
            for(int i = 0; i < cursor->numChaves; i++){
                if(chave < cursor->chaves[i]){
                    cursor = cursor->pChaves[i];
                    break;
                }
                if (i == (cursor->numChaves - 1)){
                    cursor = cursor->pChaves[i + 1];
                    break;
                }
            }
        }
        for(int i = 0; i < cursor->numChaves; i++){
            if(cursor->chaves[i] == chave){
                return cursor->index[i]; // Se achar, devolve o índice
            }
        }
        return -1; // Se não achar, devolve -1
    }
}

// Inserção na árvore B+
void BPTree::insereBPTree(int chave, int indice){
    if (raiz == NULL){ // Se a árvore for vazia, insere na raiz
        raiz = new Nodo;
        raiz->chaves[0] = chave;
        raiz->index[0] = indice;
        raiz->ehFolha = true;
        raiz->numChaves = 1;
    }
    else{ // Se a árvore não for vazia
        Nodo *cursor = raiz;
        Nodo *pai;
        while(cursor->ehFolha == false){
            pai = cursor;
            for(int i = 0; i < cursor->numChaves; i++){
                if(chave < cursor->chaves[i]){
                    cursor = cursor->pChaves[i];
                    break;
                }
                if (i == cursor->numChaves - 1) {
                    cursor = cursor->pChaves[i + 1];
                    break;
                }
            }
        }
        if(cursor->numChaves < MAX){ // Se o nodo ainda não estiver cheio
            int i = 0;
            while((chave > cursor->chaves[i]) && (i < cursor->numChaves)){
                i++;
            }
            for(int j = cursor->numChaves; j > i; j--){
                cursor->chaves[j] = cursor->chaves[j - 1];
            }
            cursor->chaves[i] = chave;
            cursor->index[i] = indice;
            cursor->numChaves++;
            cursor->pChaves[cursor->numChaves] = cursor->pChaves[cursor->numChaves - 1];
            cursor->pChaves[cursor->numChaves - 1] = NULL;
        }
        else{ // Se o nodo estiver cheio
            Nodo *n_folha = new Nodo;
            int buffer_ch[MAX + 1];
            int buffer_in[MAX + 1];
            for(int i = 0; i < MAX; i++){
                buffer_ch[i] = cursor->chaves[i];
                buffer_in[i] = cursor->index[i];
            }
            int i = 0, j;
            while((chave > buffer_in[i]) && (i < MAX)){
                i++;
            }
            for (int j = MAX; j > i; j--){
                buffer_ch[j] = buffer_ch[j - 1];
                buffer_in[j] = buffer_in[j - 1];
            }
            buffer_ch[i] = chave;
            buffer_in[i] = indice;
            n_folha->ehFolha = true;
            cursor->numChaves = (MAX + 1) / 2;
            n_folha->numChaves = MAX + 1 - (MAX + 1) / 2;
            cursor->pChaves[cursor->numChaves] = n_folha;
            n_folha->pChaves[n_folha->numChaves] = cursor->pChaves[MAX];
            cursor->pChaves[MAX] = NULL;
            for(i = 0; i < cursor->numChaves; i++){
                cursor->chaves[i] = buffer_ch[i];
                cursor->index[i] = buffer_in[i];
            }
            for(i = 0, j = cursor->numChaves; i < n_folha->numChaves; i++, j++){
                n_folha->chaves[i] = buffer_ch[j];
                n_folha->index[i] = buffer_in[j];
            }
            if(cursor == raiz){
                Nodo *n_raiz = new Nodo;
                n_raiz->chaves[0] = n_folha->chaves[0];
                n_raiz->index[0] = n_folha->index[0];
                n_raiz->pChaves[0] = cursor;
                n_raiz->pChaves[1] = n_folha;
                n_raiz->ehFolha = false;
                n_raiz->numChaves = 1;
                raiz = n_raiz;
            }
            else{
                insereInterno(n_folha->chaves[0], n_folha->index[0], pai, n_folha);
            }
        }
    }
}

// Função recursiva auxiliar de inserção
void BPTree::insereInterno(int chave, int indice, Nodo *cursor, Nodo *filho){
    if(cursor->numChaves < MAX){
    int i = 0;
    while ((chave > cursor->chaves[i]) && (i < cursor->numChaves)){
        i++;
    }
    for(int j = cursor->numChaves; j > i; j--){
        cursor->chaves[j] = cursor->chaves[j - 1];
        cursor->index[j] = cursor->index[j - 1];
    }
    for(int j = cursor->numChaves + 1; j > i + 1; j--){
        cursor->pChaves[j] = cursor->pChaves[j - 1];
    }
    cursor->chaves[i] = chave;
    cursor->index[i] = indice;
    cursor->numChaves++;
    cursor->pChaves[i + 1] = filho;
    }
    else{
        Nodo *n_interno = new Nodo;
        int buffer_ch[MAX + 1];
        int buffer_in[MAX + 1];
        Nodo *buffer_ptr[MAX + 2];
        for (int i = 0; i < MAX; i++){
        buffer_ch[i] = cursor->chaves[i];
        buffer_in[i] = cursor->index[i];
        }
        for(int i = 0; i < (MAX + 1); i++){
            buffer_ptr[i] = cursor->pChaves[i];
        }
        int i = 0, j;
        while((chave > buffer_ch[i]) && (i < MAX)){
            i++;
        }
        for(int j = MAX; j > i; j--){
            buffer_ch[j] = buffer_ch[j - 1];
            buffer_in[j] = buffer_in[j - 1];
        }
        buffer_ch[i] = chave;
        buffer_in[i] = indice;
        for(int j = (MAX + 1); j > i + 1; j--){ // Possível erro
            buffer_ptr[j] = buffer_ptr[j - 1];
        }
        buffer_ptr[i + 1] = filho;
        n_interno->ehFolha = false;
        cursor->numChaves = (MAX + 1) / 2;
        n_interno->numChaves = MAX - (MAX + 1) / 2;
        for (i = 0, j = (cursor->numChaves + 1); i < n_interno->numChaves; i++, j++){
            n_interno->chaves[i] = buffer_ch[j];
            n_interno->index[i] = buffer_in[j];
        }
        for (i = 0, j = (cursor->numChaves + 1); i < (n_interno->numChaves + 1); i++, j++){
            n_interno->pChaves[i] = buffer_ptr[j];
        }
        if(cursor == raiz){
            Nodo *n_raiz = new Nodo;
            n_raiz->chaves[0] = cursor->chaves[cursor->numChaves];
            n_raiz->index[0] = cursor->index[cursor->numChaves];
            n_raiz->pChaves[0] = cursor;
            n_raiz->pChaves[1] = n_interno;
            n_raiz->ehFolha = false;
            n_raiz->numChaves = 1;
            raiz = n_raiz;
        }
        else{
            insereInterno(cursor->chaves[cursor->numChaves], cursor->index[cursor->numChaves], achaPai(raiz, cursor), n_interno);
        }
    }
}

// Retorna o pai do nodo
Nodo *BPTree::achaPai(Nodo *cursor, Nodo *filho){
    Nodo *pai;
    if(cursor->ehFolha || (cursor->pChaves[0])->ehFolha){
        return NULL;
    }
    for(int i = 0; i < cursor->numChaves + 1; i++){
        if(cursor->pChaves[i] == filho){
            pai = cursor;
            return pai;
        }
        else{
            pai = achaPai(cursor->pChaves[i], filho);
            if (pai != NULL){
                return pai;
            }
        }
    }
  return pai;
}

// Remove na árvore B+
void BPTree::removeBPTree(int chave){
    if(raiz == NULL){
        return;
    }
    else{
        Nodo *cursor = raiz;
        Nodo *pai;
        int irmao_esq, irmao_dir;
        while(cursor->ehFolha == false){
            for(int i = 0; i < cursor->numChaves; i++){
                pai = cursor;
                irmao_esq = i - 1;
                irmao_dir = i + 1;
                if(chave < cursor->chaves[i]){
                    cursor = cursor->pChaves[i];
                    break;
                }
                if(i == (cursor->numChaves - 1)){
                    irmao_esq = i;
                    irmao_dir = i + 2;
                    cursor = cursor->pChaves[i + 1];
                    break;
                }
            }
        }
        bool achou = false;
        int pos;
        for(pos = 0; pos < cursor->numChaves; pos++){
            if(cursor->chaves[pos] == chave){
                achou = true;
                break;
            }
        }
        if(!achou){
            return;
        }
        for(int i = pos; i < cursor->numChaves; i++){
            cursor->chaves[i] = cursor->chaves[i + 1];
        }
        cursor->numChaves--;
        if(cursor == raiz){
            for(int i = 0; i < (MAX + 1); i++){
                cursor->pChaves[i] = NULL;
            }
            if(cursor->numChaves == 0){
                delete[] cursor->chaves;
                delete[] cursor->index;
                delete[] cursor->pChaves;
                delete cursor;
                raiz = NULL;
            }
            return;
        }
        cursor->pChaves[cursor->numChaves] = cursor->pChaves[cursor->numChaves + 1];
        cursor->pChaves[cursor->numChaves + 1] = NULL;
        if(cursor->numChaves >= ((MAX + 1) / 2)){
            return;
        }
        if(irmao_esq >= 0){
            Nodo *nodo_esq = pai->pChaves[irmao_esq];
            if(nodo_esq->numChaves >= ((MAX + 1) / 2 + 1)){
                for(int i = cursor->numChaves; i > 0; i--){
                    cursor->chaves[i] = cursor->chaves[i - 1];
                }
                cursor->numChaves++;
                cursor->pChaves[cursor->numChaves] = cursor->pChaves[cursor->numChaves - 1];
                cursor->pChaves[cursor->numChaves - 1] = NULL;
                cursor->chaves[0] = nodo_esq->chaves[nodo_esq->numChaves - 1];
                nodo_esq->numChaves--;
                nodo_esq->pChaves[nodo_esq->numChaves] = cursor;
                nodo_esq->pChaves[nodo_esq->numChaves + 1] = NULL;
                pai->chaves[irmao_esq] = cursor->chaves[0];
                return;
            }
        }
        if(irmao_dir <= pai->numChaves){
            Nodo *nodo_dir = pai->pChaves[irmao_dir];
            if(nodo_dir->numChaves >= ((MAX + 1) / 2 + 1)){
                cursor->numChaves++;
                cursor->pChaves[cursor->numChaves] = cursor->pChaves[cursor->numChaves - 1];
                cursor->pChaves[cursor->numChaves - 1] = NULL;
                cursor->chaves[cursor->numChaves - 1] = nodo_dir->chaves[0];
                nodo_dir->numChaves--;
                nodo_dir->pChaves[nodo_dir->numChaves] = nodo_dir->pChaves[nodo_dir->numChaves + 1];
                nodo_dir->pChaves[nodo_dir->numChaves + 1] = NULL;
                for(int i = 0; i < nodo_dir->numChaves; i++){
                    nodo_dir->chaves[i] = nodo_dir->chaves[i + 1];
                }
                pai->chaves[irmao_dir - 1] = nodo_dir->chaves[0];
                return;
            }
        }
        if(irmao_esq >= 0){
            Nodo *nodo_esq = pai->pChaves[irmao_esq];
            for(int i = nodo_esq->numChaves, j = 0; j < cursor->numChaves; i++, j++){
                nodo_esq->chaves[i] = cursor->chaves[j];
            }
            nodo_esq->pChaves[nodo_esq->numChaves] = NULL;
            nodo_esq->numChaves += cursor->numChaves;
            nodo_esq->pChaves[nodo_esq->numChaves] = cursor->pChaves[cursor->numChaves];
            removeInterno(pai->chaves[irmao_esq], pai, cursor);
            delete[] cursor->chaves;
            delete[] cursor->index;
            delete[] cursor->pChaves;
            delete cursor;
        }
        else{
            if(irmao_dir <= pai->numChaves){
                Nodo *nodo_dir = pai->pChaves[irmao_dir];
                for(int i = cursor->numChaves, j = 0; j < nodo_dir->numChaves; i++, j++){
                    cursor->chaves[i] = nodo_dir->chaves[j];
                }
                cursor->pChaves[cursor->numChaves] = NULL;
                cursor->numChaves += nodo_dir->numChaves;
                cursor->pChaves[cursor->numChaves] = nodo_dir->pChaves[nodo_dir->numChaves];
                removeInterno(pai->chaves[irmao_dir - 1], pai, nodo_dir);
                delete[] nodo_dir->chaves;
                delete[] nodo_dir->pChaves;
                delete nodo_dir;
            }
        }
    }
}

// Função recursiva auxiliar de remoção
void BPTree::removeInterno(int chave, Nodo *cursor, Nodo *filho){
    if(cursor == raiz){
        if(cursor->numChaves == 1){
            if(cursor->pChaves[1] == filho){
                delete[] filho->chaves;
                delete[] filho->index;
                delete[] filho->pChaves;
                delete filho;
                raiz = cursor->pChaves[0];
                delete[] cursor->chaves;
                delete[] cursor->index;
                delete[] cursor->pChaves;
                delete cursor;
                return;
            }
            else{
                if(cursor->pChaves[0] == filho){
                    delete[] filho->chaves;
                    delete[] filho->index;
                    delete[] filho->pChaves;
                    delete filho;
                    raiz = cursor->pChaves[1];
                    delete[] cursor->chaves;
                    delete[] cursor->index;
                    delete[] cursor->pChaves;
                    delete cursor;
                    return;
                }
            }
        }
    }
    int pos;
    for(pos = 0; pos < cursor->numChaves; pos++){
        if(cursor->chaves[pos] == chave){
            break;
        }
    }
    for(int i = pos; i < cursor->numChaves; i++){
        cursor->chaves[i] = cursor->chaves[i + 1];
    }
    for(pos = 0; pos < (cursor->numChaves + 1); pos++){
        if(cursor->pChaves[pos] == filho){
            break;
        }
    }
    for(int i = pos; i < (cursor->numChaves + 1); i++){
        cursor->pChaves[i] = cursor->pChaves[i + 1];
    }
    cursor->numChaves--;
    if(cursor->numChaves >= ((MAX + 1) / 2 - 1)){
        return;
    }
    if(cursor == raiz){
        return;
    }
    Nodo *pai = achaPai(raiz, cursor);
    int irmao_esq, irmao_dir;
    for(pos = 0; pos < (pai->numChaves + 1); pos++){
        if(pai->pChaves[pos] == cursor){
            irmao_esq = pos - 1;
            irmao_dir = pos + 1;
            break;
        }
    }
    if(irmao_esq >= 0){
        Nodo *nodo_esq = pai->pChaves[irmao_esq];
        if(nodo_esq->numChaves >= (MAX + 1) / 2){
            for(int i = cursor->numChaves; i > 0; i--){
                cursor->chaves[i] = cursor->chaves[i - 1];
            }
            cursor->chaves[0] = pai->chaves[irmao_esq];
            pai->chaves[irmao_esq] = nodo_esq->chaves[nodo_esq->numChaves - 1];
            for(int i = (cursor->numChaves + 1); i > 0; i--){
                cursor->pChaves[i] = cursor->pChaves[i - 1];
            }
            cursor->pChaves[0] = nodo_esq->pChaves[nodo_esq->numChaves];
            cursor->numChaves++;
            nodo_esq->numChaves--;
            return;
        }
    }
    if(irmao_dir <= pai->numChaves){
        Nodo *nodo_dir = pai->pChaves[irmao_dir];
        if(nodo_dir->numChaves >= ((MAX + 1) / 2)){
            cursor->chaves[cursor->numChaves] = pai->chaves[pos];
            pai->chaves[pos] = nodo_dir->chaves[0];
            for(int i = 0; i < (nodo_dir->numChaves - 1); i++){
                nodo_dir->chaves[i] = nodo_dir->chaves[i + 1];
            }
            cursor->pChaves[cursor->numChaves + 1] = nodo_dir->pChaves[0];
            for(int i = 0; i < nodo_dir->numChaves; ++i){
                nodo_dir->pChaves[i] = nodo_dir->pChaves[i + 1];
            }
            cursor->numChaves++;
            nodo_dir->numChaves--;
            return;
        }
    }
    if(irmao_esq >= 0){
        Nodo *nodo_esq = pai->pChaves[irmao_esq];
        nodo_esq->chaves[nodo_esq->numChaves] = pai->chaves[irmao_esq];
        for(int i = (nodo_esq->numChaves + 1), j = 0; j < cursor->numChaves; j++){
            nodo_esq->chaves[i] = cursor->chaves[j];
        }
        for(int i = (nodo_esq->numChaves + 1), j = 0; j < (cursor->numChaves + 1); j++){
            nodo_esq->pChaves[i] = cursor->pChaves[j];
            cursor->pChaves[j] = NULL;
        }
        nodo_esq->numChaves += cursor->numChaves + 1;
        cursor->numChaves = 0;
        removeInterno(pai->chaves[irmao_esq], pai, cursor);
    }
    else{
        if(irmao_dir <= pai->numChaves){
            Nodo *nodo_dir = pai->pChaves[irmao_dir];
            cursor->chaves[cursor->numChaves] = pai->chaves[irmao_dir - 1];
            for(int i = (cursor->numChaves + 1), j = 0; j < nodo_dir->numChaves; j++){
                cursor->chaves[i] = nodo_dir->chaves[j];
            }
            for(int i = (cursor->numChaves + 1), j = 0; j < (nodo_dir->numChaves + 1); j++){
                cursor->pChaves[i] = nodo_dir->pChaves[j];
                nodo_dir->pChaves[j] = NULL;
            }
            cursor->numChaves += nodo_dir->numChaves + 1;
            nodo_dir->numChaves = 0;
            removeInterno(pai->chaves[irmao_dir - 1], pai, nodo_dir);
        }
    }
}

// Printa a árvore B+ para debug
void BPTree::display(Nodo *cursor){
    if(cursor != NULL){
        for(int i = 0; i < cursor->numChaves; i++){
            std::cout << cursor->chaves[i] << "-" << cursor->index[i] << " ";
        }
        std::cout << "\n";
        if(cursor->ehFolha != true){
            for(int i = 0; i < (cursor->numChaves + 1); i++){
                display(cursor->pChaves[i]);
            }
        }
    }
}

// Devolve a raiz da árvore B+
Nodo *BPTree::getRaiz(){
    return raiz;
}

// Função para armazenar árvore B+ em binário
void BPTree::armazenaBPTree(Nodo *cursor, FILE* arq){
    if(cursor != NULL){
        for(int i = 0; i < cursor->numChaves; i++){
            fwrite(&(cursor->chaves[i]), sizeof(int), 1, arq);
            fwrite(&(cursor->index[i]), sizeof(int), 1, arq);
        }
        if(cursor->ehFolha != true){
            for(int i = 0; i < (cursor->numChaves + 1); i++){
                armazenaBPTree(cursor->pChaves[i], arq);
            }
        }
    }
}
