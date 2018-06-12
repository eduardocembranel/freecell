#include "ui.h"

//Exibe no console a representacao grafica do menu do jogo
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: elementos graficos do menu exibidos na tela
void setLogo (void)
{
  clear();
  printf("\
 _______  _______  _______  _______  _______  _______  _        _\n\
(  ____ \\(  ____ )(  ____ \\(  ____ \\(  ____ \\(  ____ \\( \\      ( \\\n\
| (    \\/| (    )|| (    \\/| (    \\/| (    \\/| (    \\/| (      | (\n\
| (__    | (____)|| (__    | (__    | |      | (__    | |      | |\n\
|  __)   |     __)|  __)   |  __)   | |      |  __)   | |      | |\n\
| (      | (\\ (   | (      | (      | |      | (      | |      | |\n\
| )      | ) \\ \\__| (____/\\| (____/\\| (____/\\| (____/\\| (____/\\|\
 (____/\\\n\
|/       |/   \\__/(_______/(_______/(_______/(_______/(_______/(_______/\n\n");     

printf("                    [1]JOGAR [2]INSTRUCOES [3]SAIR\n\
                    >> ");
}

//Limpa a tela do console
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: tela limpada
void clear (void)
{
  system("clear");
}

//Exibe a janela de instrucoes e aguarda por uma ENTER para retornar
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagens de instrucoes e regras do jogo exibidas no console
void showInstructions (void)
{
  clear();
  printf("\n                               INSTRUCOES\n");
  printf("\n    1) Para continuar um jogo salvo anteriormente, o nome do arquivo\n\
    de save deve ser inserido na linha de comando como argumento  de\n\
    entrada, no momento em que o programa for executado.\n");
  printf("\n    2) Objetivo: O objetivo e mover todas as cartas para as 4 pilhas\n\
    bases em ordem crescente no respectivo naipe.\n");
  printf("\n    3) Regras: Existem 4 pilhas de base que aceitam  cartas em ordem\n\
    crescente do mesmo naipe. Existem 4 celulas livres que podem ser\n\
    utilizadas como espaco temporario para apenas uma carta. Existem\n\
    8 pilhas que podem ser organizadas  em sequencia  decrescente  e\n\
    com cores  alternadas. Pilhas  vazias  podem  ser  ocupadas  por\n\
    qualquer carta.\n");
  printf("\n    4) SuperMove: Uma pilha decrescente de cores alternadas pode ser\n\
    movimentada com um unico movimento,  com uma certa quantidade de\n\
    cartas, sem precisar  utilizar celulas vazias  e espacos vazios.\n\
    A quantia maxima de cartas que pode-se movimentar sera dada por:\n\n\
              N = (1 + celulas_livres) x 2^(pilhas_vazias)\n");
  printf("\n    5) Ao jogar, pode ser solicitado  o comando help (h) atraves  da\n\
    linha de comando caso surgirem duvidas em relacao a sintaxe  dos\n\
    comandos para mover as cartas.\n");

  pressAnyKey();
}

//Exibe na tela uma mensagem para o usuario digitar enter e aguarta pela entrada
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: buffer de entrada deve estar vazio
//Pos-condicao: nenhuma
void pressAnyKey (void)
{
  printf("\nPressione ENTER para retornar "); 
  flushInput();
}

//Exibe o jogo na tela com as cartas em suas pilhas
//Entrada: vetor de pilhas e vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetores inicializados
//Pos-condicao: jogo exibido na tela
void show (Pilha *pilhas[], Carta freeCell[])
{
  Pilha *inversa[NUMPILHAS];
  getInversa(inversa, pilhas);
  
  printL1();
  printL2(pilhas, freeCell);
  printL3();
  printPilhas(inversa);
  askForMovement();
  
  destroy(inversa);
}

//exibe na tela a primeira linha da UI contendo os nomes das pilhas e cedulas
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: nomes da pilhas e cedulas exibidos na tela
void printL1 (void)
{
  clear();
  printf ("   F1        F2        F3        F4        \
         B1        B2        B3        B4\n");
}

//exibe na tela as cartas das cedulas livres e o topo das 4 pilhas da fundacao
//Entrada: vetor de pilhas e vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas com 12 pilhas e vetor de cartas com 4 cartas
//Pos-condicao: cartas das cedulas livres e topo das pilhas base exibidas
void printL2 (Pilha *pilhas[], Carta freeCell[])
{
  int i;
  for (i = 0; i < NUMFREE; ++i)
    printCarta(freeCell[i], 2, i*10 + 1, 0);
  
  printSimbolos();

  int cnt = 5;
  Carta vazia; vazia.naipe = ' '; vazia.valor = 0;
  for (i = 8; i < NUMPILHAS; ++i, ++cnt)
  {
    if (!isEmpty(pilhas, i))
      printCarta(pilhas[i]->topo->carta, 2, cnt*10, 0); 
    else
      printCarta(vazia, 2, cnt*10, 0);
  }
}

//imprime na tela uma carta (inteira ou apenas a parte superior)
//Entrada: carta, dois inteiros (coordenadas no console) e um inteiro (opcao)
//Retorno: nenhum
//Pre-condicao: opcao deve ser 0 ou 1 (carta inteira ou apenas a parte superior)
//Pos-condicao: carta exibida na tela nas coordenadas indicadas
void printCarta (Carta carta, int x, int y, int opcao)
{
  // *b[] --> bordas da carta (vertical, horizontal, sup direito, sup esquerdo
  // inf direito e inf esquerdo)
  char *b[] = {"\u2501", "\u2503", "\u2513", "\u250F", "\u251B", "\u2517"};
  char *naipes[] = {" ", "\u2663", "\u2660", "\u2661", "\u2662"};
  char *valor[] = {" ", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10",
   "J", "Q", "K"};
  int pos;

  switch (carta.naipe)
  {
    case 'C': pos = 1; break;
    case 'O': pos = 2; break;
    case 'P': pos = 3; break;
    case 'E': pos = 4; break;
    case ' ': pos = 0; break;
  }
  
  setCursor(x, y); ++x;

  //imprime apenas a parte superior da carta
  if (opcao == 1)
  {
    printf("%s%s%s%s%s%s%s%s%s\n", b[3], b[0], b[0], b[0], b[0], b[0], b[0],
     b[0], b[2]);
    setCursor(x, y); ++x;
    if (carta.valor == 10)
      printf("%s%s   %s %s\n", b[1], valor[carta.valor], naipes[pos], b[1]);
    else
      printf("%s%s    %s %s\n", b[1], valor[carta.valor], naipes[pos], b[1]);
  }

  //imprime a carta inteira
  else if (opcao == 0)
  {
    printf("%s%s%s%s%s%s%s%s%s\n", b[3], b[0], b[0], b[0], b[0], b[0], b[0],
     b[0], b[2]);
    setCursor(x, y); ++x;
    if (carta.valor == 10)
      printf("%s%s     %s\n", b[1], valor[carta.valor], b[1]);
    else
      printf("%s%s      %s\n", b[1], valor[carta.valor], b[1]);
    setCursor(x, y); ++x;
    printf("%s       %s\n", b[1], b[1]);
    setCursor(x, y); ++x;
    printf("%s   %s   %s\n", b[1], naipes[pos], b[1]);
    setCursor(x, y); ++x;
    printf("%s       %s\n", b[1], b[1]);
    setCursor(x, y); ++x;

    //10: unico valor q possui 2 caracteres, mudando a logica da impressao
    if (carta.valor == 10)
      printf("%s     %s%s\n", b[1], valor[carta.valor], b[1]);
    else
      printf("%s      %s%s\n", b[1], valor[carta.valor], b[1]);
    setCursor(x, y);
    printf("%s%s%s%s%s%s%s%s%s\n", b[5], b[0], b[0], b[0], b[0], b[0], b[0],
     b[0], b[4]);
  }
}

//posiciona o cursor de saida em uma coordenada no console
//Entrada: dois inteiros representando a coordenada (x, y) do console
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: cursor posicionado no local indicado
void setCursor (int x, int y)
{
  printf("\033[%d;%dH", x, y);
}

//imprime na tela o simbolo das 4 naipes no centro superior da tela
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhum
//Pos-condicao: simbolos das 4 naipes exibidos no centro superior da tela
void printSimbolos (void)
{
  setCursor(4, 43);
  printf("\u2663 \u2662");
  setCursor(5, 43);
  printf("\u2661 \u2660");
}

//imprime uma linha de 88 caracteres "=" na tela e o nome das pilhas inferiores
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: 88 "=" e nome das pilhas inferiores impressos na tela 
void printL3 (void)
{
  int i;
  for (i = 0; i < 88; ++i)
    printf("=");
    
  printf("\n       P1        P2        P3        P4\
        P5        P6        P7        P8\n");
}

//exibe as 8 pilhas inferiores na tela com todas as cartas
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas inicializados com 8+ pilhas de cartas
//Pos-condicao: cartas das pilhas inferiores exibidas na tela
void printPilhas (Pilha *pilhas[])
{
  No *j;
  int i, cnt;
  int x = 0, y = 0, posMaiorPilha = 0;

  for (i = 0; i < 8; ++i)
  {
    for (j = pilhas[i]->topo, cnt = 0; j != NULL; j = j->prox, ++cnt)
    {
      x = 11 + cnt*2;
      y = 5 + i*10;
      if (j->prox)
        printCarta(j->carta, x, y, 1);
      else
        printCarta(j->carta, x, y, 0);
    }
    if (posMaiorPilha < cnt)
      posMaiorPilha = cnt;
  }

  //determina a coordenada para setar o cursor apos imprimir tudo.
  //Caso seja fim de jogo (posMaiorPilha = 0) nenhuma carta inteira
  //sera exibida nas pilhas inferiores, logo a posicao mudará
  if (posMaiorPilha == 0)
    setCursor(12, 0);
  else
    setCursor(17 + 2*posMaiorPilha, 0);
}

//imprime uma mensagem pedindo ao jogador inserir uma jogada/comando
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagem exibida na tela
void askForMovement (void)
{
  printf(">> Insira um movimento (h para ajuda | q para sair e salvar):\n>> ");
}

//exibe informacoes com a sintaxe dos possiveis comandos que podem ser efetuados
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagem exibida na tela
void showHelp (void)
{
    clear();
    printf("\n                        AJUDA\n");
    printf("\n  Os movimentos devem ser inseridos no seguinte formato:\n\n");
    printf("  1) Para solicitar a impressao de uma pilha: <origem>\n");
    printf("  Ex: Imprimindo o conteudo da pilha P8:\n\n");
    printf("  >> P8\n\n");
    printf("  2) Para mover uma unica carta: <origem><destino>\n");
    printf("  Ex: Movendo uma carta da Pilha P1 para a Pilha P2:\n\n");
    printf("  >> P1P2\n\n");
    printf("  3) Para mover multiplas cartas: <origem><(qnt_cartas)><destino>\n");
    printf("  Ex: Movendo tres cartas da Pilha P1 para a Pilha P2:\n\n");
    printf("  >> P1(3)P2\n");
}

//imprime uma unica pilha com as cartas, na tela e aguarda o usuario retornar
//Entrada: vetor de pilhas e posicao da pilha
//Retorno: nenhum
//Pre-condicao: pilha inicializada
//Pos-condicao: cartas da pilha exibidas na tela
void printPilha (Pilha *pilhas[], int n)
{
  No *i;
  int cnt = 1;
  clear();
  printf("Pilha:\n\n");
  for (i = pilhas[n]->topo; i != NULL ; i = i->prox, cnt += 12)
    printCarta(i->carta, 3, cnt, 0);
  setCursor(10, 1);
  pressAnyKey();
}

//exibe a mensagem de parabenizacao por vencer o jogo e aguarda por um ENTER
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagem exibida na tela
void endGame (void)
{
  setCursor(12, 1);
  printf("Parabens, voce venceu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
  pressAnyKey();
}

//exibe uma mensagem na tela pedindo para salvar ou nao e aguarda pela escolha
//Entrada: nenhuma
//Retorno: 1 caso o usuario deseja salvar, 0 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int wantToSave (void)
{
  int escolha = 0;

  while (escolha != 1 && escolha != 2)
  {
    clear(); setCursor(1, 1);
    printf("  \n\n                  [1]SALVAR E SAIR   [2]SAIR SEM SALVAR\n\
                  >> ");
    scanf("%d", &escolha);
    flushInput();
  }
  if (escolha == 1)
    return 1;
  return 0;
}

//se obtem o nome do arquivo que o usuario deseja salvar o jogo
//Entrada: nenhuma
//Retorno: uma string (nome do arquivo)
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
char* getFileName (void)
{
  static char fName[STRSIZE];

  printf("                  >> INSIRA O NOME PARA O SAVE:\n\
                  >> ");
  fgets(fName, STRSIZE, stdin); removeNewLine(fName);

  return fName;
}