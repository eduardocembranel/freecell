#ifndef ESTRUTURA_H
#define ESTRUTURA_H

//quantidade de pilhas para o vetor pilhas
#define NUMPILHAS 12

//quantidade de cartas para o vetor de cartas livres
#define NUMFREE 4

//quantidade cartas no baralho
#define NUMCARDS 52

//tamanho para as strings
#define STRSIZE 20

//tamanho para a string "jogada"
#define JOGADASIZE 9

//flag para indicar o fim de uma pilha para o arquivo binario
#define FIM 14

//estrutura para guardar os argumentos passados pela linha de comando
typedef struct mainArguments
{
  int argc;
  char **argv;
} MainArguments;

//estrutura da carta contendo suas caracteristicas: valor, naipe e cor
typedef struct carta
{
  char naipe;
  int valor;
  int cor;
} Carta;

//estrutura de no para pilha e armazena o tipo Carta
typedef struct no
{
  Carta carta;
  struct no *prox;
} No;

//estrutura para o topo da pilha
typedef struct topo
{
  No *topo;
} Pilha;

#endif // !ESTRUTURA_H