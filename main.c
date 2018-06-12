#include "jogo.h"

int main (int argc, char **argv)
{
  MainArguments argumentos = getArguments(argc, argv);
  
  srand(time(NULL));
  run(argumentos);

  return 0;
}

//armazena na estrutura argumentos a quantidade de strings passadas na linha
// de comando e deixa o char** apontando para o vetor de strings passado
// na linha de comando
//Entrada: argumentos passados pela linha de comando pelo usuario
//Retorno: estrutura MainArguments
//Pre-condicao: nenhuma
//Pos-condicao: nenhuma
MainArguments getArguments (int argc, char **argv)
{
  MainArguments argumentos;
  argumentos.argc = argc;
  argumentos.argv = argv;

  return argumentos;
}