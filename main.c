#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ArvoreBinaria.h"

#define MAX_INPUT 100


short hifenValido(char *str, long posicaoHifen){
  /*
  Verifica se o uso de um hifen é valido no contexto de uma palavra.
  Parâmetros de entrada:
    char *str - Uma palavra ser verificada
    long posicaoHifen - Posição do hifen na palavra
  Retorno:
     0 caso hifen seja inválido
     1 caso hifen for válido
  */

  long tamanho = strlen(str);

  short posicaoValida = posicaoHifen > 0L && posicaoHifen+1 < tamanho;

  short ehHifen = str[posicaoHifen] == '-';

  short hifenCorreto = 0;

  if (posicaoValida)
    hifenCorreto = isalpha(str[posicaoHifen-1]) && isalpha(str[posicaoHifen+1]);

  return posicaoValida && ehHifen && hifenCorreto;
}


void parser(char *str){
  /*
  Remove todas as pontuações da string e substitui letras maiúsculas por minúsculas.
  Parâmetros de entrada:
    char *str - Uma texto a ser percorrido, removendo espaços e outros caracteres especiais
  Retorno:
     A própria variavel de entrada é modificada.
  */

  long i, j, tamanho = strlen(str);
  for (i = 0L, j = 0L ; i < tamanho ; i++)
    if (hifenValido(str, i) || isalpha(str[i])){
      str[j] = tolower(str[i]);
      j++;
    }

  str[j] = '\0';
}


double lerArquivo(TipoDicionario *arvore, char *nomeArquivo, int opcao){
  /*
  Lê os dados de um arquivo e os insere em uma árvore binária escolhida de acordo com a opção
  Opção 0: árvore binária de busca sem balanceamento (ABB)
  Opção 1: árvore binária de busca com balanceamento (AVL)

  Parâmetros de entrada:
    TipoDicionario *arvore - Referencia para árvore.
    char *nomeArquivo-  Arquivo a ser aberto.
    int opcao - Opção que indica a maneira de como será inserido os dados.
    char *str - Uma texto a ser percorrido, removendo espaços e outros caracteres especiais
  Retorno:
     Double:
      -1 caso o arquivo não seja encontrado
      Tempo de execução da inserção de dados em arquivo.
  */

  /*
  Abertura do arquivo em modo de leitura e retorna -1, que notifica em caso de erro
  */
  FILE* arquivo = fopen(nomeArquivo, "r");
  if (!arquivo)
    return -1;

  /*
  Leitura dos dados do arquivo
  */
  clock_t inicio, fim;
  double tempoTotal = 0;

  char* palavra = malloc(sizeof(TipoChave));
  while(!feof(arquivo)){
    fscanf(arquivo, "%s ", palavra);
    parser(palavra);

    /*
    Inserção da palavra lida, na árvore binária selecionada, de acordo com a opção
    */
    if (strcmp(palavra, "")){
      Registro registro;
      strcpy(registro.Chave, palavra);

      inicio = clock();
      if (opcao){
        int alt = 0;
        inserirAVL(arvore, registro, &alt);
      }else
        inserirABB(arvore, registro);
      fim = clock();
      tempoTotal += (fim - inicio) / (double)CLOCKS_PER_SEC;
    }
  }

  /*
  Fecha o arquivo e retorna o tempo total gasto na inserção, que notifica o sucesso de execução
  */
  fclose(arquivo);
  return tempoTotal;
}


void menu(TipoDicionario *arvoreABB, TipoDicionario *arvoreAVL){
  /*
  Identifica comando de entrada e realiza a ação apropriada

  OBS.: De acordo com o enunciado, não é necessário o tratamento de comandos de entrada
  inválidos, portanto este tratamento não foi realizado nesta função

  Parâmetros de entrada:
    TipoDicionario *arvoreABB -> Referência para árvore Binária de Busca
    TipoDicionario *arvoreAVL -> Referência para árvore Binária Balanceada AVL
  Retorno:
    Nenhum
  */


  /*
  Leitura da entrada
  */
  char entrada[MAX_INPUT];
  fgets(entrada,MAX_INPUT,stdin);

  /*
  Divide o comando de entrada em até três partes, sendo elas:
    - comando: identifica a operação a ser realizada
    - tipo: identifica o tipo de árvore binária de busca (ABB ou AVL)
    - nome_arquivo: identifica o nome do arquivo a ser lido
  */
  int tamanho = strlen(entrada);
  char comando[3], tipo[4], nome_arquivo[tamanho - 7];
  strncpy(comando, entrada, 2);
  if(strcmp(comando,"FM")){
    if(strcmp(comando,"IA")){

      strncpy(nome_arquivo, entrada + 3, tamanho - 8);
      nome_arquivo[tamanho - 8] = '\0';
    }
    strncpy(tipo, entrada + tamanho - 4, 3);
    tipo[3] = '\0';
  }
  comando[2] = '\0';

  /*
  Identifica o comando de entrada e realiza a operação adequada
  */
  if (!strcmp(comando, "IR")){ //Inserção em árvore binária
    double tempoTotal;
    if(strcmp(tipo,"ABB")){
      tempoTotal = lerArquivo(arvoreAVL, nome_arquivo, 1);
      if (tempoTotal < 0){
        puts("ERRO");
        return;
      }else
        puts("SUCESSO");
    }else{
      tempoTotal = lerArquivo(arvoreABB, nome_arquivo, 0);
      if (tempoTotal < 0){
        puts("ERRO");
        return;
      }else
        puts("SUCESSO");
    }

    /*
    Imprime em tela o tempo total gasto na inserção
    */
    printf("Tempo total gasto: %lfs\n", tempoTotal);

  }else if(!strcmp(comando, "BR")){ //Busca em árvore binária
    /*
    Abertura do arquivo em modo de leitura e notifica em caso de erro
    */
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo){
      puts("ERRO");
      return;
    }

    /*
    Leitura dos dados do arquivo
    */
    clock_t inicio, fim;
    double tempoTotal = 0;

    char* palavra = malloc(sizeof(TipoChave));
    while(!feof(arquivo)){
      fscanf(arquivo, "%s ", palavra);

      /*
      Busca da palavra lida, na árvore binária selecionada, de acordo com a opção
      e calcula o tempo total gasto na busca
      */
      inicio = clock();
      if(strcmp(tipo,"ABB"))
        buscar(arvoreAVL, palavra);
      else
        buscar(arvoreABB, palavra);
      fim = clock();
      tempoTotal += (fim - inicio) / (double)CLOCKS_PER_SEC;
    }

    /*
    Imprime em tela o tempo total gasto na busca
    */
    printf("Tempo total gasto: %lfs\n", tempoTotal);

  }else if(!strcmp(comando, "IA")){ //Impressão em pré-ordem de árvore binária
    if(strcmp(tipo,"ABB"))
      imprimir(arvoreAVL);
    else
      imprimir(arvoreABB);

  }else if(!strcmp(comando, "FM")){ //Finalização do programa
    destruir(arvoreABB);
    destruir(arvoreAVL);
    exit(0);
  }
}



int main(){
  /*
  Criação e inicialização das árvores ABB e AVL
  */
  TipoDicionario arvoreABB;
  inicializar(&arvoreABB);
  TipoDicionario arvoreAVL;
  inicializar(&arvoreAVL);

  /*
  Loop de execução do algoritmo, de acordo com um menu de comandos de entrada, que continua
  até que o comando de finalização do programa seja executado na função menu()
  */
  while(1){
    menu(&arvoreABB, &arvoreAVL);
  }

  /*
  Encerramento do programa
  */
  return 0;
}
