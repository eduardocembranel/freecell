#include "jogadas.h"
#include "ui.h"

//processa os movimento inserido pelo jogados na linha de comando
//Entrada: string contendo a jogada, vetor de pilhas e vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas e vetor de cartas inicializado
//Pos-condicao: jogada efetuada caso possivel
void processMovement (char *jogada, Pilha *pilhas[], Carta freeCell[])
{
  int nOrigem, nDestino, qntCartas;
  char tOrigem, tDestino;
  Carta aux;

  if (strcmp(jogada, "h") == 0)
  {
    showHelp();
    pressAnyKey();
  }

  //comando para imprimir o conteudo de uma pilha. Ex: P1, B8...
  else if (strlen(jogada) == 2 && isValid0(jogada))
  {
    nOrigem = jogada[1] - '0';

    if (jogada[0] == 'P')
      printPilha(pilhas, nOrigem - 1);
    else if (jogada[0] == 'B')
      printPilha(pilhas, nOrigem + 7);
  }

  //comando para mover uma unica carta. Ex: P1P2
  else if (strlen(jogada) == 4 && isValid(jogada))
  {
    nOrigem = jogada[1] - '0';
    nDestino = jogada[3] - '0';

    if (jogada[0] == 'P' && jogada[2] == 'F')
      pilhaToFreeCell(pilhas, freeCell, nOrigem - 1, nDestino - 1);
    else if (jogada[0] == 'P' && jogada[2] == 'B')
      pilhaToBase(pilhas, nOrigem - 1, nDestino + 7);
    else if (jogada[0] == 'P' && jogada[2] == 'P')
      pilhaToPilha(pilhas, nOrigem - 1, nDestino-1);
    else if (jogada[0] == 'F' && jogada[2] == 'F')
      freeCellToFreeCell(freeCell, nOrigem - 1, nDestino - 1);
    else if (jogada[0] == 'F' && jogada[2] == 'B')
      freeCellToBase(freeCell, pilhas, nOrigem - 1, nDestino + 7);
    else if (jogada[0] == 'F' && jogada[2] == 'P')
      freeCellToPilha(freeCell, pilhas, nOrigem - 1, nDestino - 1);
  }

  //comando para mover multiplas cartas. EX: P1(2)P2
  else if (strlen(jogada) == 7 && isValid2(jogada))
  {
    nOrigem = jogada[1] - '0';
    nDestino = jogada[6] - '0';
    qntCartas = jogada[3] - '0';
  
    if (isPossible(pilhas, freeCell, nOrigem - 1, nDestino - 1, qntCartas))
      mPilhaToPilha (pilhas, nOrigem - 1, nDestino - 1, qntCartas);
  }

  //comando p/ mover multiplas cartas e quantidade de cartas é > 9. Ex: P1(15)P2
  else if (strlen(jogada) == 8 && isValid3(jogada))
  {
    nOrigem = jogada[1] - '0';
    nDestino = jogada[7] - '0';
    qntCartas = (jogada[3] - '0') * 10 + (jogada[4] - '0'); 
    
    if (isPossible(pilhas, freeCell, nOrigem - 1, nDestino - 1, qntCartas))
      mPilhaToPilha (pilhas, nOrigem - 1, nDestino - 1, qntCartas);
  }
}

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid0 (char *jogada)
{
  if (jogada[1] < '1' || jogada[1] > '8' || (jogada[0] == 'B' && jogada[1] > '4'))
    return 0;

  return 1;
}

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid (char *jogada)
{
  if (jogada[1] < '1' || jogada[3] < '1' || jogada[1] > '8' || jogada[3] > '8')
    return 0;
  if ((jogada[0] == 'F' && jogada[1] > '4') || 
   ((jogada[2] == 'F' || jogada[2] == 'B') && jogada[3] > '4'))
    return 0;

  return 1;
}

//move uma carta de uma pilha para uma cedula livre se possivel
//Entrada: vetor de pilhas, vetor de cartas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void pilhaToFreeCell (Pilha *pilhas[], Carta freeCell[], int origem, int destino)
{
  if (!isEmpty(pilhas, origem) && freeCell[destino].valor == 0)
  {
    Carta aux = pop(pilhas, origem);
    freeCell[destino] = aux;
  }
}

//move uma carta de uma pilha para uma das pilhas da fundacao (base)
//Entrada: vetor de pilhas, vetor de cartas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void pilhaToBase (Pilha *pilhas[], int origem, int destino)
{
  if (!isEmpty(pilhas, origem))
  {
    if (isEmpty(pilhas, destino) && pilhas[origem]->topo->carta.valor == 1)
    {
      Carta aux = pop(pilhas, origem);
      push(pilhas, destino, aux);   
    }
    else if (!isEmpty(pilhas, destino))
    {
      if (pilhas[origem]->topo->carta.naipe == pilhas[destino]->topo->carta.naipe)
        if (isNext(pilhas[origem]->topo->carta, pilhas[destino]->topo->carta))
        {
          Carta aux = pop(pilhas, origem);
          push(pilhas, destino, aux);
        }
    }
  }
}

//checa se o valor da primeira carta é exatamente 1 maior que a segunda
//Entrada: 2 cartas
//Retorno: 1 caso a primeira carta seja exatamente 1 valor maior que a segunda
//Pre-condicao: cartas nao vazias
//Pos-condicao: nenhuma
int isNext (Carta carta1, Carta carta2)
{
  if ((carta2.valor + 1) == carta1.valor)
    return 1;

  return 0;
}

//move uma carta de uma pilha inferiores para outra pilha inferior
//Entrada: vetor de pilhas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void pilhaToPilha (Pilha *pilhas[], int origem, int destino)
{ 
  if (!isEmpty(pilhas, origem) && (isEmpty(pilhas, destino) || 
    (!isSameColor(pilhas[origem]->topo->carta, pilhas[destino]->topo->carta)
    && isNext(pilhas[destino]->topo->carta, pilhas[origem]->topo->carta))))
    {
      Carta aux = pop(pilhas, origem);
      push(pilhas, destino, aux);
    }
}

//checa se a car das duas cartas é a mesma
//Entrada: 2 cartas
//Retorno: 1 caso as cores forem iguais, 0 caso contrario
//Pre-condicao: cartas nao vazias
//Pos-condicao: nenhuma
int isSameColor (Carta carta1, Carta carta2)
{
  if (carta1.cor == carta2.cor)
    return 1;
  return 0;
}

//move uma carta de uma cedula livre para outra cedula livre se possivel
//Entrada: vetor de cartas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: vetor de cartas inicializado
//Pos-condicao: carta movida se possivel
void freeCellToFreeCell (Carta freeCell[], int origem, int destino)
{
  if (freeCell[origem].valor != 0 && freeCell[destino].valor == 0)
  {
    Carta aux = freeCell[origem];
    toZero(freeCell, origem);
    freeCell[destino] = aux;
  } 
}

//move uma carta de uma cedula livre para uma das pilhas base se possivel
//Entrada: vetor de cartas, vetor de pilhas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void freeCellToBase (Carta freeCell[], Pilha *pilhas[], int origem, int destino)
{
  if (freeCell[origem].valor != 0 &&  (isEmpty(pilhas, destino) && 
    freeCell[origem].valor == 1) || (!isEmpty(pilhas, destino)  &&
    freeCell[origem].naipe == pilhas[destino]->topo->carta.naipe  &&
    isNext(freeCell[origem], pilhas[destino]->topo->carta)))
    {
      Carta aux = freeCell[origem];
      toZero(freeCell, origem);
      push(pilhas, destino, aux);
    }
}

//move uma carta de uma cedula livre para uma das pilhas inferiores, se possivel
//Entrada: vetor de cartas, vetor de pilhas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void freeCellToPilha (Carta freeCell[], Pilha *pilhas[], int origem, int destino)
{
  if (freeCell[origem].valor != 0 && (isEmpty(pilhas, destino)) || 
    (!isSameColor(freeCell[origem], pilhas[destino]->topo->carta) &&
    isNext(pilhas[destino]->topo->carta, freeCell[origem])))
    {    
      Carta aux = freeCell[origem];
      toZero(freeCell, origem);
      push(pilhas, destino, aux);
    }
}

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid2 (char *jogada)
{
  if (jogada[2] != '(' || jogada[4] != ')' || jogada[0] != 'P' ||
    jogada[5] != 'P'   || jogada[1] > '8'  || jogada[1] < '1'  ||
    jogada[6] > '8'    || jogada[6] < '1'  || jogada[3] < '2'  ||
    jogada[1] == jogada[6])
      return 0;

  return 1;
}

//checa se é possivel mover multiplas cartas de uma determinada pilha para outra 
//Entrada: vetor de pilhas, vetor de cartas, 3 inteiros (origem, destino e
// quantidade de cartas a serem movidas)
//Retorno: 1 caso seja possivel, 0 caso contrario
//Pre-condicao: vetor de pilhas e de cartas inicializados
//Pos-condicao: nenhuma
int isPossible (Pilha *pilhas[], Carta freeCell[], int orig, int dest, int qntC)
{
  int cntFree = 0, cntVazia = 0, cnt, j;
  
  //Checa se é possivel mover essa quantidade de cartas
  //segundo a equacao: qnt = (1 + celulas_livres) x 2^(pilhas_vazias)
  ////////////////////////////////////////////////////////////////
  for (j = 0; j < NUMFREE; ++j)
    if (freeCell[j].valor == 0)
      ++cntFree;

  for (j = 0; j < 8; ++j)
    if (isEmpty(pilhas, j))
      ++cntVazia;

  cnt = (cntFree + 1) * pow(2, cntVazia);
  if (qntC > cnt) 
    return 0;
  ////////////////////////////////////////////////////////////////

  No *i = pilhas[orig]->topo;
  Carta ultima;

  //se todas as cartas que deseja mover estao em cores alternadas
  //e em ordem decrescente, procede.
  for (cnt = 1; i && i->prox && cnt < qntC; i = i->prox, ++cnt)
  { 
    if (!isNext(i->prox->carta, i->carta) || i->carta.cor == i->prox->carta.cor)
      return 0;
    ultima = i->prox->carta;
  }
 
  if (cnt == qntC && cnt > 1)
    if (isEmpty(pilhas, dest) || isNext(pilhas[dest]->topo->carta, ultima) 
     && ultima.cor != pilhas[dest]->topo->carta.cor)
       return 1;
  return 0;
}

//move 2 ou mais carta de uma pilha para outra pilha inferior
//Entrada: vetor de pilhas, 3 inteiros (origem, destido e quantidade de cartas) 
//Retorno: nenhum
//Pre-condicao: vetor de pilhas inicializado
//Pos-condicao: cartas movidas
void mPilhaToPilha (Pilha *pilhas[], int origem, int destino, int qntCartas)
{
  Pilha *aux = malloc(sizeof(Pilha));
  aux->topo = NULL;
  Carta carta;

  int i = 0;
  for (i = 0; i < qntCartas ; ++i)
  {
    carta = pop(pilhas, origem);
    push1(aux, carta);
  }
  for (i = 0; i < qntCartas; ++i)
  {
    carta = pop1(aux);
    push(pilhas, destino, carta);
  }
  free(aux);
}

//insere uma carta na pilha
//Entrada: pilha e carta a ser inserida
//Retorno: nenhum
//Pre-condicao: pilha inicializada
//Pos-condicao: carta inserida na pilha
void push1 (Pilha *pilha, Carta carta)
{
  No *novo = malloc(sizeof(No));

  novo->carta.naipe = carta.naipe;
  novo->carta.valor = carta.valor;
  novo->carta.cor = carta.cor;
  novo->prox = pilha->topo;
  pilha->topo = novo;
}

//remove uma carta da pilha
//Entrada: pilha
//Retorno: carta removida
//Pre-condicao: pilha inicializada
//Pos-condicao: carta removida da pilha caso nao for vazia
Carta pop1 (Pilha *pilha)
{
  if (pilha->topo)
  {
    No *aux = pilha->topo->prox;
    Carta topo = pilha->topo->carta;
    free(pilha->topo);
    pilha->topo = aux;
    return topo;
  } 
}

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid3 (char *jogada)
{
  if (jogada[2] != '(' || jogada[5] != ')' || jogada[0] != 'P' ||
    jogada[6] != 'P'   || jogada[1] > '8'  || jogada[1] < '1'  ||
    jogada[7] > '8'    || jogada[7] < '1'  || jogada[3] < '1'  ||
    jogada[3] > '5'    || jogada[4] < '0'  || jogada[4] > '9'  ||
    jogada[1] == jogada[7])
      return 0;

  return 1; 
}