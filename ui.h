#ifndef UI_H
#define UI_H

#include "jogo.h"

//Exibe no console a representacao grafica do menu do jogo
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: elementos graficos do menu exibidos na tela
void setLogo (void);

//Limpa a tela do console
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: tela limpada
void clear (void);

//Exibe a janela de instrucoes e aguarda por uma ENTER para retornar
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagens de instrucoes e regras do jogo exibidas no console
void showInstructions (void);

//Exibe na tela uma mensagem para o usuario digitar enter e aguarta pela entrada
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: buffer de entrada deve estar vazio
//Pos-condicao: nenhuma
void pressAnyKey (void);

//Exibe o jogo na tela com as cartas em suas pilhas
//Entrada: vetor de pilhas e vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetores inicializados
//Pos-condicao: jogo exibido na tela
void show (Pilha**, Carta*);

//exibe na tela a primeira linha da UI contendo os nomes das pilhas e cedulas
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: nomes da pilhas e cedulas exibidos na tela
void printL1 (void);

//exibe na tela as cartas das cedulas livres e o topo das 4 pilhas da fundacao
//Entrada: vetor de pilhas e vetor de cartas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas com 12 pilhas e vetor de cartas com 4 cartas
//Pos-condicao: cartas das cedulas livres e topo das pilhas base exibidas
void printL2 (Pilha**, Carta*);

//imprime na tela uma carta (inteira ou apenas a parte superior)
//Entrada: carta, dois inteiros (coordenadas no console) e um inteiro (opcao)
//Retorno: nenhum
//Pre-condicao: opcao deve ser 0 ou 1 (carta inteira ou apenas a parte superior)
//Pos-condicao: carta exibida na tela nas coordenadas indicadas
void printCarta (Carta, int, int, int);

//posiciona o cursor de saida em uma coordenada no console
//Entrada: dois inteiros representando a coordenada (x, y) do console
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: cursor posicionado no local indicado
void setCursor (int x, int y);

//imprime na tela o simbolo das 4 naipes no centro superior da tela
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhum
//Pos-condicao: simbolos das 4 naipes exibidos no centro superior da tela
void printSimbolos (void);

//imprime uma linha de 88 caracteres "=" na tela e o nome das pilhas inferiores
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: 88 "=" e nome das pilhas inferiores impressos na tela 
void printL3 (void);

//exibe as 8 pilhas inferiores na tela com todas as cartas
//Entrada: vetor de pilhas
//Retorno: nenhum
//Pre-condicao: vetor de pilhas inicializados com 8+ pilhas de cartas
//Pos-condicao: cartas das pilhas inferiores exibidas na tela
void printPilhas (Pilha**);

//imprime uma mensagem pedindo ao jogador inserir uma jogada/comando
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagem exibida na tela
void askForMovement ();

//exibe informacoes com a sintaxe dos possiveis comandos que podem ser efetuados
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagem exibida na tela
void showHelp (void);

//imprime uma unica pilha com as cartas, na tela e aguarda o usuario retornar
//Entrada: vetor de pilhas e posicao da pilha
//Retorno: nenhum
//Pre-condicao: pilha inicializada
//Pos-condicao: cartas da pilha exibidas na tela
void printPilha (Pilha**, int);

//exibe a mensagem de parabenizacao por vencer o jogo e aguarda por um ENTER
//Entrada: nenhuma
//Retorno: nenhum
//Pre-condicao: nenhuma
//Pos-condicao: mensagem exibida na tela
void endGame (void);

//exibe uma mensagem na tela pedindo para salvar ou nao e aguarda pela escolha
//Entrada: nenhuma
//Retorno: 1 caso o usuario deseja salvar, 0 caso contrario
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
int wantToSave (void);

//se obtem o nome do arquivo que o usuario deseja salvar o jogo
//Entrada: nenhuma
//Retorno: uma string (nome do arquivo)
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
char* getFileName (void);

#endif // !UI_H