#include <iostream>
#include <fstream>
#include "include\Operacoes.h"

int main()
{

    /* 3. Realizar a coleta e a persist�ncia de dados de maneira incremental, o programa deve manter os dados nos arquivos e, ao carregar, o programa deve ler os
          dados processados anteriormente. Se novos dados forem processados, eles devem ser adicionados aos j� existentes. */
    if((ArquivoExiste("anime.bin") == -1) && (ArquivoExiste("manga.bin") == -1)){

    /* 1. Processar dados brutos provenientes da Web ou a partir de arquivos locais, do tipo TXT, CSV, HTML ou XML, os quais ser�o a fonte de dados inicial;
          O programa deve importar m�ltiplos documentos de entrada. */
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
                /* 5. Permitir a busca de informa��es dos arquivos locais por algum crit�rio.
                  (a) busca pela chave principal de um elemento � obrigat�ria. */
            case 2:{
                std::cout << "Digite o ID:";
                std::cin >> id;
                buscaAnimePorID(id);
            }
                break;
                /* 1. Tratar exclus�o de registros, o que envolve a implementa��o de fun��es para remover elementos das
                      mais diversas estruturas de dados implementados. */
            case 3:
                std::cout << "Digite o ID:";
                std::cin >> id;
                deletaAnime(id);
                break;
                /* 4. Permitir ao usu�rio classificar os dados dos arquivos locias em ordem normal e inversa;
                  para visualiza��o n�o ficar muito polu�da, pode-se mostrar apenas os TOP N resultados ordenados. */
            case 4:
                ordenaAnime();
                break;
            case 5:
                ordenaAnimeInverso();
                break;
            case -1:
                break;
                /* 5. Permitir a busca de informa��es dos arquivos locais por algum crit�rio.
                  (a) busca pela chave principal de um elemento � obrigat�ria. */
            case -2:{
                std::cout << "Digite o ID:";
                std::cin >> id;
                buscaMangaPorID(id);
            }
                break;
                /* 1. Tratar exclus�o de registros, o que envolve a implementa��o de fun��es para remover elementos das
                      mais diversas estruturas de dados implementados. */
            case -3:
                std::cout << "Digite o ID:";
                std::cin >> id;
                deletaManga(id);
                break;
                /* 4. Permitir ao usu�rio classificar os dados dos arquivos locias em ordem normal e inversa;
                  para visualiza��o n�o ficar muito polu�da, pode-se mostrar apenas os TOP N resultados ordenados. */
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
