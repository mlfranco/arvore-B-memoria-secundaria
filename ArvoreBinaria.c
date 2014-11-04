/*
Referencia: Jayme Luiz Szwarcfiter & Lilian Markenzon
            Estruturas de Dados e seus Algoritmos
            LTC Editora, 1994
Adaptacao do codigo de Nivio Ziviani, Projeto de Algoritmos
Grupo:
-
-
-
-
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArvoreBinaria.h"


void inicializar(TipoDicionario *arvore){
  /*
  Inicializa a árvore com o valor NULL, ou seja, a árvore inicia vazia (sem nós)
  Parâmetros de entrada:
    TipoDicionario *arvore - arvore a ser inicializada com NULL
  Retorno:
    Nenhum
  */

  *arvore = NULL;
}


void rotacaoEsquerda(TipoDicionario *pai, int *alt){
  /*
  Faz a rotacao para a esquerda
  Parâmetros de entrada:
    TipoDicionario *pai - Nó a ser balanceado
    int* alt - variável que retorna 0 indicando que a rotação não desbalanceou a árvore
  Retorno:
    Nenhum
  */

  TipoDicionario filho = (*pai)->Dir;  //passando para filho do nó desbalanceado
  (*pai)->Dir = filho->Esq; //direita de p aponta para null
  filho->Esq = (*pai);
  (*pai)->balanceamento = 0;
  (*pai) = filho;
  (*pai)->balanceamento = 0;//aqui o pai é o filho
  (*alt) = 0;
}


void rotacaoDireita(TipoDicionario *pai, int *alt){
  /*
  Faz a rotacao para a Direita
  Parâmetros de entrada:
    TipoDicionario *pai - Nó a ser balanceado
    int* alt - variável que retorna 0 indicando que a rotação não desbalanceou a árvore
  Retorno:
    Nenhum
  */

  TipoDicionario filho = (*pai)->Esq;  //passando para filho do nó desbalanceado
  (*pai)->Esq = filho->Dir;
  filho->Dir = (*pai);
  (*pai)->balanceamento = 0;
  (*pai) = filho;
  (*pai)->balanceamento = 0;
  (*alt) = 0;
}


void rotacaoEsqDir(TipoDicionario *pai, int *alt){
  /*
  Faz a rotaçao para esquerda depois para direita.
  Os nós filho e neto rotacionados recebem o o balaceamento adequado.
  pai
   \
   filho
    \
    neto
  Parâmetros de entrada:
    TipoDicionario *pai - Nó a ser balanceado
    int* alt - variável que retorna 0 indicando que a rotação não desbalanceou a árvore
  Retorno:
    Nenhum
  */

  TipoDicionario filho = (*pai)->Esq;  //passando para filho do nó desbalanceado
  TipoDicionario neto = filho->Dir;
  filho->Dir = neto->Esq;    neto->Esq = filho; //direita de filho aponta para null e filho se torna filho esquerdo de neto
  (*pai)->Esq = neto->Dir;  neto->Dir = (*pai); //esquerda de p aponta para null  e p se torna filho  direito de neto

  if (neto->balanceamento == -1)
    (*pai)->balanceamento = 1;
  else
    (*pai)->balanceamento = 0;

  if (neto->balanceamento == 1)
    filho->balanceamento = -1;
  else
    filho->balanceamento = 0;

  (*pai) = neto;
  (*pai)->balanceamento = 0;
  (*alt) = 0;
}


void rotacaoDirEsq(TipoDicionario *pai, int *alt){
  /*
  Faz a rotaçao para direita depois para esquerda.
  Os nós filho e neto rotacionados recebem o o balaceamento adequado.
  pai
   \
   filho
    \
    neto
  Parâmetros de entrada:
    TipoDicionario *pai - Nó a ser balanceado
    int* alt - variável que retorna 0 indicando que a rotação não desbalanceou a árvore
  Retorno:
    Nenhum
  */


  TipoDicionario filho = (*pai)->Dir;  //passando para filho do nó desbalanceado
  TipoDicionario neto = filho->Esq;
  filho->Esq = neto->Dir;    neto->Dir = filho; //esq de filho aponta para null e filho se torna filho direito de neto
  (*pai)->Dir = neto->Esq;  neto->Esq = (*pai); //dir de p aponta para null  e p se torna filho  esquerdo de neto

  if (neto->balanceamento == 1)
    (*pai)->balanceamento = -1;
  else
    (*pai)->balanceamento = 0; //atualiza FB de p

  if (neto->balanceamento == -1)
    filho->balanceamento = 1;
  else
    filho->balanceamento = 0; //atualiza FB de filho

  (*pai) = neto; //neto agora é p
  (*pai)->balanceamento = 0; //atualiza FB de p
  (*alt) = 0;
}


void inserirAVL(TipoDicionario *arvore, Registro reg, int *alt){
  /*
  Insere o registro reg na árvore referenciada por arvore.
  alt retorna se houve ou nao alteracao na altura da subarvore do no em questao,
  induzindo a atualizacao do campo balanceamento.
  Parâmetros de entrada:
    TipoDicionario *arvore - referência para arvore onde o elemento será inserido
    Registro reg - registro a ser inserido a árvore
    int *alt - variavel indicando que balanceamento deve ser verificado
  Parâmetros de saída:
    Nenhum
  */

  *alt = 0;
  if (*arvore == NULL){ // insere o registro na árvore
    *arvore = (TipoDicionario)malloc(sizeof(No));
    (*arvore)->Reg = reg;
    (*arvore)->Esq = (*arvore)->Dir = NULL;
    (*arvore)->Reg.numOcorrencias = (*arvore)->ocorrencias = 1;
    (*arvore)->balanceamento = 0;
    *alt = 1;  // balanceamento deve ser verificado
  }else if (strcmp(reg.Chave, (*arvore)->Reg.Chave) < 0) {
    inserirAVL(&(*arvore)->Esq, reg, alt);
    if (*alt) {   // verifica balanceamento
      switch ((*arvore)->balanceamento) {
        case  1: // subarvores esquerda e direita passam a ter a mesma altura
          (*arvore)->balanceamento = 0;
          (*alt) = 0;
          break;
        case  0: // subarvore esquerda passa a ter uma unidade de altura maior do que a da direita
          (*arvore)->balanceamento = -1;
          break;
        case -1: // subarvore esquerda passa a ter duas unidades de altura maior do que a da direita
          if ((*arvore)->Esq->balanceamento == -1)
            rotacaoDireita(&(*arvore), alt);
          else
            rotacaoEsqDir(&(*arvore), alt);
          break;
      }
    }
  }else if (strcmp(reg.Chave, (*arvore)->Reg.Chave) > 0) {
    inserirAVL(&(*arvore)->Dir, reg , alt);
    if (*alt) {   // verifica balanceamento
      switch ((*arvore)->balanceamento) {
        case -1: // subarvores esquerda e direita passam a ter a mesma altura
          (*arvore)->balanceamento = 0;
          (*alt) = 0;
          break;
        case  0: // subarvore direita passa a ter uma unidade de altura maior do que a da esquerda
          (*arvore)->balanceamento = 1;
          break;
        case  1: // subarvore direita passa a ter duas unidades de altura maior do que a da esquerda
          if ((*arvore)->Dir->balanceamento == 1)
            rotacaoEsquerda(&(*arvore), alt);
          else
            rotacaoDirEsq(&(*arvore), alt);
        break;
      }
    }
  }else{
    *alt = 0;
    (*arvore)->Reg.numOcorrencias = ++(*arvore)->ocorrencias;
  }
}


void inserirABB(TipoDicionario *arvore, Registro registro){
  /*
  Insere um dado registro, em uma árvore binária de busca (ABB)

  Parâmetros de entrada:
    TipoDicionario *arvore - referência para arvore onde o elemento será inserido
    Registro reg - registro a ser inserido a árvore
    int *alt - variavel indicando que balanceamento deve ser verificado
  Parâmetros de saída:
    Nenhum
  */
  if (*arvore == NULL){ // insere o registro na árvore
    *arvore = (TipoDicionario)malloc(sizeof(No));
    (*arvore)->Reg = registro;
    (*arvore)->Esq = (*arvore)->Dir = NULL;
    (*arvore)->Reg.numOcorrencias = (*arvore)->ocorrencias = 1;
    (*arvore)->balanceamento = 0;
  }
  else if (strcmp(registro.Chave, (*arvore)->Reg.Chave) > 0){ // vai para a subarvore à diretia
    inserirABB(&((*arvore)->Dir), registro);
  }
  else if (strcmp(registro.Chave, (*arvore)->Reg.Chave) < 0){ // vai para a subarvore à esquerda
    inserirABB(&((*arvore)->Esq), registro);
  }
  else // o registro já existe, portanto só incrementa seu número de ocorrências
    (*arvore)->Reg.numOcorrencias = ++(*arvore)->ocorrencias;
}


void destruir(TipoDicionario *arvore){
  /*
  Libera todos os espaços de memória alocados para a árvore binária.

  Parâmetros de entrada:
    TipoDicionario *arvore - referencia da raiz da árvore a ser destruída.
  Parâmetros de saída:
    Nenhum
  */

  if (*arvore == NULL)
    return;
  destruir(&(*arvore)->Esq);
  destruir(&(*arvore)->Dir);
  free(*arvore);
}


void buscar(TipoDicionario *arvore, TipoChave chave){
  /*
  Busca um nó cujo registro possue a chave de busca.
  Parâmetros de entrada:
    TipoDicionario *arvore - referencia da raiz da árvore utilizada na busca.
    TipoChave chave - Chave que contem o elemnto a ser buscado.
  Parâmetros de saída:
    Nenhum
  */

  if ((*arvore) == NULL)
    printf("%s NAO_ENCONTRADO 0\n", chave);
  else if (strcmp(chave, (*arvore)->Reg.Chave) > 0)
    buscar(&(*arvore)->Dir, chave);
  else if (strcmp(chave, (*arvore)->Reg.Chave) < 0)
    buscar(&(*arvore)->Esq, chave);
  else
    printf("%s ENCONTRADO %d\n", chave, (*arvore)->Reg.numOcorrencias);
}


void imprimir(TipoDicionario *arvore){
  /*
  Imprime o registro de todos os nós da árvore binária em Pré-ordem.
  Imprime no formato <chave> <ocorrencias> <balanceamento>
  Parâmetros de entrada:
    TipoDicionario *arvore - referencia da raiz da árvore a ser percorrida.
  Parâmetros de saída:
    Nenhum
  */

  if (*arvore == NULL)
    return;
  printf("%s %d %d\n",(*arvore)->Reg.Chave, (*arvore)->Reg.numOcorrencias, (*arvore)->balanceamento);
  imprimir(&(*arvore)->Esq);
  imprimir(&(*arvore)->Dir);
}
