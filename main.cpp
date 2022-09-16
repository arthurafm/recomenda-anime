#include <iostream>
#include <fstream>
#include "include\Operacoes.h"

int main()
{

    /* 3. Realizar a coleta e a persistência de dados de maneira incremental, o programa deve manter os dados nos arquivos e, ao carregar, o programa deve ler os
          dados processados anteriormente. Se novos dados forem processados, eles devem ser adicionados aos já existentes. */
    int csv_cond = 0, csv_flag = 0;
    std::string csv_nome_anime, csv_nome_manga;
    if(true){//if((ArquivoExiste("anime.bin") == -1) || (ArquivoExiste("manga.bin") == -1)){

    /* 1. Processar dados brutos provenientes da Web ou a partir de arquivos locais, do tipo TXT, CSV, HTML ou XML, os quais serão a fonte de dados inicial;
          O programa deve importar múltiplos documentos de entrada. */
        std::cout << "Digite o nome do CSV de Anime: " << std::endl;
        fflush(stdin);
        std::cin >> csv_nome_anime;
        std::cout << "Digite o nome do CSV de Manga: " << std::endl;
        fflush(stdin);
        std::cin >> csv_nome_manga;
        ProcessaArquivoCSV(csv_nome_anime, csv_nome_manga, csv_flag);
    }
    else{
        std::cout << "Voce quer ler um CSV novo?\n1 para Sim, 0 para Nao" << std::endl;
        std::cin >> csv_cond;
        if(csv_cond == 1){
            std::cout << "Digite o nome do CSV de Anime: " << std::endl;
            fflush(stdin);
            std::cin >> csv_nome_anime;
            std::cout << "Digite o nome do CSV de Manga: " << std::endl;
            fflush(stdin);
            std::cin >> csv_nome_manga;
            csv_flag = 1;
            ProcessaArquivoCSV(csv_nome_anime, csv_nome_manga, csv_flag);
        }
    }


    char nome1[200], nome2[200];
    int op_code, id;
    std::vector<int> ids = {};

    trie_string* raiz_licensors = cria_trie_string('\0');
    raiz_licensors = cria_arq_inv(raiz_licensors, LICENSORS);
    trie_string* raiz_genres = cria_trie_string('\0');
    raiz_genres = cria_arq_inv(raiz_genres, GENRES);
    trie_string* raiz_studios = cria_trie_string('\0');
    raiz_studios = cria_arq_inv(raiz_studios, STUDIOS);

    do{
        std::cout << "Selecione a operacao desejada:" << std::endl
        << "1: Recomendar Anime" << std::endl << "2: Buscar Anime" << std::endl << "3: Excluir Anime"
        << std::endl << "4: Top Anime ordenado" << std::endl << "5: Top Anime inverso" << std::endl
        << "6: Buscar Anime por prefixo" << std::endl << "7: Buscar Anime por genero" << std::endl
        << "8: Buscar Anime por estudio" << std::endl << "9: Buscar Anime por genero e licensiador"
        << std::endl << "10: Buscar Anime por dois studios"
        << std::endl << "-1: Recomendar Manga" << std::endl << "-2: Buscar Manga" << std::endl
        << "-3: Excluir Manga" << std::endl << "-4: Top Manga" << std::endl << "-5: Top Manga inverso"
        << std::endl << "-6: Buscar Manga por prefixo" << std::endl << "-7: Buscar Manga por dois campos"
        << std::endl << "-8: Buscar Manga por dois do mesmo campo"
        << std::endl << std::endl << "0: Sair" << std::endl;
        std::cin >> op_code;
        switch(op_code){
            case 1:
                std::cout << "Digite o ID:";
                std::cin >> id;
                recomendaAnime(id, raiz_genres, raiz_studios);
                break;
                /* 5. Permitir a busca de informações dos arquivos locais por algum critério.
                  (a) busca pela chave principal de um elemento é obrigatória. */
            case 2:{
                std::cout << "Digite o ID:";
                std::cin >> id;
                buscaAnimePorID(id);
            }
                break;
                /* 1. Tratar exclusão de registros, o que envolve a implementação de funções para remover elementos das
                      mais diversas estruturas de dados implementados. */
            case 3:
                std::cout << "Digite o ID:";
                std::cin >> id;
                deletaAnime(id);
                break;
                /* 4. Permitir ao usuário classificar os dados dos arquivos locias em ordem normal e inversa;
                  para visualização não ficar muito poluída, pode-se mostrar apenas os TOP N resultados ordenados. */
            case 4:
                ordenaAnime();
                break;
            case 5:
                ordenaAnimeInverso();
                break;
                /* 2. Fazer buscas por prefixo */
            case 6:
                std::cout << "Digite o nome: ";
                fflush(stdin);
                gets(nome1);
                buscaAnimePorPrefixo(nome1);
                break;
            /* 5. (b) além do acesso a chave usado a chave principal, deverá ser implementado pelo menos um arquivo
                      invertido para um dos outros campos, onde será possível consultar todas as ocorrências de um dado valor. */
            case 7:
                std::cout << "Digite o nome do genero: ";
                fflush(stdin);
                gets(nome1);
                Busca_Um_Campo(nome1, raiz_genres);
                break;
            case 8:
                std::cout << "Digite o nome do estudio: ";
                fflush(stdin);
                gets(nome1);
                Busca_Um_Campo(nome1, raiz_studios);
                break;
                /* 4. Fazer buscas de múltiplos campos em paralelo. */
            case 9:
                std::cout << "Digite o nome do genero: ";
                fflush(stdin);
                gets(nome1);
                std::cout << "Digite o nome do licensiador: ";
                fflush(stdin);
                gets(nome2);
                Busca_Dois_Campos(nome1, nome2, raiz_genres, raiz_licensors);
                break;
                /* 3. Fazer buscas de múltiplos valores de um dado campo. */
            case 10:
                std::cout << "Digite o nome do studio 1: ";
                fflush(stdin);
                gets(nome1);
                std::cout << "Digite o nome do studio 2: ";
                fflush(stdin);
                gets(nome2);
                Busca_Dois_Mesmo_Campo(nome1, nome2, raiz_studios);
            case -1:

                break;
                /* 5. Permitir a busca de informações dos arquivos locais por algum critério.
                  (a) busca pela chave principal de um elemento é obrigatória. */
            case -2:{
                std::cout << "Digite o ID:";
                std::cin >> id;
                buscaMangaPorID(id);
            }
                break;
                /* 1. Tratar exclusão de registros, o que envolve a implementação de funções para remover elementos das
                      mais diversas estruturas de dados implementados. */
            case -3:
                std::cout << "Digite o ID:";
                std::cin >> id;
                deletaManga(id);
                break;
                /* 4. Permitir ao usuário classificar os dados dos arquivos locias em ordem normal e inversa;
                  para visualização não ficar muito poluída, pode-se mostrar apenas os TOP N resultados ordenados. */
            case -4:
                ordenaManga();
                break;
            case -5:
                ordenaMangaInverso();
                break;
                /* 2. Fazer buscas por prefixo */
            case -6:
                std::cout << "Digite o nome: ";
                fflush(stdin);
                gets(nome1);
                buscaMangaPorPrefixo(nome1);
                break;
            case -7:
                break;
            case -8:
                break;
            case 0:
                op_code = 0;
                break;
            default:
                std::cout << "Operacao invalida." << std::endl;
                break;
        }
    }while(op_code != 0);


    free_trie_string(raiz_genres);
    free_trie_string(raiz_licensors);
    free_trie_string(raiz_studios);
    return 0;
}
