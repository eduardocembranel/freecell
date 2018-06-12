#include "ui.h"
#include "jogadas.h"

//Roda o jogo partindo do menu e distribuindo as opcoes selecionadas
//Entrada: argumentos passados pela linha de comando pelo usuario
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
void run (MainArguments argumentos)
{
  int escolha = 0;
  while (escolha != 3)
  {
    escolha = menu();
    setOption(escolha, argumentos);

    //se o usuario ja jogou uma vez, entao se for jogar novamente
    //nao havera load game, mesmo q tenha solicitado anteriormente
    if (escolha == 1) argumentos.argc = 1;
  }
}

//Roda o menu do jogo e aguarda por uma escolha do usuario
//Entrada: nenhuma
//Retorno: inteiro (1-3) representando a escolha do usuario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int menu (void)
{
  int escolha = 0;
  
  while (escolha > 3 || escolha < 1)
  {
    setLogo();
    scanf ("%d", &escolha);
    flushInput();
  }
  return escolha;  
}

//Limpa o buffer de entrada, caso estiver vazio aguarda por \n (enter)
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: buffer de entrada vazio
void flushInput (void)
{
  int x;
  while ((x = getchar()) != '\n' && x != EOF);
}

//Distribui a escolha feita pelo jogador, anteriormente, no menu
//Entrada: argumentos da linha de comando e a escolha do jogador
//Retorno: nenhum
//Pre-condicao: escolha deve ser 1 (jogar) ou 2 (instrucoes)
//Pos-condicao: incia o jogo ou exibe as intrucoes
void setOption (int escolha, MainArguments argumentos)
{
  if (escolha == 1)
    play(argumentos);
  else if (escolha == 2)
    showInstructions();
}

//inicializa o jogo, aguarda por jogadas e processa os comandos do usuario
//Entrada: argumentos passados pela linha de comando pelo usuario
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
void play (MainArguments argumentos)
{
  Pilha *pilhas[NUMPILHAS];
  Carta freeCell[NUMFREE];
  char jogada[JOGADASIZE] = "\0";
  
  startGame(pilhas, freeCell, argumentos);

  while (!isEndGame(pilhas) && strcmp(jogada, "q") != 0) 
  {
    fgets(jogada, JOGADASIZE, stdin); removeNewLine(jogada);
    processMovement(jogada, pilhas, freeCell);
    show(pilhas, freeCell);
  }
  
  if (isEndGame(pilhas))
    endGame();
  else
    saveGame(pilhas, freeCell);
  
  destroy(pilhas);
}

//inicializa as pilhas e as cedulas livres e carrega/embaralha as cartas
//Entrada: vetor de pilhas de cartas, vetor de cartas e argumentos do main
//Retorno: nenhum
//Pre-condicao: vetor de pilhas com 12 pilhas e vetor de cartas de 4 cartas
//Pos-condicao: cartas distribuidas nas pilhas e exibe o jogo na tela 
void startGame (Pilha *pilhas[], Carta freeCell[], MainArguments argumentos)
{  
  if (argumentos.argc < 2 || !loadGame(argumentos.argv[1], pilhas, freeCell))
  {
    criaPilhas(pilhas);
    embaralha(pilhas);
    criaFreeCells(freeCell);
  }
  show(pilhas, freeCell);
}

//carrega os dados do jogo para as pilhas e cedulas livres, caso arquivo exista
//Entrada: nome do arquivo, vetor de pilhas e vetor de cartas
//Retorno: 0 caso o carregamento obteve fracasso, 1 caso contrario
//Pre-condicao: vetor de pilha deve conter 12 pilhas e vetor de cartas, 4 cartas
//Pos-condicao: pilhas inicializadas com jogo carregado caso obteve sucesso
int loadGame (char *fName, Pilha *pilhas[], Carta freeCell[])
{
  FILE *fr = fopen(fName, "rb");
  if (!fr) return 0;

  Pilha *inversa[NUMPILHAS];
  criaPilhas(inversa);
  Carta aux;

  int i = 0;
  for (i = 0; i < NUMPILHAS; ++i)
    while (fread(&aux, sizeof(Carta), 1, fr) && aux.valor != FIM) 
        push(inversa, i, aux);  
  
  fread(freeCell, sizeof(Carta), NUMFREE, fr);
  
  getInversa(pilhas, inversa);
  destroy(inversa);
  
  fclose(fr);
  return 1;
}

//as 12 pilhas do jogo sao criadas (alocadas na memoria) com valor inicial nulo
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas deve conter 12 pilhas
//Pos-condicao: pilhas inicializadas, vazias, com espaco na memoria
void criaPilhas (Pilha *pilhas[])
{
  int i;
  for (i = 0; i < NUMPILHAS; ++i)
  {
    pilhas[i] = malloc(sizeof(Pilha));
    pilhas[i]->topo = NULL;
  }
}

//insere uma carta na pilha indicada
//Entrada: vetor de pilhas, inteiro (posicao da pilha) e a carta a ser inserida 
//Retorno: nenhum
//Pre-condicao: pilhas inicializadas
//Pos-condicao: carta inserida na pilha
void push (Pilha *pilhas[], int N, Carta carta)
{
  No *novo = malloc(sizeof(No));

  novo->carta.naipe = carta.naipe;
  novo->carta.valor = carta.valor;
  novo->carta.cor = carta.cor;
  novo->prox = pilhas[N]->topo;
  pilhas[N]->topo = novo;
}

//obtem-se a configuracao inversa de um vetor de 12 pilhas
//Entrada: vetor de pilhas nulo e vetor de pilhas original
//Retorno: nenhum
//Pre-condicao: vetor original inicializado 
//Pos-condicao: vetor de 12 pilhas invertido p/ outra pilha (original n altera)
void getInversa (Pilha *inversa[], Pilha *pilhas[])
{
  criaPilhas(inversa);
  
  int i; No *j;
  for (i = 0; i < NUMPILHAS; ++i)
    for (j = pilhas[i]->topo; j; j = j->prox)
      push(inversa, i, j->carta);
}

//libera a memoria alocada do vetor de pilhas
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de 12 pilhas com memoria alocada dinamicamente
//Pos-condicao: elementos removidos e memoria liberada das 12 pilhas
void destroy (Pilha *pilhas[])
{
  int i;
  for (i = 0; i < NUMPILHAS; ++i)
  {
    while (!isEmpty(pilhas, i))
      pop(pilhas, i);
    free(pilhas[i]);
  }
}

//checa se uma pilha e vazia
//Entrada: vetor de pilhas e posicao da pilha a ser checada
//Retorno: 1 se a pilha for vazia, 0 caso contrario
//Pre-condicao: vetor de pilhas inicializado
//Pos-condicao: nenhuma
int isEmpty (Pilha *pilhas[], int n)
{
  if (pilhas[n]->topo == NULL)
    return 1;
    
  return 0;
}

//remove uma carta da pilha
//Entrada: vetor de pilhas e posicao da pilha
//Retorno: carta removida
//Pre-condicao: vetor de pilha inicializado
//Pos-condicao: carta removida da pilha caso nao for vazia
Carta pop (Pilha *pilhas[], int n)
{
  if (!isEmpty(pilhas, n))
  {
    No *aux = pilhas[n]->topo->prox;
    Carta topo = pilhas[n]->topo->carta;
    free(pilhas[n]->topo);
    pilhas[n]->topo = aux;
    return topo;
  }
}

//faz o embaralhamento das 52 cartas e distribui elas para as pilhas
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas inicializado
//Pos-condicao: nenhuma
void embaralha (Pilha *pilhas[])
{
  int i, aux[NUMCARDS];
  
  for (i = 0; i < NUMCARDS; ++i)
    aux[i] = i;
  for (i = 0; i < NUMCARDS; ++i)
  {
    int rnd = rand() % NUMCARDS;
    int tmp = aux[i];
    aux[i] = aux[rnd];
    aux[rnd] = tmp;
  }
  for (i = 0; i < NUMCARDS; ++i)
    push(pilhas, i % 8, getCarta(aux[i]));
}

//Obtem-se uma das 52 cartas do baralho
//Entrada: um inteiro
//Retorno: uma das 52 cartas do baralho
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
Carta getCarta (int x)
{
  Carta carta;

  carta.naipe = getNaipe(x);
  carta.cor = getCor(x);
  carta.valor = getValor(x);

  return carta;
}

//Obtem-se uma das 4 naipes existes
//Entrada: um inteiro
//Retorno: caracter com a naipe obtida
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
char getNaipe (int x)
{
  char *naipe = "CPOE";

  return naipe[x %= 4];
}

//Obtem-se uma das 2 cores de carta (vermelha ou preta)
//Entrada: um inteiro
//Retorno: 0 para a cor vermelha, 1 para a cor preta
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
int getCor (int x)
{
  int cor[2] = {0, 1};
  
  return cor[x %= 2];
}

//Obtem-se o valor da carta (1 ate 13)
//Entrada: um inteiro
//Retorno: inteiro com o valor da carta
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
int getValor (int x)
{
  int valor[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

  return valor[x /= 4];
}

//Inicializa o vetor de cartas
//Entrada: vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetor com 4 cartas
//Pos-condicao: vetor de cartas incializado (vazios)
void criaFreeCells (Carta freeCell[])
{
  int i;
  for (i = 0; i < NUMFREE; ++i)
    toZero(freeCell, i);
}

//deixa uma carta sem valor, como se nao existisse
//Entrada: vetor de cartas e inteiro com a posicao do vetor
//Retorno: nenhum
//Pre-condicao: inteiro com a posicao valido para o vetor de cartas
//Pos-condicao: carta com valor vazio
void toZero (Carta freeCell[], int n)
{
  freeCell[n].valor = 0;
  freeCell[n].naipe = ' ';
  freeCell[n].cor = -1;
}

//checa se o jogo acabou (jogador venceu)
//Entrada: vetor de pilhas
//Retorno: 1 caso o jogo acabou, 0 caso contrario
//Pre-condicao: vetor de pilhas com 12 pilhas
//Pos-condicao: nenhuma
int isEndGame (Pilha *pilhas[])
{
  int i;
  for (i = 8; i < NUMPILHAS; ++i)
    if (isEmpty(pilhas, i) || pilhas[i]->topo->carta.valor != 13)
      return 0;
  return 1;
}

//remove \n do fim da string caso possuir, senao limpa o buffer de entrada
//Entrada: uma string
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: \n removido da string ou buffer de entrada limpado
void removeNewLine (char *s)
{
  if (s[strlen(s) - 1] == '\n') 
    s[strlen(s) - 1] = '\0';
  else
    flushInput();  
}

//salva o estado do jogo em um arquivo binario caso o jogador queira 
//Entrada: vetor de pilhas e vetor de cartas
//Retorno: 0 caso o jogador nao queira salvar ou nao foi possivel criar
// o arquivo, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: cartas salvas no arquivo binario
int saveGame (Pilha *pilhas[], Carta freeCell[])
{
  char fName[STRSIZE];

  if (wantToSave())
    strcpy(fName, getFileName());
  else return 0;
  
  FILE *fw = fopen(fName, "wb");
  if (!fw) return 0;

  int i; No *j;
  for (i = 0; i < NUMPILHAS; ++i)
  {
    for (j = pilhas[i]->topo; j != NULL; j = j->prox)
      fwrite(&j->carta, sizeof(Carta), 1, fw);
    
    Carta end; end.valor = FIM;
    fwrite(&end, sizeof(Carta), 1, fw);
  }
  fwrite(freeCell, sizeof(Carta), NUMFREE, fw);

  fclose(fw);
  return 1;
}