#include <iostream>
#include <string>
#include <climits>
#include <fstream>
#include <sstream>
#include <utility>

#define MAX 3 // Define o grau das �rvores B+

short ArquivoExiste(std::string name);
void ProcessaArquivoCSV();

// Nodo da �rvore B+
class Nodo {
  bool ehFolha;
  int *chaves, numChaves;
  int *index;
  Nodo **pChaves;
  friend class BPTree;

   public:
  Nodo();
  int getNumChaves();
  int getChaves(int i);
  int getIndex(int i);
};

// �rvore B+
class BPTree {
  Nodo *raiz;
  void insereInterno(int chave, int indice, Nodo *cursor, Nodo *filho);
  void removeInterno(int chave, Nodo *cursor, Nodo *filho);
  Nodo *achaPai(Nodo *cursor, Nodo *filho);

   public:
  BPTree();
  int procuraBPTree(int chave);
  void removeBPTree(int chave);
  void insereBPTree(int chave, int indice);
  void display(Nodo *cursor);
  Nodo *getRaiz();
};
