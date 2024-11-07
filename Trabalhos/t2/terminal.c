#include "terminal.h"

// implementado usando
//   - sequências de escape ANSI para controlar a saída (cursor, cores)
//   - ioctl para descobrir o tamanho do terminal
//   - signal para ser sinalizado quando o terminal mudar de tamanho
//   - clock_gettime para obter o valor do relógio com boa resolução


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <signal.h>
#include <time.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <termios.h>
#include <unistd.h>

// INICIALIZAÇÃO

// funções auxiliares

static void t_altera_configuracao_saida(void);
static void t_altera_configuracao_entrada(bool altera);
static void t_seleciona_tela_alternativa(bool alt);
static void t_le_nlincol(int);

void t_inicializa(void)
{
  t_altera_configuracao_saida();
  t_altera_configuracao_entrada(true);
  t_seleciona_tela_alternativa(true);
  // chama t_le_nlincol se tela mudar de tamanho
  signal(SIGWINCH, t_le_nlincol);
  t_le_nlincol(0);
  t_limpa();
  t_mostra_cursor(false);
  t_atualiza();
}

void t_finaliza(void)
{
  t_limpa();
  t_seleciona_tela_alternativa(false);
  t_mostra_cursor(true);
  t_atualiza();
  t_altera_configuracao_entrada(false);
}

// implementação das funções auxiliares

// muda o modo de saída dos caracteres, de forma que sejam enviados para uma
// região de memória (um buffer) antes de serem enviados à tela. Isso melhora
// a qualidade de apresentação da tela, mas exige que se chame t_atualiza
// ao final da impressão para que a tela receba efetivamente os caracteres.
static void t_altera_configuracao_saida(void)
{
  setbuf(stdout, malloc(BUFSIZ));
}

// muda o processamento de caracteres de entrada pelo terminal
//   para que a leitura seja feita em caracteres individuais, sem esperar
//   digitar enter
static void t_altera_configuracao_entrada(bool altera)
{
  // variável estática para guardar a configuração original do teclado
  static struct termios config_original_do_teclado;
  if (altera) {
    // lê e guarda a configuração atual do teclado
    tcgetattr(1, &config_original_do_teclado);
    struct termios config_nova_do_teclado = config_original_do_teclado;
    // altera a configuração para não ecoar o que é digitado nem esperar <enter>
    config_nova_do_teclado.c_lflag &= (~ECHO & ~ICANON);
    config_nova_do_teclado.c_cc[VMIN] = 0;
    config_nova_do_teclado.c_cc[VTIME] = 0;
    // envia a nova configuração para o sistema
    tcsetattr(1, TCSANOW, &config_nova_do_teclado);
  } else {
    // reconfigura o teclado com a configuração original
    tcsetattr(1, TCSANOW, &config_original_do_teclado);
  }
}

static void t_seleciona_tela_alternativa(bool alt)
{
  if (alt) {
    printf("\e[?1049h");
  } else {
    printf("\e[?1049l");
  }
}


// SAÍDA

void t_mostra_cursor(bool mostra)
{
  if (mostra) {
    printf("\e[?25h");
  } else {
    printf("\e[?25l");
  }
}

void t_atualiza(void)
{
  // espera até que seja a hora de atualizar a tela
  static double ultima_atualizacao = 0;
  double proxima_atualizacao = ultima_atualizacao + (1.0 / TELAS_POR_SEGUNDO);
  double agora = t_relogio();
  if (agora < proxima_atualizacao) {
    t_cochila(proxima_atualizacao - agora);
    ultima_atualizacao = proxima_atualizacao;
  } else {
    ultima_atualizacao = agora;
  }

  // envia os dados de saída memorizados para a tela
  fflush(stdout);
}

void t_limpa(void)
{
  printf("\e[2J");
}

void t_lincol(int lin, int col)
{
  printf("\e[%d;%dH", lin, col);
}

static int nlin, ncol; 
static bool tamanho_da_tela_mudou;

// descobre o número de linhas e colunas do terminal
static void t_le_nlincol(int nada)
{
  struct winsize tam;
  bool ok = false;
  // pede para o sistema o tamanho da janela de texto
  int fd = open(ctermid(NULL), O_RDWR);
  if (fd != -1) {
    if (ioctl(fd, TIOCGWINSZ, &tam) == 0) {
      nlin = tam.ws_row;
      ncol = tam.ws_col;
      if (nlin > 15 && ncol > 20) {
        ok = true;
      }
    }
  }
  if (!ok) {
    nlin = 24;
    ncol = 80;
    printf("Não consegui identificar tamanho do terminal, usando %dx%d\n",
        nlin, ncol);
  }
  tamanho_da_tela_mudou = true;
}

bool t_tamanho_mudou()
{
  return tamanho_da_tela_mudou;
}

void t_tamanho(int *ref_nlin, int *ref_ncol)
{
  *ref_nlin = nlin;
  *ref_ncol = ncol;
  tamanho_da_tela_mudou = false;
}

void t_cor_normal(void)
{
  printf("\e[m");
}

void t_cor_letra(int vermelho, int verde, int azul)
{
  printf("\e[38;2;%d;%d;%dm", vermelho, verde, azul);
}

void t_cor_fundo(int vermelho, int verde, int azul)
{
  printf("\e[48;2;%d;%d;%dm", vermelho, verde, azul);
}


double t_relogio(void)
{
  struct timespec agora;
  clock_gettime(CLOCK_REALTIME, &agora);
  return agora.tv_sec + agora.tv_nsec*1e-9;
}

void t_cochila(float tempo)
{
  struct timespec t;
  t.tv_sec = tempo;
  t.tv_nsec = (tempo - t.tv_sec) * 1e9;
  nanosleep(&t, NULL);
}


static bool tem_tecla_guardada = false;
static char tecla_guardada;

bool t_tem_tecla()
{
  if (tem_tecla_guardada) return true;
  tem_tecla_guardada = (read(1, &tecla_guardada, 1) == 1);
  return tem_tecla_guardada;
}

char t_tecla()
{
  if (t_tem_tecla()) {
    tem_tecla_guardada = false;
    return tecla_guardada;
  }
  return '\0';
}
