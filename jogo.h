#ifndef J0GO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "estrutura.h"

//armazena na estrutura argumentos a quantidade de strings passadas na linha
// de comando e deixa o char** apontando para o vetor de strings passado
// na linha de comando  
//Entrada: argumentos passados pela linha de comando pelo usuario
//Retorno: estrutura MainArguments
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
MainArguments getArguments (int , char**);

//Roda o jogo partindo do menu e distribuindo as opcoes selecionadas
//Entrada: argumentos passados pela linha de comando pelo usuario
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
void run (MainArguments);

//Roda o menu do jogo e aguarda por uma escolha do usuario
//Entrada: nenhuma
//Retorno: inteiro (1-3) representando a escolha do usuario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int menu (void);

//Limpa o buffer de entrada, caso estiver vazio aguarda por \n (enter)
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: buffer de entrada vazio
void flushInput (void);

//Distribui a escolha feita pelo jogador, anteriormente, no menu
//Entrada: argumentos da linha de comando e a escolha do jogador
//Retorno: nenhum
//Pre-condicao: escolha deve ser 1 (jogar) ou 2 (instrucoes)
//Pos-condicao: incia o jogo ou exibe as intrucoes
void setOption (int, MainArguments);

//inicializa o jogo, aguarda por jogadas e processa os comandos do usuario
//Entrada: argumentos passados pela linha de comando pelo usuario
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
void play (MainArguments);

//inicializa as pilhas e as cedulas livres e carrega/embaralha as cartas
//Entrada: vetor de pilhas de cartas, vetor de cartas e argumentos do main
//Retorno: nenhum
//Pre-condicao: vetor de pilhas com 12 pilhas e vetor de cartas de 4 cartas
//Pos-condicao: cartas distribuidas nas pilhas e exibe o jogo na tela 
void startGame (Pilha**, Carta*, MainArguments);

//carrega os dados do jogo para as pilhas e cedulas livres, caso arquivo exista
//Entrada: nome do arquivo, vetor de pilhas e vetor de cartas
//Retorno: 0 caso o carregamento obteve fracasso, 1 caso contrario
//Pre-condicao: vetor de pilha deve conter 12 pilhas e vetor de cartas, 4 cartas
//Pos-condicao: pilhas inicializadas com jogo carregado caso obteve sucesso
int loadGame (char*, Pilha**, Carta*);

//as 12 pilhas do jogo sao criadas (alocadas na memoria) com valor inicial nulo
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas deve conter 12 pilhas
//Pos-condicao: pilhas inicializadas, vazias, com espaco na memoria
void criaPilhas (Pilha**);

//insere uma carta na pilha indicada
//Entrada: vetor de pilhas, inteiro (posicao da pilha) e a carta a ser inserida 
//Retorno: nenhum
//Pre-condicao: pilhas inicializadas
//Pos-condicao: carta inserida na pilha
void push (Pilha**, int, Carta);

//obtem-se a configuracao inversa de um vetor de 12 pilhas
//Entrada: vetor de pilhas nulo e vetor de pilhas original
//Retorno: nenhum
//Pre-condicao: vetor original inicializado 
//Pos-condicao: vetor de 12 pilhas invertido p/ outra pilha (original n altera)
void getInversa (Pilha**, Pilha**);

//libera a memoria alocada do vetor de pilhas
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de 12 pilhas com memoria alocada dinamicamente
//Pos-condicao: elementos removidos e memoria liberada das 12 pilhas
void destroy (Pilha**);

//checa se uma pilha e vazia
//Entrada: vetor de pilhas e posicao da pilha a ser checada
//Retorno: 1 se a pilha for vazia, 0 caso contrario
//Pre-condicao: vetor de pilhas inicializado
//Pos-condicao: nenhuma
int isEmpty (Pilha**, int);

//remove uma carta da pilha
//Entrada: vetor de pilhas e posicao da pilha
//Retorno: carta removida
//Pre-condicao: vetor de pilha inicializado
//Pos-condicao: carta removida da pilha caso nao for vazia
Carta pop (Pilha**, int);

//faz o embaralhamento das 52 cartas e distribui elas para as pilhas
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas inicializado
//Pos-condicao: nenhuma
void embaralha (Pilha**);

//Obtem-se uma das 52 cartas do baralho
//Entrada: um inteiro
//Retorno: uma das 52 cartas do baralho
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
Carta getCarta (int);

//Obtem-se uma das 4 naipes existes
//Entrada: um inteiro
//Retorno: caracter com a naipe obtida
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
char getNaipe (int);

//Obtem-se uma das 2 cores de carta (vermelha ou preta)
//Entrada: um inteiro
//Retorno: 0 para a cor vermelha, 1 para a cor preta
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
int getCor (int);

//Obtem-se o valor da carta (1 ate 13)
//Entrada: um inteiro
//Retorno: inteiro com o valor da carta
//Pre-condicao: valor do inteiro de entrada entre 0 a 51
//Pos-condicao: nenhuma
int getValor (int);

//Inicializa o vetor de cartas
//Entrada: vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetor com 4 cartas
//Pos-condicao: vetor de cartas incializado (vazios)
void criaFreeCells (Carta*);

//deixa uma carta sem valor, como se nao existisse
//Entrada: vetor de cartas e inteiro com a posicao do vetor
//Retorno: nenhum
//Pre-condicao: inteiro com a posicao valido para o vetor de cartas
//Pos-condicao: carta com valor vazio
void toZero (Carta*, int);

//posiciona o cursor de saida em uma coordenada no console
//Entrada: dois inteiros representando a coordenada (x, y) do console
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: cursor posicionado no local indicado
void setCursor (int, int);

//checa se o jogo acabou (jogador venceu)
//Entrada: vetor de pilhas
//Retorno: 1 caso o jogo acabou, 0 caso contrario
//Pre-condicao: vetor de pilhas com 12 pilhas
//Pos-condicao: nenhuma
int isEndGame (Pilha**);

//remove \n do fim da string caso possuir, senao limpa o buffer de entrada
//Entrada: uma string
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: \n removido da string ou buffer de entrada limpado
void removeNewLine (char*);

//salva o estado do jogo em um arquivo binario caso o jogador queira 
//Entrada: vetor de pilhas e vetor de cartas
//Retorno: 0 caso o jogador nao queira salvar ou nao foi possivel criar
// o arquivo, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: cartas salvas no arquivo binario
int saveGame (Pilha *pilhas[], Carta freeCell[]);

#endif // !JOGO_H