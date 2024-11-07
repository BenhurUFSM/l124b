# t2 - n-rainhas

## parte I

Faça uma função que recebe um tabuleiro contendo rainhas e retorna um inteiro:
- `0` se o tabuleiro tem menos de *n* rainhas e não tem ameaça entre as rainhas existentes;
- `1` se existir ameaça entre quaisquer rainhas no tabuleiro;
- `2` se existirem *n* rainhas no tabuleiro, e não existir ameaças entre elas.

O tabuleiro está em um vetor de char, com cada caractere podendo ser '.' ou 'X' (posição livre ou ocupada por uma rainha); os primeiros *n* caracteres representam a primeira linha, os *n* caracteres seguintes a segunda e assim por diante.

A função deve suportar tabuleiro de qualquer tamanho. Para isso, recebe 2 argumentos: um inteiro com o tamanho do tabuleiro e um vetor de char que codifica o tabuleiro.
```c
  int n_rainhas(int n, char tab[]) { ... }
```

## parte II

Faça uma função para desenhar o tabuleiro.
A função deve receber o tamanho do tabuleiro e o vetor de char que o codifica.
Além disso, deve receber 2 inteiros que identificam a linha e coluna de uma posição no tabuleiro que deve ser desenhada em destaque. A primeira linha e coluna do tabuleiro são identificadas pelo valor *1*.

O tabuleiro deve ser desenhado como o de xadrez, com a cor de fundo alternando a cada posição.
A posição de destaque deve ser desenhada com uma terceira cor de fundo.
A borda do tabuleiro deve ter uma entre 3 cores, para representar o estado do tabuleiro de acordo com o retorno da função da parte I.

Use as funções nos arquivos `terminal.h` e `terminal.c`, que permitem posicionar o cursor e alterar a cor do que será escrito na tela.
O arquivo `terminal_exemplo.c` contém um programa que exemplifica o uso dessas funções.

```c
void desenha_tabuleiro(int n, char tab[], int lin, int col)
{
  t_cor_normal();
  t_limpa();
  //...
  t_atualiza();
}
```

## parte III

Faça uma função para realizar o processamento da entrada de uma tecla, da seguinte forma:
- se não houver tecla na entrada, não faz nada e retorna false;
- se a tecla for 'w', 'a', 's', 'd', incrementa ou decrementa a linha ou coluna do cursor, sem permitir que tenham valores fora de *1* a *n* e retorna false;
- se a tecla for enter ou espaço, altera o tabuleiro na posição do cursor, colocando uma rainha se não houver e retirando se houver e retorna false;
- se a tecla for 'x', retorna true;
- se a tecla for qualquer outra, não faz nada e retorna false.

```c
bool trata_teclado(int n, int tab[], int *ref_lin, int *ref_col)
{
  if (!t_tem_tecla()) return false;
  //...
}
```

## parte IV

Faça um programa, usando as funções anteriores, para permitir que o usuário preencha um tabuleiro. O programa deve encerrar quando o tabuleiro estiver corretamente preenchido ou quando a função da parte III retornar true. No primeiro caso, o programa deve felicitar o usuário e informar o tempo que ele levou para preencher o tabuleiro.

O tamanho do tabuleiro deve ser perguntado ao usuário no início da execução do programa.

A estrutura do programa deve ser algo como:
```c
  inicializa variáveis e terminal
  repete {
    trata_teclado
    desenha_tabuleiro
    verifica se deve terminar
  }
  parabeniza o usuário se for o caso
  finaliza o terminal
```

## parte V

Coloca um comentário na primeira linha do arquivo com o programa, contendo "l1-t2" e o nome do autor.
Muda o nome do arquivo para "l1-t2-*nome*.c" (substituindo *nome* por uma sequência de caracteres que permita identificar facilmente o autor na lista de chamada).
Anexa o arquivo em um email, que tem como assunto "entrega de l1-t2-*nome*", com *nome* como acima.
Envia o email para o endereço da disciplina, antes do encerramento do prazo.
