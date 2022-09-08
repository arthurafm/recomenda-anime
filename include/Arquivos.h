#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>
#include <utility>
#include <stdio.h>

#define MAX 3 // Define o grau das árvores B+

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
