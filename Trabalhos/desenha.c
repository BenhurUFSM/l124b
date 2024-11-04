// programa para exemplificar o uso de funções para o controle da tela


#include <stdio.h>

// posiciona o cursor na linha e coluna (valores iniciam em 1)
void posiciona_cursor(int linha, int coluna)
{
  printf("%c[%d;%dH", 27, linha, coluna);
}

// limpa a tela
void limpa_tela()
{
  printf("%c[2J", 27);
  posiciona_cursor(1, 1);
}

// altera a cor dos próximos caracteres escritos na tela (valores entre 0 e 255)
void altera_cor_caracteres(int vermelho, int verde, int azul)
{
  printf("%c[38;2;%d;%d;%dm", 27, vermelho, verde, azul);
}

// altera a cor de fundo dos próximos caracteres escritos na tela
//   (valores entre 0 e 255)
void altera_cor_fundo(int vermelho, int verde, int azul)
{
  printf("%c[48;2;%d;%d;%dm", 27, vermelho, verde, azul);
}

// retorna a cor dos caracteres e fundo para o normal
void cor_normal()
{
  printf("%c[m", 27);
}

// envia o que foi escrito para o terminal
// (deve ser chamada quando terminar de desenhar a tela)
void atualiza_tela()
{
  fflush(stdout);
}

int main()
{
  limpa_tela();
  altera_cor_caracteres(120, 50, 80);
  posiciona_cursor(2, 10);
  printf("   teste 1   ");
  altera_cor_fundo(20, 150, 80);
  posiciona_cursor(3, 10);
  printf("   teste 2   ");
  altera_cor_caracteres(20, 50, 180);
  altera_cor_fundo(20, 50, 80);
  posiciona_cursor(4, 10);
  printf("   teste 3   ");
  cor_normal();
  posiciona_cursor(5, 10);
  printf("   teste 4   ");
  posiciona_cursor(7, 1);
  atualiza_tela();
}
