#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3 // Define o grau das árvores B+
#define NTRIE 26
#define ANIME 1
#define MANGA 2

short AbreArquivo(FILE **arq, char nome_arq[], char *modo);
short ArquivoExiste(std::string name);
void ProcessaArquivoCSV();

// Nodo da árvore B+
class Nodo{
    public:
        Nodo();
    private:
        bool ehFolha;
        int *chaves, numChaves;
        int *index;
        Nodo **pChaves;
        friend class BPTree;
};

// Árvore B+
class BPTree{
    public:
        BPTree();
        int procuraBPTree(int chave);
        void removeBPTree(int chave);
        void insereBPTree(int chave, int indice);
        void display(Nodo *cursor);
        void armazenaBPTree(Nodo *cursor, FILE *arq);
        Nodo *getRaiz();
    private:
        Nodo *raiz;
        void insereInterno(int chave, int indice, Nodo *cursor, Nodo *filho);
        void removeInterno(int chave, Nodo *cursor, Nodo *filho);
        Nodo *achaPai(Nodo *cursor, Nodo *filho);
};

typedef struct NodoTrie NodoTrie;

struct NodoTrie {
    char caracter;
    NodoTrie* filhos[NTRIE];
    int eh_folha;
    int indexanime;
    int indexmanga;
};

NodoTrie* cria_NodoTrie(char caracter);

void free_NodoTrie(NodoTrie* nodo);

NodoTrie* insert_trie(NodoTrie* raiz, std::string name, int index, int anime_ou_manga);

int busca_trie(NodoTrie* raiz, std::string name, int anime_ou_manga);

int checa_divergencia(NodoTrie* raiz, std::string name);

std::string busca_maior_prefixo(NodoTrie* raiz, std::string name);

int nodo_eh_folha(NodoTrie* raiz, std::string name);

NodoTrie* delete_trie(NodoTrie* raiz, std::string name);

void print_trie(NodoTrie* raiz);

void print_nome(NodoTrie* raiz, std::string name, int anime_ou_manga);

void armazenaTRIE(NodoTrie *raiz, FILE *arq);

NodoTrie* recuperaTRIE(NodoTrie* raiz, FILE* arq);
