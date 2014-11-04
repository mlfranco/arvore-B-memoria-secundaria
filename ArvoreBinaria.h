//Define Tipochave como vetor de 20 caracteres
typedef char TipoChave[20];
//Estrutura registro
typedef struct Registro{
  TipoChave Chave;
  int numOcorrencias;
} Registro;

//Tipo de dados Apontador que é um alias de ponteiro para nó
typedef struct No* Apontador;

//Estrutura Nó
typedef struct No{
  Registro Reg;
  Apontador Esq, Dir;
  int ocorrencias;
  int balanceamento; /* Deverá ser ignorado para ABB, contendo sempre o valor 0 */
} No;

//Alias para o tipo apontador
typedef Apontador TipoDicionario;

//Inicializa a árvore com o valor NULL, ou seja, a árvore inicia vazia (sem nós)
void inicializar(Apontador *arvore);

//Rotação dos nós para esquerda para balanceamento
void rotacaoEsquerda(Apontador *pai, int *alt);

//Rotação dos nós para direita para balanceamento
void rotacaoDireita(Apontador *pai, int *alt);

//Rotação dos nós para esquerda e depois direita para balanceamento
void rotacaoEsqDir(Apontador *pai, int *alt);

//Rotação dos nós para direita e depois esquerda para balanceamento
void rotacaoDirEsq(Apontador *pai, int *alt);

//insere registro na árvore balanceando utilizando AVL
void inserirAVL(Apontador *arvore, Registro reg, int *alt);

//insere registro na árvore binária de busca
void inserirABB(Apontador *arvore, Registro registro);

//Libera todos os espaços de memória alocados para a árvore binária
void destruir(Apontador *arvore);

//Busca um nó cujo registro possue a chave de busca.
void buscar(Apontador *arvore, TipoChave chave);

//Imprime os elementos de uma árvore em pré-ordem.
void imprimir(Apontador *arvore);
