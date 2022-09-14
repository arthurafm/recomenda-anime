#include <iostream>
#include <fstream>
#include "include\Operacoes.h"

int main()
{

    /* 3. Realizar a coleta e a persistência de dados de maneira incremental, o programa deve manter os dados nos arquivos e, ao carregar, o programa deve ler os
          dados processados anteriormente. Se novos dados forem processados, eles devem ser adicionados aos já existentes. */
    if((ArquivoExiste("anime.bin") == -1) && (ArquivoExiste("manga.bin") == -1)){

    /* 1. Processar dados brutos provenientes da Web ou a partir de arquivos locais, do tipo TXT, CSV, HTML ou XML, os quais serão a fonte de dados inicial;
          O programa deve importar múltiplos documentos de entrada. */
        ProcessaArquivoCSV();
    }
    int op_code, id;
    do{
        std::cout << "Selecione a operacao desejada:" << std::endl
        << "1: Recomendar Anime" << std::endl << "2: Buscar Anime" << std::endl << "3: Excluir Anime"
        << std::endl << "4: Top Anime ordenado" << std::endl << "5: Top Anime inverso" << std::endl
        << "-1: Recomendar Manga" << std::endl << "-2: Buscar Manga" << std::endl << "-3: Excluir Manga"
        << std::endl << "-4: Top Manga" << std::endl << "-5: Top Manga inverso" << std::endl
        << std::endl << "0: Sair" << std::endl;
        std::cin >> op_code;
        switch(op_code){
            case 1:
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
            case 0:
                op_code = 0;
                break;
            default:
                std::cout << "Operacao invalida." << std::endl;
                break;
        }
    }while(op_code != 0);

    return 0;
}
