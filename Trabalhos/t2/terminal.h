// terminal.h
// ----------
// funções para controlar o terminal
// l124b

#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdbool.h>

// frequência de atualização da tela
#define TELAS_POR_SEGUNDO 30

// inicializa a tela
//   deve ser chamada no início do programa, antes de chamar qualquer outra
//   função deste arquivo)
void t_inicializa(void);

// volta a tela ao normal
//   deve ser chamada no final da execução do programa; depois de chamar esta
//   função, nenhuma outra deste arquivo deve ser chamada
void t_finaliza(void);


// retorna (por referência) o tamanho da tela (número de linhas e colunas)
void t_tamanho(int *ref_nlin, int *ref_ncol);

// retorna true se o tamanho da tela foi alterado desde a última chamada a t_tamanho
bool t_tamanho_mudou();


// limpa a tela
void t_limpa(void);

// posiciona o cursor na linha e coluna passadas como argumento
//   o canto superior esquerdo está na linha 1 e coluna 1
void t_lincol(int lin, int col);


// cor normal para as próximas impressões
void t_cor_normal(void);

// seleciona a cor das letras nas próximas impressões
//   os componentes da cor são valores entre 0 e 255
void t_cor_letra(int vermelho, int verde, int azul);

// seleciona a cor do fundo nas próximas impressões
//   os componentes da cor são valores entre 0 e 255
void t_cor_fundo(int vermelho, int verde, int azul);

// seleciona se o cursor aparece ou não
void t_mostra_cursor(bool mostra);

// para melhorar a apresentação na tela, os dados impressos são
// mantidos em memória para serem enviados agrupados ao sistema.
// Esta função deve ser chamada quando for necessário que os dados
// sejam enviados e efetivamente apareçam
void t_atualiza(void);


// TEMPO

// retorna o número de segundos desde algum momento no passado
double t_relogio(void);

// suspende a execução por um certo tempo (em segundos)
void t_cochila(float tempo);


// ENTRADA

// retorna true se tem alguma tecla digitada que ainda não foi lida
bool t_tem_tecla();

// retorna a próxima tecla digitada
//   retorna '\0' se não houver tecla digitada
char t_tecla();

#endif // TERMINAL_H
