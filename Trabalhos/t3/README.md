## t3 - n-rainhas - versão com tela gráfica

Você deve reaproveitar algumas funções do t1 para reimplementar o programa das n-rainhas, desta vez usando uma tela gráfica em substituição à tela textual.

A representação de um tabuleiro deve continuar a mesma do t1.
A função de verificação de ameaças deve continuar a mesma do t1.
A função de desenho da tela deve ser substituída para usar as funções gráficas fornecidas.
Deve ser feita uma nova função, para o tratamento do mouse.
O tamanho do tabuleiro deve ser obtido como argumento do main (olha no texto da aula 19).

## parte I

Para a implementação, você deve usar as funções de acesso à tela gráfica fornecidas em janela.h e janela.c. Tem um exemplo de uso dessas funções em exemplo_janela.c, com um comentário no início de como compilar.
Você precisa ter a biblioteca allegro5 instalada e acessível.

Faça funcionar o programa exemplo_janela em seu ambiente.

## parte II

Faça uma função para o desenho do tabuleiro.
Ela deve receber os mesmos argumentos da função semelhante do t1.
O tabuleiro deve ser desenhado no centro da janela.
O tabuleiro deve ter um contorno em cor que corresponde ao estado (sem ameaça, com ameaça, completo).
O tabuleiro deve desenhar de forma destacada a casa na linha e coluna que recebe como argumento.
A linha e coluna recebidas podem ser fora do tabuleiro (-1, por exemplo), o que indica que nenhuma casa deve ser desenhada de forma destacada.

Faça uma função para desenhar uma região na tela que serve para desistir do jogo quando clicada.

Faça uma função que desenha o tempo de jogo em algum local da janela.

Faça também uma função para desenhar algo na posição do mouse.

Faça uma função para desenhar a janela, que usa essas funções todas.

## parte III

Faça uma função que implementa o processamento do mouse.

Se o primeiro botão do mouse for clicado em uma posição da janela que corresponde a uma casa do tabuleiro, o valor dessa posição deve ser trocado (se tiver uma rainha deixa de ter, se não tiver passa a ter).

A função deve também identificar se o clique aconteceu com o mouse em cima da região de desistência.

Se o botão for clicado em outra posição ou se não for clicado, a função não altera o tabuleiro.

A função deve retornar true se detectou um clique na região de desistência e false caso contrário.

## parte IV

Faça um programa, usando as funções anteriores, para permitir que o usuário preencha um tabuleiro. O programa deve encerrar quando o tabuleiro estiver corretamente preenchido ou quando o usuário desistir. No primeiro caso, o programa deve felicitar o usuário e informar o tempo que ele levou para preencher o tabuleiro.


A estrutura do programa deve ser algo como:
```c
  inicializa variáveis e janela
  repete {
    trata_entrada
    desenha_janela
    verifica se deve terminar
  }
  parabeniza o usuário se for o caso
  finaliza o janela
```

## parte V

Coloca um comentário na primeira linha do arquivo com o programa, contendo "l1-t3" e o nome do autor.
Muda o nome do arquivo para "l1-t3-*nome*.c" (substituindo *nome* por uma sequência de caracteres que permita identificar facilmente o autor na lista de chamada).
Anexa o arquivo em um email, que tem como assunto "entrega de l1-t3-*nome*", com *nome* como acima.
Envia o email para o endereço da disciplina, antes do encerramento do prazo.

* * *

**Sugestão**: tanto o desenho quanto o processamento do mouse serão mais fáceis de implementar se houver uma função que traduz coordenadas do mouse em coordenadas da janela e outra para o contrário.

A representação interna do tabuleiro pode ser feita com uma matriz, em vez de um vetor. A interface das funções que recebem o tabuleiro como um vetor devem ser alteradas nesse caso para receberem uma matriz. Não recomendo fazer isso e sim aproveitar o código do trabalho anterior.
