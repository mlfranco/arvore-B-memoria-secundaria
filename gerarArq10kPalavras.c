#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000


typedef char TipoChave[20];


short hifenValido(char *str, long posicaoHifen){
  /*
  Verifica se o uso de um hifen é valido no contexto de uma palavra
  */

  long tamanho = strlen(str);

  short posicaoValida = posicaoHifen > 0L && posicaoHifen+1 < tamanho;

  short ehHifen = str[posicaoHifen] == '-';

  short hifenCorreto = isalpha(str[posicaoHifen-1]) && isalpha(str[posicaoHifen+1]);

  return posicaoValida && ehHifen && hifenCorreto;
}


void parser(char *str){
  /*
  Remove todas as pontuações da string e substitui letras maiúsculas por minúsculas
  */

  long i, j, tamanho = strlen(str);
  for (i = 0L, j = 0L ; i < tamanho ; i++)
    if (hifenValido(str, i) || isalpha(str[i])){
      str[j] = tolower(str[i]);
      j++;
    }

  str[j] = '\0';
}


void inicializarHashTable(TipoChave hashTable[MAX]){
  /*
  Inicializa a hash table com caracteres '\0'
  */
  int i;
  for (i = 0 ; i < MAX ; i++)
    strcpy(hashTable[i], "\0");
}


int hashing(char* str){
  /*
  Cálcula o valor hash de uma string e retorna o resultado
  */
  int i, tamanho = strlen(str), soma = 0;
  for (i = 0 ; i < tamanho-1 ; i++)
    soma += str[i];
  return soma % MAX;
}


void inserirHashTable(TipoChave hashTable[MAX], int* tamanho, TipoChave str, int posicao){
  /*
  Insere string na hash table usando tratamento de colisão
  */
  if (*tamanho < MAX){
    while (strcmp(hashTable[posicao], "\0") && strcmp(hashTable[posicao], str))
      posicao = (posicao+1) % MAX;

    if (strcmp(str, hashTable[posicao])){
      strcpy(hashTable[posicao], str);
      (*tamanho)++;
    }
  }
}

int main(){
  /*
  Gera um arquivo de até MAX palavras diferentes, utilizando um arquivo de texto como base para extraí-las
  OBS.: Apenas depende do arquivo base conter palavras suficientes, para que sejam selecionadas MAX palavras
  diferentes, através do uso de hashing, a serem inseridas em um novo arquivo de texto
  */

  int i, posicao, tamanhoHashTable = 0;
  TipoChave palavra, hashTable[MAX];
  inicializarHashTable(hashTable);

  /*
  Leitura de um arquivo de texto base e inserção de suas palvras na tabela hash (hashTable)  
  */
  char nomeArq[90];
  printf("Digite o nome do arquivo base para gerar as palavras: ");
  fgets(nomeArq,90,stdin);
  nomeArq[strlen(nomeArq)-1] = '\0';

  FILE* arquivo = fopen(nomeArq, "r");
  if (!arquivo){
    puts("ERRO");
    exit(0);
  }

  while (tamanhoHashTable < MAX && !feof(arquivo)){
    fscanf(arquivo, "%s ", palavra);
    parser(palavra);
    posicao = hashing(palavra);
    inserirHashTable(hashTable, &tamanhoHashTable, palavra, posicao);
  }
  fclose(arquivo);

  /*
  Informa o número de palavras diferentes encontradas
  */
  printf("Numero de palavras diferentes geradas: %d\n", tamanhoHashTable);

  /*
  Insere o conteúdo da tabela hash (hashTable) em um arquivo de texto
  */
  printf("Digite o nome do arquivo para armazenar as palavras: ");
  fgets(nomeArq,90,stdin);
  nomeArq[strlen(nomeArq)-1] = '\0';

  arquivo = fopen(nomeArq, "w");
  for (i = 0 ; i < MAX ; i++){
    if (strcmp(hashTable[i], "\0"))
      fprintf(arquivo, "%s ", hashTable[i]);
  }
  fclose(arquivo);

  /*
  Fim da execução do programa
  */
  return 0;
}
