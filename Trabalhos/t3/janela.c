// janela.c
// ------
// implementação das funções de acesso à janela gráfica, mouse, relógio
//   usando allegro
// l124b

// inclui as definicoes
#include "janela.h"

// includes normais
#include <stdio.h>
#include <assert.h>

// includes do allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// variáveis globais

static struct {
  // estado do teclado
  bool shift;
  bool control;
  int tecla_guardada;
  // fila para receber os eventos do teclado
  ALLEGRO_EVENT_QUEUE *eventos_teclado;
} glob;

// funções auxiliares

// abandona o programa com erro
static void cai_fora(char *msg)
{
  int cai = 42;
  int fora = 42;
  fprintf(stderr, "\n\nERRO FATAL\n%s\n\n", msg);
  assert(cai-fora);
}

static void j_inicializa_janela(tamanho_t tamanho, char nome[])
{
  // pede para tentar linhas mais suaves (multisampling)
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  // cria uma janela
  ALLEGRO_DISPLAY *janela = al_create_display(tamanho.largura, tamanho.altura);
  if (janela == NULL) {
    cai_fora("problema na criação de janela do allegro");
  }
  // esconde o cursor do mouse
  al_hide_mouse_cursor(janela);
  al_set_window_title(janela, nome);
}

static ALLEGRO_COLOR conv_cor(cor_t cor)
{
  return (ALLEGRO_COLOR){cor.vermelho, cor.verde, cor.azul, cor.opacidade};
}

static void j_inicializa_teclado(void)
{
  if (!al_install_keyboard()) {
    cai_fora("problema na inicialização do teclado do allegro");
  }
  // cria e inicializa a fila de eventos do teclado
  glob.eventos_teclado = al_create_event_queue();
  if (glob.eventos_teclado == NULL) {
    cai_fora("problema na criação da fila de eventos do teclado do allegro");
  }
  al_register_event_source(glob.eventos_teclado,
                           al_get_keyboard_event_source());
}

void t_inicializa(tamanho_t tamanho, char nome[])
{
  // inicializa os subsistemas do allegro
  if (!al_init()) cai_fora("problema na inicialização do allegro");
  if (!al_install_mouse()) cai_fora("problema na inicialização do mouse do allegro");
  if (!al_init_primitives_addon()) cai_fora("problema na inicialização de addons do allegro");
  al_init_font_addon();
  if (!al_init_ttf_addon()) cai_fora("problema na inicialização do addon de fontes ttf");

  // inicializa a janela
  j_inicializa_janela(tamanho, nome);
  j_inicializa_teclado();
}


void j_finaliza(void)
{
  // badabum!
  al_uninstall_system();
}

void j_atualiza(void)
{
  static double tempo_ultima_atualizacao = 0;
  double agora = j_relogio();
  double quando_mostrar = tempo_ultima_atualizacao + SEGUNDOS_POR_QUADRO;
  double tempo_ate_mostrar = quando_mostrar - agora;
  if (tempo_ate_mostrar > 0) {
    // é muito cedo, dá uma cochilada
    j_cochila(tempo_ate_mostrar);
  }
  // troca a janela mostrada pela que foi desenhada em memória
  al_flip_display();
  tempo_ultima_atualizacao = j_relogio();

  // limpa todo o canvas em memória, para desenhar a próxima janela
  cor_t preto = { 0, 0, 0, 1 };
  al_clear_to_color(conv_cor(preto));
}


void j_circulo(circulo_t circulo, float largura, cor_t cor_linha, cor_t cor_interna)
{
  // preenche
  al_draw_filled_circle(circulo.centro.x, circulo.centro.y, circulo.raio,
                        conv_cor(cor_interna));
  // faz o contorno
  if (largura > 0) {
    al_draw_circle(circulo.centro.x, circulo.centro.y, circulo.raio,
                   conv_cor(cor_linha), largura);
  }
}

void j_linha(ponto_t inicio, ponto_t fim, float largura, cor_t cor_linha)
{
  al_draw_line(inicio.x, inicio.y, fim.x, fim.y, conv_cor(cor_linha), largura);
}

void j_retangulo(retangulo_t retangulo, float largura,
                    cor_t cor_linha, cor_t cor_interna)
{
  int x1 = retangulo.inicio.x;
  int y1 = retangulo.inicio.y;
  int x2 = retangulo.inicio.x + retangulo.tamanho.largura;
  int y2 = retangulo.inicio.y + retangulo.tamanho.altura;
  al_draw_filled_rectangle(x1, y1, x2, y2, conv_cor(cor_interna));
  if (largura > 0) {
    al_draw_rectangle(x1, y1, x2, y2, conv_cor(cor_linha), largura);
  }
}

// retorna uma fonte com o tamanho pedido
#define N_FONTES 5  // número de fontes a guardar
static ALLEGRO_FONT *j_fonte(int tam)
{
  static struct {
    int tamanho;
    ALLEGRO_FONT *fonte;
  } fontes[N_FONTES] = { { 0, NULL } };
  static int prox_indice = 0;

  for (int i = 0; i < N_FONTES; i++) {
    if (fontes[i].tamanho == tam) return fontes[i].fonte;
  } 

  // carrega uma fonte, para poder escrever na janela
  ALLEGRO_FONT *fonte = al_load_font("DejaVuSans.ttf", tam, 0);
  if (fonte == NULL) {
    al_uninstall_system();
    cai_fora("A carga do arquivo de caracteres não deu certo na função j_fonte.\n"
             "A função j_inicializa foi chamada?\n"
             "O arquivo .ttf está no diretório corrente?\n");
  }

  // se ja tinha uma fonte carregada, livra-se dela antes de carregar outra
  if (fontes[prox_indice].fonte != NULL) {
    al_destroy_font(fontes[prox_indice].fonte);
  }
  fontes[prox_indice].fonte = fonte;
  fontes[prox_indice].tamanho = tam;
  prox_indice++;
  if (prox_indice >= N_FONTES) {
    prox_indice = 0;
  }

  return fonte;
}

void j_texto(ponto_t posicao, int tamanho, cor_t cor, char texto[])
{
  ALLEGRO_FONT *fonte = j_fonte(tamanho);
  posicao.y -= al_get_font_ascent(fonte);
  al_draw_text(fonte, conv_cor(cor), posicao.x, posicao.y, ALLEGRO_ALIGN_LEFT, texto);
}

retangulo_t j_texto_contorno(ponto_t posicao, int tamanho, char texto[])
{
  ALLEGRO_FONT *fonte = j_fonte(tamanho);
  retangulo_t ret;
  int rx, ry, rw, rh;
  al_get_text_dimensions(fonte, texto, &rx, &ry, &rw, &rh);
  ret.inicio.x = posicao.x + rx;
  ret.inicio.y = posicao.y + ry - al_get_font_ascent(fonte);
  ret.tamanho.largura = rw;
  ret.tamanho.altura = rh;
  return ret;
}

rato_t j_rato()
{
  ALLEGRO_MOUSE_STATE mouse;
  rato_t rato;
  al_get_mouse_state(&mouse);
  rato.posicao.x = al_get_mouse_state_axis(&mouse, 0);
  rato.posicao.y = al_get_mouse_state_axis(&mouse, 1);

  static int ultimo_giro = INT_MAX;
  int giro = al_get_mouse_state_axis(&mouse, 2);
  if (ultimo_giro == INT_MAX) ultimo_giro = giro;
  rato.giro = ultimo_giro - giro;
  ultimo_giro = giro;
  
  static bool ultimo_apertado[3] = { false, false, false };
  for (int b = 0; b < 3; b++) {
    rato.apertado[b] = al_mouse_button_down(&mouse, b + 1);
    rato.clicado[b] = ultimo_apertado[b] && !rato.apertado[b];
    ultimo_apertado[b] = rato.apertado[b];
  }

  return rato;
}

static void ve_se_tem_tecla()
{
  ALLEGRO_EVENT ev;

  while (glob.tecla_guardada == '\0' && al_get_next_event(glob.eventos_teclado, &ev)) {
    glob.shift = ev.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
    glob.control = ev.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
      int k = ev.keyboard.keycode;
      switch (k) {
        case ALLEGRO_KEY_ENTER:
          glob.tecla_guardada = '\n';
          break;
        case ALLEGRO_KEY_BACKSPACE:
          glob.tecla_guardada = '\b';
          break;
        default:
          glob.tecla_guardada = ev.keyboard.unichar;
          break;
      }
    }
  }
}

bool j_shift()
{
  return glob.shift;
}

bool j_control()
{
  return glob.control;
}

bool j_tem_tecla()
{
  ve_se_tem_tecla();
  return glob.tecla_guardada != '\0';
}

int j_tecla()
{
  int tec = '\0';
  if (j_tem_tecla()) {
    tec = glob.tecla_guardada;
    glob.tecla_guardada = '\0';
  }
  return tec;
}


double j_relogio(void)
{
  return al_get_time();
}

void j_cochila(double segundos)
{
  al_rest(segundos);
}
