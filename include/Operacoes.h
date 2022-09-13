#include "../include/Registro.h"
#include "../include/Arquivos.h"
#include <cmath>

void buscaAnimePorPrefixo(char* nome);
void buscaMangaPorPrefixo(char* nome);
void buscaAnimePorID(int id);
void buscaMangaPorID(int id);
void ordenaAnime();
void ordenaAnimeInverso();
void ordenaManga();
void ordenaMangaInverso();

std::vector<int> geraSequenciaDeGaps(int tam);
