#include <stdio.h>
#include <stdlib.h>
#include <time.h>                               // utilizar o clock do pc para gerar os numeros aleatoriamente

# define TAM 20                                 // número de conjuntos a serem gerados

// #include "avl_tree.c"
// #include "b_tree.c"
// #include "rb_tree.c"

//****************************

//Variáveis Globais
int monitoramento_Avl_01 = 0;       // Monitoramento das execuções da função balanceamento_avl;
int monitoramento_Avl_02 = 0;       // Monitoramento das execuções da função adicionarNo_Avl;

int monitoramento_B_01 = 0;         // Monitoramento das execuções da função percorreArvore_b;
int monitoramento_B_02 = 0;         // Monitoramento das execuções da função adicionaChaveRecursivo_b;

int monitoramento_RB_01 = 0;        // Monitoramento das execuções da função adicionarNo_rb;
int monitoramento_RB_02 = 0;        // Monitoramento das execuções da função balancear_rb;

//****************************
//Árvore AVL
typedef struct no_avl {
  struct no_avl * pai;
  struct no_avl * esquerda;
  struct no_avl * direita;
  int valor;
}
No_Avl;

typedef struct arvore_avl {
  struct no_avl * raiz;
}
Arvore_Avl;

void balanceamento_avl(Arvore_Avl * , No_Avl * );
int altura_avl(No_Avl * );
int fb_avl(No_Avl * );
No_Avl * rsd_avl(Arvore_Avl * , No_Avl * );
No_Avl * rse_avl(Arvore_Avl * , No_Avl * );
No_Avl * rdd_avl(Arvore_Avl * , No_Avl * );
No_Avl * rde_avl(Arvore_Avl * , No_Avl * );

Arvore_Avl * criar_avl() {
  Arvore_Avl * arvore_avl = (Arvore_Avl*) malloc(sizeof(Arvore_Avl));
  arvore_avl -> raiz = NULL;
  return arvore_avl;
}

int vazia_avl(Arvore_Avl * arvore_avl) {
  return arvore_avl -> raiz == NULL;
}

No_Avl* criarNo_Avl(Arvore_Avl* arvore_avl, No_Avl* pai, int valor) {
    No_Avl *no_avl = malloc(sizeof(No_Avl));

    no_avl->pai = pai;
    no_avl->esquerda = NULL;
    no_avl->direita = NULL;
    no_avl->valor = valor;

    if (valor < pai->valor) {
        pai->esquerda = no_avl;
    } else {
        pai->direita = no_avl;
    }

    balanceamento_avl(arvore_avl, pai);

    return no_avl;
}

No_Avl* adicionarNo_Avl(Arvore_Avl* arvore_avl, No_Avl* no_avl, int valor) {
    monitoramento_Avl_02++;              // Monitoramento das execuções da função adicionarNo_Avl   
    if (valor < no_avl->valor) {
        if (no_avl->esquerda == NULL) {
            return criarNo_Avl(arvore_avl, no_avl, valor);
        } else {
            return adicionarNo_Avl(arvore_avl, no_avl->esquerda, valor);
        }
    } else {
        if (no_avl->direita == NULL) {
            return criarNo_Avl(arvore_avl, no_avl, valor);
        } else {
            return adicionarNo_Avl(arvore_avl, no_avl->direita, valor);
        }
    }
}

No_Avl* adicionar_Avl(Arvore_Avl* arvore_avl, int valor) {
    if (vazia_avl(arvore_avl)) {
        monitoramento_Avl_02++;
        No_Avl *no_avl = malloc(sizeof(No_Avl));

        no_avl->pai = NULL;
        no_avl->esquerda = NULL;
        no_avl->direita = NULL;
        no_avl->valor = valor;

        arvore_avl->raiz = no_avl;

        return no_avl;
    } else {
        return adicionarNo_Avl(arvore_avl, arvore_avl->raiz, valor);
    }
}

void remover_avl(Arvore_Avl * arvore_avl, No_Avl * no_avl) {
  if (no_avl -> esquerda != NULL) {
    remover_avl(arvore_avl, no_avl -> esquerda);
  }

  if (no_avl -> direita != NULL) {
    remover_avl(arvore_avl, no_avl -> direita);
  }

  if (no_avl -> pai == NULL) {
    arvore_avl -> raiz = NULL;
  } else {
    if (no_avl -> pai -> esquerda == no_avl) {
      no_avl -> pai -> esquerda = NULL;
    } else {
      no_avl -> pai -> direita = NULL;
    }
  }

  free(no_avl);
}

No_Avl * localizar_avl(No_Avl * no_avl, int valor) {
  if (no_avl -> valor == valor) {
    return no_avl;
  } else {
    if (valor < no_avl -> valor) {
      if (no_avl -> esquerda != NULL) {
        return localizar_avl(no_avl -> esquerda, valor);
      }
    } else {
      if (no_avl -> direita != NULL) {
        return localizar_avl(no_avl -> direita, valor);
      }
    }
  }

  return NULL;
}

void percorrerProfundidadeInOrder_avl(No_Avl * no_avl, void( * callback)(int)) {
  if (no_avl != NULL) {
    percorrerProfundidadeInOrder_avl(no_avl -> esquerda, callback);
    callback(no_avl -> valor);
    percorrerProfundidadeInOrder_avl(no_avl -> direita, callback);
  }
}

void percorrerProfundidadePreOrder_avl(No_Avl * no_avl, void( * callback)(int)) {
  if (no_avl != NULL) {
    callback(no_avl -> valor);
    percorrerProfundidadePreOrder_avl(no_avl -> esquerda, callback);
    percorrerProfundidadePreOrder_avl(no_avl -> direita, callback);
  }
}

void percorrerProfundidadePosOrder_avl(No_Avl * no_avl, void(callback)(int)) {
  if (no_avl != NULL) {
    percorrerProfundidadePosOrder_avl(no_avl -> esquerda, callback);
    percorrerProfundidadePosOrder_avl(no_avl -> direita, callback);
    callback(no_avl -> valor);
  }
}

void visitar_avl(int valor) {
  printf("%d ", valor);
}

void balanceamento_avl(Arvore_Avl * arvore_avl, No_Avl * no_avl) {
    monitoramento_Avl_01++;       // Monitoramento das execuções da função balanceamento_avl;
  while (no_avl != NULL) {
    int fator = fb_avl(no_avl);

    if (fator > 1) { //árvore mais pesada para esquerda
      //rotação para a direita
      if (fb_avl(no_avl -> esquerda) > 0) {
        //printf("RSD(%d)\n", no_avl -> valor);
        rsd_avl(arvore_avl, no_avl); //rotação simples a direita, pois o FB do filho tem sinal igual
      } else {
        //printf("RDD(%d)\n", no_avl -> valor);
        rdd_avl(arvore_avl, no_avl); //rotação dupla a direita, pois o FB do filho tem sinal diferente
      }
    } else if (fator < -1) { //árvore mais pesada para a direita
      //rotação para a esquerda
      if (fb_avl(no_avl -> direita) < 0) {
        //printf("RSE(%d)\n", no_avl -> valor);
        rse_avl(arvore_avl, no_avl); //rotação simples a esquerda, pois o FB do filho tem sinal igual
      } else {
        //printf("RDE(%d)\n", no_avl -> valor);
        rde_avl(arvore_avl, no_avl); //rotação dupla a esquerda, pois o FB do filho tem sinal diferente
      }
    }

    no_avl = no_avl -> pai;
  }
}

int altura_avl(No_Avl * no_avl) {
  int esquerda = 0, direita = 0;

  if (no_avl -> esquerda != NULL) {
    esquerda = altura_avl(no_avl -> esquerda) + 1;
  }

  if (no_avl -> direita != NULL) {
    direita = altura_avl(no_avl -> direita) + 1;
  }

  return esquerda > direita ? esquerda : direita; //max(esquerda,direita)
}

int fb_avl(No_Avl * no_avl) {
  int esquerda = 0, direita = 0;

  if (no_avl -> esquerda != NULL) {
    esquerda = altura_avl(no_avl -> esquerda) + 1;
  }

  if (no_avl -> direita != NULL) {
    direita = altura_avl(no_avl -> direita) + 1;
  }

  return esquerda - direita;
}

No_Avl * rse_avl(Arvore_Avl * arvore_avl, No_Avl * no_avl) {
  No_Avl * pai = no_avl -> pai;
  No_Avl * direita = no_avl -> direita;

  no_avl -> direita = direita -> esquerda;
  no_avl -> pai = direita;

  direita -> esquerda = no_avl;
  direita -> pai = pai;

  if (pai == NULL) {
    arvore_avl -> raiz = direita;
  } else {
    if (pai -> esquerda == no_avl) {
      pai -> esquerda = direita;
    } else {
      pai -> direita = direita;
    }
  }

  return direita;
}

No_Avl * rsd_avl(Arvore_Avl * arvore_avl, No_Avl * no_avl) {
  No_Avl * pai = no_avl -> pai;
  No_Avl * esquerda = no_avl -> esquerda;

  no_avl -> esquerda = esquerda -> direita;
  no_avl -> pai = esquerda;

  esquerda -> direita = no_avl;
  esquerda -> pai = pai;

  if (pai == NULL) {
    arvore_avl -> raiz = esquerda;
  } else {
    if (pai -> esquerda == no_avl) {
      pai -> esquerda = esquerda;
    } else {
      pai -> direita = esquerda;
    }
  }

  return esquerda;
}

No_Avl * rde_avl(Arvore_Avl * arvore_avl, No_Avl * no_avl) {
  no_avl -> direita = rsd_avl(arvore_avl, no_avl -> direita);
  return rse_avl(arvore_avl, no_avl);
}

No_Avl * rdd_avl(Arvore_Avl * arvore_avl, No_Avl * no_avl) {
  no_avl -> esquerda = rse_avl(arvore_avl, no_avl -> esquerda);
  return rsd_avl(arvore_avl, no_avl);
}
// Árvore AVL
//***************************************

// ************************
// Árvore B
typedef struct no_b {
  int total;
  int * chaves;
  struct no_b ** filhos;
  struct no_b * pai;
}
No_B;

typedef struct arvoreB {
  No_B * raiz;
  int ordem;
}
ArvoreB;

ArvoreB * criaArvore_b(int);
No_B * criaNo_b(ArvoreB * );
void percorreArvore_b(No_B * );
int pesquisaBinaria_b(No_B * , int);
int localizaChave_b(ArvoreB * , int);
No_B * localizaNo_b(ArvoreB * , int);
void adicionaChaveNo_b(No_B * , No_B * , int);
int transbordo_b(ArvoreB * , No_B * );
No_B * divideNo_h(ArvoreB * , No_B * );
void adicionaChaveRecursivo_b(ArvoreB * , No_B * , No_B * , int);
void adicionaChave_b(ArvoreB * , int);

ArvoreB * criaArvore_b(int ordem) {
  ArvoreB * a = malloc(sizeof(ArvoreB));
  a -> ordem = ordem;
  a -> raiz = criaNo_b(a);

  return a;
}

int contador = 0;

No_B * criaNo_b(ArvoreB * arvore) {
  int max = arvore -> ordem * 2;
  No_B * no_b = malloc(sizeof(No_B));

  no_b -> pai = NULL;

  no_b -> chaves = malloc(sizeof(int) * (max + 1));
  no_b -> filhos = malloc(sizeof(No_B) * (max + 2));
  no_b -> total = 0;

  for (int i = 0; i < max + 2; i++)
    no_b -> filhos[i] = NULL;

  return no_b;
}

void percorreArvore_b(No_B * no_b) {
    monitoramento_B_01++;       // Monitoramento das execuções da função percorreArvore_b;
  if (no_b != NULL) {
    for (int i = 0; i < no_b -> total; i++) {
      percorreArvore_b(no_b -> filhos[i]); //visita o filho a esquerda

      printf("%d ", no_b -> chaves[i]);
    }

    percorreArvore_b(no_b -> filhos[no_b -> total]); //visita ultimo filho (direita)
  }
}

int pesquisaBinaria_b(No_B * no_b, int chave) {
  int inicio = 0, fim = no_b -> total - 1, meio;

  while (inicio <= fim) {
    contador++;

    meio = (inicio + fim) / 2;

    if (no_b -> chaves[meio] == chave) {
      return meio; //encontrou	
    } else if (no_b -> chaves[meio] > chave) {
      fim = meio - 1;
    } else {
      inicio = meio + 1;
    }
  }
  return inicio; //não encontrou	
}

int localizaChave_b(ArvoreB * arvore, int chave) {
  No_B * no_b = arvore -> raiz;

  while (no_b != NULL) {
    int i = pesquisaBinaria_b(no_b, chave);

    if (i < no_b -> total && no_b -> chaves[i] == chave) {
      return 1; //encontrou
    } else {
      no_b = no_b -> filhos[i];
    }
  }

  return 0; //não encontrou	
}

No_B * localizaNo_b(ArvoreB * arvore, int chave) {
  No_B * no_b = arvore -> raiz;

  while (no_b != NULL) {
    contador++;

    int i = pesquisaBinaria_b(no_b, chave);

    if (no_b -> filhos[i] == NULL)
      return no_b; //encontrou nó
    else
      no_b = no_b -> filhos[i];
  }

  return NULL; //não encontrou nenhum nó
}

void adicionaChaveNo_b(No_B * no_b, No_B * novo, int chave) {
  int i = pesquisaBinaria_b(no_b, chave);

  contador++;

  for (int j = no_b -> total - 1; j >= i; j--) {
    no_b -> chaves[j + 1] = no_b -> chaves[j];
    no_b -> filhos[j + 2] = no_b -> filhos[j + 1];
  }

  no_b -> chaves[i] = chave;
  no_b -> filhos[i + 1] = novo;

  no_b -> total++;
}

int transbordo_b(ArvoreB * arvore, No_B * no_b) {
  contador++;

  return no_b -> total > arvore -> ordem * 2;
}

No_B * divideNo_h(ArvoreB * arvore, No_B * no_b) {
  int meio = no_b -> total / 2;
  No_B * novo = criaNo_b(arvore);
  novo -> pai = no_b -> pai;

  contador++;

  for (int i = meio + 1; i < no_b -> total; i++) {
    novo -> filhos[novo -> total] = no_b -> filhos[i];
    novo -> chaves[novo -> total] = no_b -> chaves[i];
    if (novo -> filhos[novo -> total] != NULL) novo -> filhos[novo -> total] -> pai = novo;

    novo -> total++;
  }

  novo -> filhos[novo -> total] = no_b -> filhos[no_b -> total];
  if (novo -> filhos[novo -> total] != NULL) novo -> filhos[novo -> total] -> pai = novo;
  no_b -> total = meio;
  return novo;
}

void adicionaChaveRecursivo_b(ArvoreB * arvore, No_B * no_b, No_B * novo, int chave) {
    
    monitoramento_B_02++;         // Monitoramento das execuções da função adicionaChaveRecursivo_b;
  contador++;

  adicionaChaveNo_b(no_b, novo, chave);

  if (transbordo_b(arvore, no_b)) {
    int promovido = no_b -> chaves[arvore -> ordem];
    No_B * novo = divideNo_h(arvore, no_b);

    if (no_b -> pai == NULL) {
      contador++;

      No_B * pai = criaNo_b(arvore);
      pai -> filhos[0] = no_b;
      adicionaChaveNo_b(pai, novo, promovido);

      no_b -> pai = pai;
      novo -> pai = pai;
      arvore -> raiz = pai;
    } else
      adicionaChaveRecursivo_b(arvore, no_b -> pai, novo, promovido);
  }
}

void adicionaChave_b(ArvoreB * arvore, int chave) {
  No_B * no_b = localizaNo_b(arvore, chave);

  adicionaChaveRecursivo_b(arvore, no_b, NULL, chave);
}
// Árvore B
//******************************

//**********************************
// Árvore Rubro Negra
enum coloracao {
  Vermelho,
  Preto
};
typedef enum coloracao Cor;

typedef struct no_rb {
  struct no_rb * pai;
  struct no_rb * esquerda;
  struct no_rb * direita;
  Cor cor;
  int valor;
}
No_Rb;

typedef struct arvore_rb {
  struct no_rb * raiz;
  struct no_rb * nulo;
}
Arvore_Rb;

No_Rb * criarNo_rb(Arvore_Rb * , No_Rb * , int);
void balancear_rb(Arvore_Rb * , No_Rb * );
void rotacionarEsquerda_rb(Arvore_Rb * , No_Rb * );
void rotacionarDireita_rb(Arvore_Rb * , No_Rb * );

Arvore_Rb * criar_rb();
int vazia_rb(Arvore_Rb * );
No_Rb * adicionar_rb(Arvore_Rb * , int);
No_Rb * localizar_rb(Arvore_Rb * arvore_rb, int valor);

Arvore_Rb * criar_rb() {
  Arvore_Rb * arvore_rb = malloc(sizeof(Arvore_Rb));
  arvore_rb -> nulo = NULL;
  arvore_rb -> raiz = NULL;

  arvore_rb -> nulo = criarNo_rb(arvore_rb, NULL, 0);
  arvore_rb -> nulo -> cor = Preto;

  return arvore_rb;
}

int vazia_rb(Arvore_Rb * arvore_rb) {
  return arvore_rb -> raiz == NULL;
}

No_Rb * criarNo_rb(Arvore_Rb * arvore_rb, No_Rb * pai, int valor) {
  No_Rb * no_rb = malloc(sizeof(No_Rb));

  no_rb -> pai = pai;
  no_rb -> valor = valor;
  no_rb -> direita = arvore_rb -> nulo;
  no_rb -> esquerda = arvore_rb -> nulo;

  return no_rb;
}

No_Rb * adicionarNo_rb(Arvore_Rb * arvore_rb, No_Rb * no_rb, int valor) {
    monitoramento_RB_01++;        // Monitoramento das execuções da função adicionarNo_rb;
  if (valor > no_rb -> valor) {
    if (no_rb -> direita == arvore_rb -> nulo) {
      no_rb -> direita = criarNo_rb(arvore_rb, no_rb, valor);
      no_rb -> direita -> cor = Vermelho;

      return no_rb -> direita;
    } else {
      return adicionarNo_rb(arvore_rb, no_rb -> direita, valor);
    }
  } else {
    if (no_rb -> esquerda == arvore_rb -> nulo) {
      no_rb -> esquerda = criarNo_rb(arvore_rb, no_rb, valor);
      no_rb -> esquerda -> cor = Vermelho;

      return no_rb -> esquerda;
    } else {
      return adicionarNo_rb(arvore_rb, no_rb -> esquerda, valor);
    }
  }
}

No_Rb * adicionar_rb(Arvore_Rb * arvore_rb, int valor) {
  if (vazia_rb(arvore_rb)) {
    monitoramento_RB_01++;      // Monitoramento das execuções da função adicionarNo_rb;
    arvore_rb -> raiz = criarNo_rb(arvore_rb, arvore_rb -> nulo, valor);
    arvore_rb -> raiz -> cor = Preto;

    return arvore_rb -> raiz;
  } else {
    No_Rb * no_rb = adicionarNo_rb(arvore_rb, arvore_rb -> raiz, valor);
    balancear_rb(arvore_rb, no_rb);

    return no_rb;
  }
}

No_Rb * localizar_rb(Arvore_Rb * arvore_rb, int valor) {
  if (!vazia_rb(arvore_rb)) {
    No_Rb * no_rb = arvore_rb -> raiz;

    while (no_rb != arvore_rb -> nulo) {
      if (no_rb -> valor == valor) {
        return no_rb;
      } else {
        no_rb = valor < no_rb -> valor ? no_rb -> esquerda : no_rb -> direita;
      }
    }
  }

  return NULL;
}

void percorrerProfundidadeInOrder_rb(Arvore_Rb * arvore_rb, No_Rb * no_rb, void( * callback)(int)) {
  if (no_rb != arvore_rb -> nulo) {

    percorrerProfundidadeInOrder_rb(arvore_rb, no_rb -> esquerda, callback);
    callback(no_rb -> valor);
    percorrerProfundidadeInOrder_rb(arvore_rb, no_rb -> direita, callback);
  }
}

void percorrerProfundidadePreOrder_rb(Arvore_Rb * arvore_rb, No_Rb * no_rb, void( * callback)(int)) {
  if (no_rb != arvore_rb -> nulo) {
    callback(no_rb -> valor);
    percorrerProfundidadePreOrder_rb(arvore_rb, no_rb -> esquerda, callback);
    percorrerProfundidadePreOrder_rb(arvore_rb, no_rb -> direita, callback);
  }
}

void percorrerProfundidadePosOrder_rb(Arvore_Rb * arvore_rb, No_Rb * no_rb, void(callback)(int)) {
  if (no_rb != arvore_rb -> nulo) {
    percorrerProfundidadePosOrder_rb(arvore_rb, no_rb -> esquerda, callback);
    percorrerProfundidadePosOrder_rb(arvore_rb, no_rb -> direita, callback);
    callback(no_rb -> valor);
  }
}

void visitar_rb(int valor) {
  printf("%d ", valor);
}

void balancear_rb(Arvore_Rb * arvore_rb, No_Rb * no_rb) {
    monitoramento_RB_02++;        // Monitoramento das execuções da função balancear_rb;
  while (no_rb -> pai -> cor == Vermelho) {
    if (no_rb -> pai == no_rb -> pai -> pai -> esquerda) {
      No_Rb * tio = no_rb -> pai -> pai -> direita;

      if (tio -> cor == Vermelho) {
        tio -> cor = Preto; //Caso 1
        no_rb -> pai -> cor = Preto;

        no_rb -> pai -> pai -> cor = Vermelho; //Caso 1
        no_rb = no_rb -> pai -> pai; //Caso 1
      } else {
        if (no_rb == no_rb -> pai -> direita) {
          no_rb = no_rb -> pai; //Caso 2
          rotacionarEsquerda_rb(arvore_rb, no_rb); //Caso 2
        } else {
          no_rb -> pai -> cor = Preto;
          no_rb -> pai -> pai -> cor = Vermelho; //Caso 3
          rotacionarDireita_rb(arvore_rb, no_rb -> pai -> pai); //Caso 3
        }
      }
    } else {
      No_Rb * tio = no_rb -> pai -> pai -> esquerda;

      if (tio -> cor == Vermelho) {
        tio -> cor = Preto; //Caso 1
        no_rb -> pai -> cor = Preto;

        no_rb -> pai -> pai -> cor = Vermelho; //Caso 1
        no_rb = no_rb -> pai -> pai; //Caso 1
      } else {
        if (no_rb == no_rb -> pai -> esquerda) {
          no_rb = no_rb -> pai; //Caso 2
          rotacionarDireita_rb(arvore_rb, no_rb); //Caso 2
        } else {
          no_rb -> pai -> cor = Preto;
          no_rb -> pai -> pai -> cor = Vermelho; //Caso 3
          rotacionarEsquerda_rb(arvore_rb, no_rb -> pai -> pai); //Caso 3
        }
      }
    }
  }
  arvore_rb -> raiz -> cor = Preto; //Conserta possível quebra regra 2
}

void rotacionarEsquerda_rb(Arvore_Rb * arvore_rb, No_Rb * no_rb) {
  No_Rb * direita = no_rb -> direita;
  no_rb -> direita = direita -> esquerda;

  if (direita -> esquerda != arvore_rb -> nulo) {
    direita -> esquerda -> pai = no_rb;
  }

  direita -> pai = no_rb -> pai;

  if (no_rb -> pai == arvore_rb -> nulo) {
    arvore_rb -> raiz = direita;
  } else if (no_rb == no_rb -> pai -> esquerda) {
    no_rb -> pai -> esquerda = direita;
  } else {
    no_rb -> pai -> direita = direita;
  }

  direita -> esquerda = no_rb;
  no_rb -> pai = direita;
}

void rotacionarDireita_rb(Arvore_Rb * arvore_rb, No_Rb * no_rb) {
  No_Rb * esquerda = no_rb -> esquerda;
  no_rb -> esquerda = esquerda -> direita;

  if (esquerda -> direita != arvore_rb -> nulo) {
    esquerda -> direita -> pai = no_rb;
  }

  esquerda -> pai = no_rb -> pai;

  if (no_rb -> pai == arvore_rb -> nulo) {
    arvore_rb -> raiz = esquerda;
  } else if (no_rb == no_rb -> pai -> esquerda) {
    no_rb -> pai -> esquerda = esquerda;
  } else {
    no_rb -> pai -> direita = esquerda;
  }

  esquerda -> direita = no_rb;
  no_rb -> pai = esquerda;
}
// Árvore Rubro Negra
//********************************

//*************************************

void test_avl_tree() {
    Arvore_Avl* a = criar_avl();

    adicionar_Avl(a, 2);
    adicionar_Avl(a, 8);
    adicionar_Avl(a, 1);
    adicionar_Avl(a, 3);
    adicionar_Avl(a, 6);
    adicionar_Avl(a, 9);
    adicionar_Avl(a, 5);

    printf("In-order:\n");
    percorrerProfundidadeInOrder_avl(a->raiz,visitar_avl);
    printf("\n");
}

void test_b_tree() {
  ArvoreB * arvore = criaArvore_b(1);

  contador = 0;

  adicionaChave_b(arvore, 12);
  adicionaChave_b(arvore, 3);
  adicionaChave_b(arvore, 5);
  adicionaChave_b(arvore, 7);
  adicionaChave_b(arvore, 15);
  adicionaChave_b(arvore, 99);
  adicionaChave_b(arvore, 1);

  percorreArvore_b(arvore -> raiz);

  printf("\nNúmero de operações: %d\n", contador);

}

void test_rb_tree() {
    Arvore_Rb* a = criar_rb();

    adicionar_rb(a,7);
    adicionar_rb(a,6);
    adicionar_rb(a,5);
    adicionar_rb(a,4);
    adicionar_rb(a,3);
    adicionar_rb(a,2);
    adicionar_rb(a,1);

    printf("In-order:\n");
    percorrerProfundidadeInOrder_rb(a, a->raiz,visitar_rb);
    printf("\n\n");
}

void monitoramento() {
    printf("Iteracoes da função balanceamento_avl: %d\n",         monitoramento_Avl_01);
    printf("Iteracoes da função adicionarNo_Avl: %d\n",           monitoramento_Avl_02);
    printf("Iteracoes da função percorreArvore_b: %d\n",          monitoramento_B_01);
    printf("Iteracoes da função adicionaChaveRecursivo_b: %d\n",  monitoramento_B_02);
    printf("Iteracoes da função adicionarNo_rb: %d\n",            monitoramento_RB_01);
    printf("Iteracoes da função balancear_rb: %d\n",              monitoramento_RB_02); 
}

//********************************

    // media1 -> Complexidade da árvore AVL para o Caso Médio
    // media2 -> Complexidade da árvore B para o Caso Médio
    // media3 -> Complexidade da árvore Rubro-negra para o Caso Médio
    // media4 -> Complexidade da árvore Rubro-negra para o Pior Caso

//********************************

void media1() {
    srand(time(NULL));                              // seed para a geração dos números aleatórios;

    int *conjunto, *media1;
    int i, j, k, igual, tam;

    media1 = malloc(TAM * sizeof(int));             // vetor de respostas, conforme o número de conjuntos

    
    for( i=0; i<TAM; i++ ){                         // inicializando media1          
        *(media1 + i) = 0; 
    }
    
    for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o número de conjuntos a serem criados
            conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos
            

            for( i=0; i<tam; i++ ){                 // a partir deste FOR criamos as chaves
                *(conjunto + i) = rand()%100;           // aritmética de ponteiros.

                igual = 0;                         
                for( j = 0; j < i; j++ ){           // este FOR garante que nenhuma chave se repetirá
                    if( conjunto[j] == conjunto[i] )
                        igual = 1;
                }

                if (igual == 1)
                    i--;            
            }
            
            Arvore_Avl* a = criar_avl();
            //printf("\n Conjunto %d: \n", tam);
            for(i = 0; i < tam; i++){
                //printf("%d ", *(conjunto + i));   // imprime o conteúdo desta região de memória
                adicionar_Avl(a, *(conjunto + i));  // adicionando todos as chaves do conjunto na árvore criada
            }

            *( media1 + tam - 1 ) = *( media1 + tam - 1 ) + monitoramento_Avl_01 + monitoramento_Avl_02;

            /*                                      // teste AVL
            printf("\n");
            printf("In-order:\n");
            percorrerProfundidadeInOrder_avl(a->raiz,visitar_avl);
            printf("\n Complexidade Total AVL:  %d  \n", monitoramento_Avl_01+monitoramento_Avl_02);
            */

            /*
            printf("\nTestando media1: %d\n", *( media1 + tam - 1 ));
            for(i = 0; i < tam; i++){
                printf("%d ", *(media1 + i)); //imprime o conteúdo desta região de memória
            }
            */

            monitoramento_Avl_01 = 0;
            monitoramento_Avl_02 = 0;

            free (conjunto);              // desalocando a memória        
        }

    printf("\n Complexidade Total AVL: \n");
    for(i = 0; i < TAM; i++){
        printf("%d ", *(media1 + i));            // imprime a média do conteúdo desta região de memória
    }
    free (media1);                       // desalocando a memória
    printf("\n");  
}

void media2() {
    srand(time(NULL));                              // seed para a geração dos números aleatórios;

    int *conjunto, *media2;
    int i, j, k, igual, tam;

    media2 = malloc(TAM * sizeof(int));             // vetor de respostas, conforme o número de conjuntos

    
    for( i=0; i<TAM; i++ ){                         // inicializando media2          
        *(media2 + i) = 0; 
    }
    
    for( k=0; k<10; k++ ){                          // Looping para Validação estatística
        for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o número de conjuntos a serem criados
            conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos
            

            for( i=0; i<tam; i++ ){                 // a partir deste FOR criamos as chaves
                *(conjunto + i) = rand();           // aritmética de ponteiros.

                igual = 0;                         
                for( j = 0; j < i; j++ ){           // este FOR garante que nenhuma chave se repetirá
                    if( conjunto[j] == conjunto[i] )
                        igual = 1;
                }

                if (igual == 1)
                    i--;            
            }
            
            ArvoreB* a = criaArvore_b(1);           // Quanto maior a ordem da árvore, menos nós são criados!
            for(i = 0; i < tam; i++){
                adicionaChave_b(a, *(conjunto + i));// adicionando todos as chaves do conjunto na árvore criada
            }

            *( media2 + tam - 1 ) = *( media2 + tam - 1 ) + monitoramento_B_01 + monitoramento_B_02;

            monitoramento_B_01 = 0;
            monitoramento_B_02 = 0;

            free (conjunto);              // desalocando a memória        
        }
    }

    printf("\n Complexidade Total B: \n");
    for(i = 0; i < TAM; i++){
        printf("%d ", *(media2 + i)/10);            // imprime a média do conteúdo desta região de memória
    }
    free (media2);                       // desalocando a memória
    printf("\n");  
}

void media3() {
    srand(time(NULL));                              // seed para a geração dos números aleatórios;

    int *conjunto, *media3;
    int i, j, k, igual, tam;

    media3 = malloc(TAM * sizeof(int));             // vetor de respostas, conforme o número de conjuntos

    
    for( i=0; i<TAM; i++ ){                         // inicializando media3          
        *(media3 + i) = 0; 
    }
    
    for( k=0; k<10; k++ ){                          // Looping para Validação estatística
        for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o número de conjuntos a serem criados
            conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos
            

            for( i=0; i<tam; i++ ){                 // a partir deste FOR criamos as chaves
                *(conjunto + i) = rand();      // aritmética de ponteiros.

                igual = 0;                         
                for( j = 0; j < i; j++ ){           // este FOR garante que nenhuma chave se repetirá
                    if( conjunto[j] == conjunto[i] )
                        igual = 1;
                }

                if (igual == 1)
                    i--;            
            }
            
            Arvore_Rb* a = criar_rb();          
            for(i = 0; i < tam; i++){
                adicionar_rb(a, *(conjunto + i));// adicionando todos as chaves do conjunto na árvore criada
            }

            *( media3 + tam - 1 ) = *( media3 + tam - 1 ) + monitoramento_RB_01 + monitoramento_RB_02;

            monitoramento_RB_01 = 0;
            monitoramento_RB_02 = 0;

            free (conjunto);              // desalocando a memória  
        }
    }

    printf("\n Complexidade Total Rubro-negra: \n");
    for(i = 0; i < TAM; i++){
        printf("%d ", *(media3 + i)/10);            // imprime a média do conteúdo desta região de memória
    }
    free (media3);                       // desalocando a memória
    printf("\n");  
}

void media4() {

    int *conjunto, *media4;
    int i, j, k, igual, valor, tam;

    media4 = malloc(TAM * sizeof(int));             // vetor de respostas, conforme o número de conjuntos

    
    for( i=0; i<TAM; i++ ){                         // inicializando media4          
        *(media4 + i) = 0; 
    }
    
    for( k=0; k<10; k++ ){                          // Looping para Validação estatística
        for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o número de conjuntos a serem criados
            conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos

            valor = tam;
            for( i=0; i<tam; i++ ){
            *(conjunto + i) = valor;            // aritmética de ponteiros
            valor--;                      
        }
            
        Arvore_Avl* a = criar_avl();
        for(i = 0; i < tam; i++){
            adicionar_Avl(a, *(conjunto + i));  // adicionando todos as chaves do conjunto na árvore criada
        }

        *( media4 + tam - 1 ) = *( media4 + tam - 1 ) + monitoramento_Avl_01 + monitoramento_Avl_02;

        monitoramento_Avl_01 = 0;
        monitoramento_Avl_02 = 0;

        free (conjunto);              // desalocando a memória    
        }
    }

    printf("\n Complexidade Total AVL: \n");
    for(i = 0; i < TAM; i++){
        printf("%d ", *(media4 + i)/10);    // imprime a média do conteúdo desta região de memória
    }
    free (media4);                          // desalocando a memória
    printf("\n");  
}

void media5() {

    int *conjunto, *media5;
    int i, j, k, igual, valor, tam;

    media5 = malloc(TAM * sizeof(int));             // vetor de respostas, conforme o número de conjuntos

    
    for( i=0; i<TAM; i++ ){                         // inicializando media5          
        *(media5 + i) = 0; 
    }
    
    for( k=0; k<10; k++ ){                          // Looping para Validação estatística
        for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o número de conjuntos a serem criados
            conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos

            valor = tam;
            for( i=0; i<tam; i++ ){
            *(conjunto + i) = valor;            // aritmética de ponteiros
            valor--;                      
        }
            
        ArvoreB* a = criaArvore_b(1);           // Quanto maior a ordem da árvore, menos nós são criados!
            for(i = 0; i < tam; i++){
                adicionaChave_b(a, *(conjunto + i));// adicionando todos as chaves do conjunto na árvore criada
            }

            *( media5 + tam - 1 ) = *( media5 + tam - 1 ) + monitoramento_B_01 + monitoramento_B_02;

            monitoramento_B_01 = 0;
            monitoramento_B_02 = 0;

            free (conjunto);              // desalocando a memória  
        }
    }

    printf("\n Complexidade Total B: \n");
    for(i = 0; i < TAM; i++){
        printf("%d ", *(media5 + i)/10);    // imprime a média do conteúdo desta região de memória
    }
    free (media5);                          // desalocando a memória
    printf("\n");  
}

void media6() {

    int *conjunto, *media6;
    int i, j, k, igual, valor, tam;

    media6 = malloc(TAM * sizeof(int));             // vetor de respostas, conforme o número de conjuntos

    
    for( i=0; i<TAM; i++ ){                         // inicializando media6          
        *(media6 + i) = 0; 
    }
    
    for( k=0; k<10; k++ ){                          // Looping para Validação estatística
        for( tam = 1; tam <= TAM; tam++ ){          // neste FOR definimos o número de conjuntos a serem criados
            conjunto = malloc(tam * sizeof(int));   // alocação de memória para o vetor, conforme o número de elementos

            valor = tam;
            for( i=0; i<tam; i++ ){
            *(conjunto + i) = valor;            // aritmética de ponteiros
            valor--;                      
        }
            
        Arvore_Rb* a = criar_rb();          
            for(i = 0; i < tam; i++){
                adicionar_rb(a, *(conjunto + i));// adicionando todos as chaves do conjunto na árvore criada
            }

            *( media6 + tam - 1 ) = *( media6 + tam - 1 ) + monitoramento_RB_01 + monitoramento_RB_02;

            monitoramento_RB_01 = 0;
            monitoramento_RB_02 = 0;

            free (conjunto);              // desalocando a memória   
        }
    }

    printf("\n Complexidade Total Rubro-negra: \n");
    for(i = 0; i < TAM; i++){
        printf("%d ", *(media6 + i)/10);    // imprime a média do conteúdo desta região de memória
    }
    free (media6);                          // desalocando a memória
    printf("\n");  
}

int main() {
    printf("\n CASO MEDIO - CONJUNTOS DE CHAVES ALEATORIAS:\n");
    media1();
    media2();
    media3();
    
    printf("\n PIOR CASO - CONJUNTOS DE CHAVES EM ORDEM DECRESCENTE:\n");
    media4();
    media5();
    media6();

    return 0;
}

// Main
// ****************************

  /*printf("\nÁrvore AVL\n");
  test_avl_tree();
  printf("\n\nÁrvore B\n");
  test_b_tree();
  printf("\n\nÁrvore Rubro Negra\n");
  test_rb_tree();
  monitoramento();
  */
