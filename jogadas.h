#ifndef J0GADAS_H
#define JOGADAS_H

#include "estrutura.h"

//processa os movimento inserido pelo jogados na linha de comando
//Entrada: string contendo a jogada, vetor de pilhas e vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas e vetor de cartas inicializado
//Pos-condicao: jogada efetuada caso possivel
void processMovement (char*, Pilha**, Carta*);

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid0 (char*);

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid (char*);

//move uma carta de uma pilha para uma cedula livre se possivel
//Entrada: vetor de pilhas, vetor de cartas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void pilhaToFreeCell (Pilha**, Carta*, int, int);

//move uma carta de uma pilha para uma das pilhas da fundacao (base)
//Entrada: vetor de pilhas, vetor de cartas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void pilhaToBase (Pilha**, int, int);

//checa se o valor da primeira carta é exatamente 1 maior que a segunda
//Entrada: 2 cartas
//Retorno: 1 caso a primeira carta seja exatamente 1 valor maior que a segunda
//Pre-condicao: cartas nao vazias
//Pos-condicao: nenhuma
int isNext (Carta, Carta);

//move uma carta de uma pilha inferiores para outra pilha inferior
//Entrada: vetor de pilhas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void pilhaToPilha (Pilha**, int, int);

//checa se a car das duas cartas é a mesma
//Entrada: 2 cartas
//Retorno: 1 caso as cores forem iguais, 0 caso contrario
//Pre-condicao: cartas nao vazias
//Pos-condicao: nenhuma
int isSameColor (Carta, Carta);

//move uma carta de uma cedula livre para outra cedula livre se possivel
//Entrada: vetor de cartas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: vetor de cartas inicializado
//Pos-condicao: carta movida se possivel
void freeCellToFreeCell (Carta*, int, int);

//move uma carta de uma cedula livre para uma das pilhas base se possivel
//Entrada: vetor de cartas, vetor de pilhas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void freeCellToBase (Carta*, Pilha**, int, int);

//move uma carta de uma cedula livre para uma das pilhas inferiores, se possivel
//Entrada: vetor de cartas, vetor de pilhas, 2 inteiros (origem e destino)
//Retorno: nenhum
//Pre-condicao: pilhas e vetor de cartas inicializados
//Pos-condicao: carta movida se possivel
void freeCellToPilha (Carta*, Pilha**, int, int);

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid2 (char*);

//checa se é possivel mover multiplas cartas de uma determinada pilha para outra 
//Entrada: vetor de pilhas, vetor de cartas, 3 inteiros (origem, destino e
// quantidade de cartas a serem movidas)
//Retorno: 1 caso seja possivel, 0 caso contrario
//Pre-condicao: vetor de pilhas e de cartas inicializados
//Pos-condicao: nenhuma
int isPossible (Pilha**, Carta*, int, int, int);

//move 2 ou mais carta de uma pilha para outra pilha inferior
//Entrada: vetor de pilhas, 3 inteiros (origem, destido e quantidade de cartas) 
//Retorno: nenhum
//Pre-condicao: vetor de pilhas inicializado
//Pos-condicao: cartas movidas
void mPilhaToPilha (Pilha**, int, int, int);

//insere uma carta na pilha
//Entrada: pilha e carta a ser inserida
//Retorno: nenhum
//Pre-condicao: pilha inicializada
//Pos-condicao: carta inserida na pilha
void push1 (Pilha*, Carta);

//remove uma carta da pilha
//Entrada: pilha
//Retorno: carta removida
//Pre-condicao: pilha inicializada
//Pos-condicao: carta removida da pilha caso nao for vazia
Carta pop1 (Pilha*);

//checa se a jogada inserida nao tenta mover uma carta de/para um lugar invalido
//Entrada: string com a jogada
//Retorno: 0 caso a jogada seja invalida, 1 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int isValid3 (char*);

#endif // !JOGADAS_H