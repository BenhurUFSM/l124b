// nome
#include <stdio.h>
#include <stdbool.h>

// funções para a entrada de dados pelo usuário

// tipo de figura
char le_tipo()
{
  char t;
  do {
    printf("Qual o tipo de figura (a-h ou z para sair)? ");
    scanf(" %c", &t);
  } while (t < 'a' || (t > 'h' && t != 'z'));
  return t;
}

// o caractere usado no desenho da figura
char le_caract()
{
  char t;
  printf("Com qual caractere desenhar a figura? ");
  scanf(" %c", &t);
  return t;
}

// o tamanho da figura
int le_tamanho()
{
  int a;
  do {
    printf("Qual o tamanho da figura? ");
    scanf("%d", &a);
  } while (a < 1);
  return a;
}


// Funções auxiliares para desenho de linhas de caracteres
// (peca no quesito sobre clareza de nomes)

// imprime n caracteres de código c
void putchars(int n, char c)
{
  for (int i = 0; i < n; i++) {
    putchar(c);
  }
}

// imprime n caracteres de código c e fim de linha
void putcharsl(int n, char c)
{
  putchars(n, c);
  putchar('\n');
}

// imprime n caracteres, inicia e termina com c, recheia com espaços
void putcharsb(int n, char c)
{
  putchar(c);
  if (n > 2)
    putchars(n - 2, ' ');
  if (n > 1)
    putchar(c);
}

// como a anterior, com fim de linha
void putcharsbl(int n, char c)
{
  putcharsb(n, c);
  putchar('\n');
}

// imprime n caracteres, inicia e termina com espaço, recheia com c
void putcharsbi(int n, char c)
{
  putchar(' ');
  if (n > 2)
    putchars(n - 2, c);
  if (n > 1)
    putchar(' ');
}

// como a anterior, com fim de linha
void putcharsbil(int n, char c)
{
  putcharsbi(n, c);
  putchar('\n');
}


// Funções para o desenho das figuras de cada tipo (incompleto)
// Essas funções estão organizadas da seguinte forma:
// - um laço com o número de linhas a desenhar
// - variáveis auxiliares para o número de caracteres de cada tipo em uma linha
//   - essas variáveis são inicializadas fora do laço com o número de caracteres
//     que devem ser desenhados na primeira linha, e após o desenho da linha,
//     são alterados para o valor da linha seguinte
//
// Algumas organizações alternativas:
// - calcular o número de caracteres a partir do valor da variável de controle
//   do laço
// - fazer com que a variável de controle tenha um dos números de caracteres
//   necessários, e calcular o outro(s) a partir dele ou com valor inicial e
//   atualização

void desenha_a(char caract, int tamanho)
{
  int nc = 1;
  for (int i = 0; i < tamanho; i++) {
    putcharsl(nc, caract);
    nc++;
  }
}

void desenha_c(char caract, int tamanho)
{
  int nc = 1;
  int nb = tamanho - 1;
  for (int i = 0; i < tamanho; i++) {
    putchars(nb, ' ');
    putcharsl(nc, caract);
    nc++;
    nb--;
  }
}

void desenha_e(char caract, int tamanho)
{
  int nc = 1;
  int nb = tamanho - 1;
  for (int i = 0; i < tamanho; i++) {
    putchars(nb, ' ');
    putcharsl(nc, caract);
    nc += 2;
    nb--;
  }
}

void desenha_f(char caract, int tamanho)
{
  desenha_e(caract, tamanho);
  int nc = tamanho * 2 - 3;
  int nb = 1;
  for (int i = 0; i < tamanho - 1; i++) {
    putchars(nb, ' ');
    putcharsl(nc, caract);
    nc -= 2;
    nb++;
  }
}

void desenha_e2(char caract, int tamanho)
{
  int nc = 1;
  int nb = tamanho - 1;
  for (int i = 0; i < tamanho; i++) {
    putchars(nb, ' ');
    putcharsbl(nc, caract);
    nc += 2;
    nb--;
  }
}

void desenha_g(char caract, int tamanho)
{
  desenha_e2(caract, tamanho);
  int nc = tamanho * 2 - 3;
  int nb = 1;
  for (int i = 0; i < tamanho - 1; i++) {
    putchars(nb, ' ');
    putcharsbl(nc, caract);
    nc -= 2;
    nb++;
  }
}

void desenha_h(char caract, int tamanho)
{
  // desenha uma linha inicial
  // desenha_e3(caract, tamanho);
  int nb = tamanho * 2 - 3;
  int nc = 2;
  for (int i = 0; i < tamanho - 1; i++) {
    putchars(nc, caract);
    putcharsbi(nb, caract);
    putcharsl(nc, caract);
    nb -= 2;
    nc++;
  }
  // desenha uma linha final
}


// desenha uma figura de um tipo qualquer, usando as funções específicas acima
void desenha(char tipo, char caract, int tamanho) {
  switch (tipo) {
    case 'a': case 'A':
      desenha_a(caract, tamanho);
      break;
    case 'c': case 'C':
      desenha_c(caract, tamanho);
      break;
    case 'e': case 'E':
      desenha_e(caract, tamanho);
      break;
    case 'f': case 'F':
      desenha_f(caract, tamanho);
      break;
    case 'g': case 'G':
      desenha_g(caract, tamanho);
      break;
    case 'h': case 'H':
      desenha_h(caract, tamanho);
      break;
    default:
      printf("ainda não sei desenhar tipo %c com %c tam=%d\n", tipo, caract, tamanho);
  }
}

// função principal
int main()
{
  char tipo;
  char caract;
  int tamanho;
  while (true) {
    tipo = le_tipo();
    if (tipo == 'z') break;
    caract = le_caract();
    tamanho = le_tamanho();
    desenha(tipo, caract, tamanho);
  }
}
