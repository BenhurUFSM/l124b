// Programa para exemplificar o uso das funções em terminal.[hc]
// l124b
// Para compilar:
//   gcc -o terminal_exemplo terminal_exemplo.c terminal.c
// Na execução, use as teclas wasd para movimentar a mira sobre o alvo, e enter
//   para aniquilá-lo

#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>

void desenha_tela(int l_alvo, int c_alvo, int l_cursor, int c_cursor)
{
  t_cor_normal();
  t_limpa();
  // desenha o cursor
  t_cor_letra(20, 150, 80);
  t_lincol(l_cursor - 1, c_cursor);
  putchar('|');
  t_lincol(l_cursor + 1, c_cursor);
  putchar('|');
  t_lincol(l_cursor, c_cursor - 2);
  puts("-- --");
  // desenha o alvo
  t_cor_letra(200, 20, 20);
  t_lincol(l_alvo, c_alvo);
  putchar('+');

  t_atualiza();
}

bool trata_teclado(int *ref_lin, int *ref_col)
{
  int nlin, ncol;
  t_tamanho(&nlin, &ncol);
  if (t_tem_tecla()) {
    char tecla = t_tecla();
    switch (tecla) {
      case 'w':
        if (*ref_lin > 2) (*ref_lin)--;
        break;
      case 's':
        if (*ref_lin < nlin - 1) (*ref_lin)++;
        break;
      case 'a':
        if (*ref_col > 3) (*ref_col)--;
        break;
      case 'd':
        if (*ref_col < ncol - 2) (*ref_col)++;
        break;
      case '\n':
        return true;
    }
  }
  return false;
}

int main()
{
  bool fim = false;
  int nlin, ncol;
  int l_alvo, c_alvo;
  int l_curs, c_curs;
  double ultima_mexida;

  t_inicializa();

  t_tamanho(&nlin, &ncol);
  l_alvo = 2 + rand() % (nlin - 4);
  c_alvo = 2 + rand() % (ncol - 4);
  ultima_mexida = t_relogio();
  l_curs = nlin / 2;
  c_curs = ncol / 2;
  
  while (!fim) {
    fim = trata_teclado(&l_curs, &c_curs);
    if (t_relogio() - ultima_mexida >= 8.2) {
      l_alvo = 2 + rand() % (nlin - 4);
      c_alvo = 2 + rand() % (ncol - 4);
      ultima_mexida = t_relogio();
    }
    desenha_tela(l_alvo, c_alvo, l_curs, c_curs);
  }

  t_finaliza();
  if (l_alvo == l_curs && c_alvo == c_curs) {
    printf("acertou\n");
  } else {
    printf("errou\n");
  }
}
