#include "../include/Registro.h"
#include "../include/Arquivos.h"
#include <cmath>

void buscaAnimePorID(int id);
void buscaMangaPorID(int id);
void ordenaAnime();
void ordenaAnimeInverso();
void ordenaManga();
void ordenaMangaInverso();
void deletaAnime(int id);
void deletaManga(int id);

std::vector<int> geraSequenciaDeGaps(int tam);
