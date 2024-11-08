#ifndef _janela_h_  // para evitar problemas com inclusão múltipla deste arquivo
#define _janela_h_

// janela.h
// ------
// funções de acesso à janela gráfica, mouse, relógio
// l124b

#include <stdbool.h>

// frequência de atualização
#define QUADROS_POR_SEGUNDO 30.0
#define SEGUNDOS_POR_QUADRO (1/QUADROS_POR_SEGUNDO)

// TIPOS DE DADOS

// um tamanho na janela, em pixels
typedef struct {
  float largura;
  float altura;
} tamanho_t;

// uma coordenada na janela, em pixels
typedef struct {
  float x;
  float y;
} ponto_t;

// um círculo, com ponto central e raio em pixels
typedef struct {
  ponto_t centro;
  float raio;
} circulo_t;

// um retângulo, com o ponto superior esquerdo e o tamanho, em pixels
typedef struct {
  ponto_t inicio;
  tamanho_t tamanho;
} retangulo_t;

// uma cor, com os componentes entre 0 e 1
typedef struct {
  float vermelho;
  float verde;
  float azul;
  float opacidade;
} cor_t;

// o estado do mouse
typedef struct {
  ponto_t posicao;  // onde está o mouse
  bool apertado[3]; // o estado de cada um dos 3 botões
  bool clicado[3];  // se cada botão foi solto desde a última leitura do estado
  int giro;         // quanto a rodela de rolagem girou desda a última leitura
} rato_t;

// CRIAÇÃO E DESTRUIÇÃO

// inicialização da janela
// cria uma janela com o tamanho dado em pixels
// deve ser executada antes do uso de qualquer outra função da janela
void t_inicializa(tamanho_t tamanho, char nome[]);


// finalização da janela
// deve ser chamada no final da utilização da janela, nenhuma outra função da
// janela deve ser chamada depois desta.
void j_finaliza(void);


// DESENHO

// desenha um círculo
void j_circulo(circulo_t circulo, float largura_linha, cor_t cor_linha, cor_t cor_interna);

// desenha uma linha reta
void j_linha(ponto_t inicio, ponto_t fim, float largura_linha, cor_t cor_linha);

// desenha um retângulo
void j_retangulo(retangulo_t retangulo, float largura_linha,
                    cor_t cor_linha, cor_t cor_interna);


// desenha texto
// o texto é desenhado à direita do ponto, centrado verticalmente
// tamanho é a altura aproximada de uma letra minúscula, em pixels
void j_texto(ponto_t posicao, int tamanho, cor_t cor, char texto[]);

// retorna o retângulo que contorna o texto
retangulo_t j_texto_contorno(ponto_t posicao, int tamanho, char texto[]);


// atualiza a janela
// faz com o que foi desenhado na janela desde a última atualização apareça.
// deve ser chamada ao final das funções de desenho
void j_atualiza();


// ACESSO AO RATO

// retorna o estado do rato
rato_t j_rato();


// ACESSO AO TECLADO

// retorna true se algo foi digitado e não lido
bool j_tem_tecla();

// retorna uma tecla digitada ou '\0' se nenhuma tecla for digitada
// se for digitado enter, retorna '\n'
// se for digitado backspace, retorna '\b'
int j_tecla();

// retorna o estado das teclas shift e control da última tecla (true se apertadas)
bool j_shift();
bool j_control();

// TEMPO

// retorna quantos segundos transcorreram desde algum momento no passado
double j_relogio();

// fica um tempo sem fazer nada
void j_cochila(double segundos);

#endif // _janela_h_
