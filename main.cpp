#include <iostream>
#include <fstream>
#include "include\Registro.h"
#include "include\Arquivos.h"

int main()
{

    /* 3. Realizar a coleta e a persistência de dados de maneira incremental, o programa deve manter os dados nos arquivos e, ao carregar, o programa deve ler os
          dados processados anteriormente. Se novos dados forem processados, eles devem ser adicionados aos já existentes. */
    if((ArquivoExiste("bin_anime.bin") == -1) && (ArquivoExiste("bin_manga.bin") == -1)){

        /* 1. Processar dados brutos provenientes da Web ou a partir de arquivos locais, do tipo TXT, CSV, HTML ou XML, os quais serão a fonte de dados inicial;
              O programa deve importar múltiplos documentos de entrada.*/
        ProcessaArquivoCSV();
    }
    int op_code;
    do{
        std::cout << "Selecione a operacao desejada:" << std::endl << "1- Recomendar" << std::endl << "2- Buscar" << std::endl << "3- Adicionar" << std::endl << "4- Excluir"
        << std::endl << "5- Classificar ordenado" << std::endl << "6- Classificar inverso" << std::endl << "0- Sair" << std::endl;
        std::cin >> op_code;
        switch(op_code){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
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
