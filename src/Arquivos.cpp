#include "..\include\Arquivos.h"
#include <iostream>
#include <fstream>
#include "..\include\Registro.h"


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

    // Manipulação de arquivos binários
    /*
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

    */

    BPTree bt_anime, bt_manga;

    for(unsigned int i = 0; i < dados_entrada_anime.size(); i++){
        bt_anime.insereBPTree(dados_entrada_anime[i].getID(), i);
        bt_anime.display(bt_anime.devolveRaiz());
        std::cout << "\n\n\n\n";
    }

    std::cout << dados_entrada_anime[bt_anime.procuraBPTree(6)].getName() << std::endl;
}

// Construtor de Nodo
Nodo::Nodo(){
    chaves = new std::pair<int, int> [MAX];
    pChaves = new Nodo *[MAX+1];
}

// Construtor de Árvore
BPTree::BPTree(){
    raiz = NULL;
}

// Procura na BPTree pela chave e retorna o indice
int BPTree::procuraBPTree(int chave){
    if(raiz == NULL){
        return -1;
    }
    else{
        Nodo *cursor = raiz;
        while(cursor->ehFolha == false){
            for(int i = 0; i < cursor->numChaves; i++){
                if(chave < cursor->chaves[i].first){
                    cursor = cursor->pChaves[i];
                    break;
                }
                if(i == (cursor->numChaves - 1)){
                    cursor = cursor->pChaves[i + 1];
                    break;
                }
            }
        }
        for(int i = 0; i < cursor->numChaves; i++){
            if(cursor->chaves[i].first == chave){
                return cursor->chaves[i].second;
            }
        }
        return -1;
    }
}


// Insere um nodo na BPTree
void BPTree::insereBPTree(int chave, int indice){
    if(raiz == NULL){
        raiz = new Nodo;
        raiz->chaves[0].first = chave;
        raiz->chaves[0].second = indice;
        raiz->ehFolha = true;
        raiz->numChaves = 1;
    }
    else{
        Nodo *cursor = raiz;
        Nodo *pai;
        while(cursor->ehFolha == false){
            pai = cursor;
            for(int i = 0; i < cursor->numChaves; i++){
                if(chave < cursor->chaves[i].first){
                    cursor = cursor->pChaves[i];
                    break;
                }
                if(i == (cursor->numChaves - 1)){
                    cursor = cursor->pChaves[i + 1];
                    break;
                }
            }
        }
        if(cursor->numChaves < MAX){
            int i = 0;
            while((chave > cursor->chaves[i].first) && (i < cursor->numChaves)){
                i++;
            }
            for(int j = cursor->numChaves; j > i; j--){
                cursor->chaves[j] = cursor->chaves[j-1];
            }
            cursor->chaves[i].first = chave;
            cursor->chaves[i].second = indice;
            cursor->numChaves++;
            cursor->pChaves[cursor->numChaves] = cursor->pChaves[cursor->numChaves - 1];
            cursor->pChaves[cursor->numChaves - 1] = NULL;
        }
        else{ // Erro quando divide
            Nodo *n_folha = new Nodo;
            std::pair <int, int> nodoVirtual[MAX + 1];
            for(int i = 0; i < MAX; i++){
                nodoVirtual[i] = cursor->chaves[i];
            }
            int i = 0, j;
            while((chave > nodoVirtual[i].first) && (i < MAX)){
                i++;
            }
            for(int j = (MAX + 1); j > i; j--){ // De alguma forma, modifica o n_folha e quebra o programa
                nodoVirtual[j] = nodoVirtual[j - 1];
            }
            nodoVirtual[i].first = chave;
            nodoVirtual[i].second = indice;
            n_folha->ehFolha = true;
            cursor->numChaves = (MAX + 1)/2;
            n_folha->numChaves = MAX + 1 - (MAX + 1)/2;
            cursor->pChaves[cursor->numChaves] = n_folha;
            n_folha->pChaves[n_folha->numChaves] = cursor->pChaves[MAX];
            cursor->pChaves[MAX] = NULL;
            for(i = 0; i < cursor->numChaves; i++){
                cursor->chaves[i] = nodoVirtual[i];
            }
            for(i = 0, j = cursor->numChaves; i < n_folha->numChaves; i++, j++){
                n_folha->chaves[i] = nodoVirtual[j];
            }
            if(cursor == raiz){
                Nodo *n_raiz = new Nodo;
                n_raiz->chaves[0] = n_folha->chaves[0];
                n_raiz->pChaves[0] = cursor;
                n_raiz->pChaves[1] = n_folha;
                n_raiz->ehFolha = false;
                n_folha->numChaves = 1;
                raiz = n_raiz;
            }
            else{
                insereInterno(n_folha->chaves[0], pai, n_folha);
            }
        }
    }
}

// Função auxilair de inserção de nodo
void BPTree::insereInterno(std::pair<int, int> chave, Nodo *cursor, Nodo *filho){
    if(cursor->numChaves < MAX){
        int i = 0;
        while((chave.first > cursor->chaves[i].first) && (i < cursor->numChaves)){
            i++;
        }
        for(int j = cursor->numChaves; j > i; j--){
            cursor->chaves[j] = cursor->chaves[j - 1];
        }
        for(int j = (cursor->numChaves + 1); j > (i + 1); j--){
            cursor->pChaves[j] = cursor->pChaves[j-1];
        }
        cursor->chaves[i] = chave;
        cursor->numChaves++;
        cursor->pChaves[i + 1] = filho;
    }
    else{
        Nodo *n_interno = new Nodo;
        std::pair <int, int> chaveVirtual[MAX +1];
        Nodo *pVirtual[MAX + 2];
        for(int i = 0; i < MAX; i++){
            chaveVirtual[i] = cursor->chaves[i];
        }
        for(int i = 0; i < (MAX + 1); i++){
            pVirtual[i] = cursor->pChaves[i];
        }
        int i = 0, j;
        while((chave.first > chaveVirtual[i].first) && (i < MAX)){
            i++;
        }
        for(int j = (MAX + 1); j > i; j--){
            chaveVirtual[j] = chaveVirtual[j - 1];
        }
        chaveVirtual[i] = chave;
        for(int j = (MAX + 2); j > (i + 1); j--){
            pVirtual[j] = pVirtual[j - 1];
        }
        pVirtual[i + 1] = filho;
        n_interno->ehFolha = false;
        cursor->numChaves = (MAX + 1)/2;
        n_interno->numChaves = MAX - (MAX + 1)/2;
        for(i = 0, j = (cursor->numChaves + 1); i < n_interno->numChaves; i++, j++){
            n_interno->chaves[i] = chaveVirtual[j];
        }
        for(i = 0, j = (cursor->numChaves + 1); i < (n_interno->numChaves + 1); i++, j++){
            n_interno->pChaves[i] = pVirtual[j];
        }
        if(cursor == raiz){
            Nodo *n_raiz = new Nodo;
            n_raiz->chaves[0] = cursor->chaves[cursor->numChaves];
            n_raiz->pChaves[0] = cursor;
            n_raiz->pChaves[1] = n_interno;
            n_raiz->ehFolha = false;
            n_raiz->numChaves = 1;
            raiz = n_raiz;
        }
        else{
            insereInterno(cursor->chaves[cursor->numChaves], achaPai(raiz, cursor), n_interno);
        }
    }
}

// Acha o pai de um nodo
Nodo *BPTree::achaPai(Nodo *cursor, Nodo *filho){
    Nodo *pai;
    if(cursor->ehFolha || (cursor->pChaves[0])->ehFolha){
        return NULL;
    }
    for(int i = 0; i < (cursor->numChaves + 1); i++){
        if(cursor->pChaves[i] == filho){
            pai = cursor;
            return pai;
        }
        else{
            pai = achaPai(cursor->pChaves[i], filho);
            if(pai != NULL){
                return pai;
            }
        }
    }
    return pai;
}

// Printa a árvore (Debug)
void BPTree::display(Nodo *cursor){
    if(cursor != NULL){
        for(int i = 0; i < cursor->numChaves; i++){
            std::cout << cursor->chaves[i].first << " ";
        }
        std::cout << std::endl;
        if(cursor->ehFolha != true){
            for(int i = 0; i < (cursor->numChaves + 1); i++){
                display(cursor->pChaves[i]);
            }
        }
    }
}

// Retorna a raiz
Nodo *BPTree::devolveRaiz(){
    return raiz;
}


