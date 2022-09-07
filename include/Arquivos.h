#include <iostream>
#include <string>
#include <utility>

#define MAX 3

short ArquivoExiste(std::string name);
void ProcessaArquivoCSV();

// Classe de Nodo de árvore B+
class Nodo{
    public:
        Nodo();
    private:
        bool ehFolha;
        std::pair <int, int> *chaves; // Par: (chave, indice)
        int numChaves;
        Nodo **pChaves;
        friend class BPTree;
};

// Classe de árvore B+
class BPTree{
    private:
        Nodo* raiz;
        void insereInterno(std::pair<int, int> chave, Nodo *cursor, Nodo *filho);
        Nodo* achaPai(Nodo *cursor, Nodo *filho);
    public:
        BPTree();
        int procuraBPTree(int chave);
        void insereBPTree(int chave, int indice);
        void display(Nodo *cursor);
        Nodo* devolveRaiz();
};
