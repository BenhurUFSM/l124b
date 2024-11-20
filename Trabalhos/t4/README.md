## t4 - números

Fazer um programa que implementa um jogo semelhante a [numbers](https://poki.com/en/g/numbers), como descrito a seguir.
O programa deve usar as funções de `janela.[ch]` do t3.

### Descrição do jogo

O jogo se desenvolve em um tabuleiro com 12 linhas de nove casas cada.
Cada casa pode estar:
- **ocupada**, contém um número entre 1 e 9;
- **vazia**, continha um número, que foi removido; ou
- **nova**, nunca foi ocupada.

O jogo inicia com algumas casas ocupadas, outras novas.
Uma jogada consiste em escolher 2 casas ocupadas para que sejam esvaziadas, conforme as regras do jogo.
O objetivo é esvaziar o tabuleiro inteiro.

A escolha de duas casas para serem esvaziadas só é válida se as casas forem "vizinhas" e se contiverem dois números iguais ou dois números cuja soma seja 10.
Duas casas são consideradas "vizinhas" se:
- estiverem na mesma linha e não houver casa ocupada entre elas (podem existir casas vazias ou novas);
- estiverem na mesma coluna e não houver casa ocupada entre elas;
- estiverem na mesma diagonal e não houver casa ocupada entre elas;
- uma for a última casa ocupada (a mais à direita) de uma linha e a outra a primeira casa ocupada da linha imediatamente seguinte;
- uma for a última casa ocupada da última linha e a outra a primeira casa ocupada da primeira linha que tem alguma casa ocupada.

Quando todas as casas ocupadas de uma linha forem esvaziadas, essa linha é apagada (as linhas acima dela descem e surge uma nova linha com casas novas no topo).

O jogador pode ainda fazer uma jogada de repovoamento, tipicamenta quando não tem mais jogadas válidas no tabuleiro. Com essa jogada, as casas ocupadas são duplicadas. O valor da última casa ocupada é colocado na última casa nova, o da penúltima casa ocupada na penúltima casa nova e assim sucessivamente. Caso não tenha um número suficiente de casas novas, o jogador perde a partida.
Exemplo (`v` representa uma casa vazia, `n` uma casa nova; o tabuleiro é bem menor que o real):
```
antes:
  n n n n n
  n n v 1 7
  v 4 v 8 v
depois:
  n n n 1 7
  4 8 v 1 7
  v 4 v 8 v
```

### Pontuação

Cada jogada bem sucedida vale 9 pontos.
Cada linha removida vale 109 pontos.

### Como jogar uma partida

Inicialmente, não há uma casa "selecionada".
O jogador clica com o mouse em alguma região da tela, que pode ser:
- a região que representa desistência da partida -- a partida é encerrada;
- a região que representa o repovoamento -- é realizada a operação de repovoamento;
- sobre uma casa ocupada. Se não houver casa "selecionada", a casa clicada passa a ser "selecionada".
Se já houver casa "selecionada" e as duas casas constituirem uma jogada válida a jogada é realizada e não há mais casa "selecionada". Se a jogada não for válida, a última casa clicada passa a ser a casa "selecionada".
- sobre qualquer outra região, o clique é ignorado.

Quando a jogada for válida:
- as duas casas são esvaziadas;
- acumula pontos;
- se alguma linha for esvaziada, deve ser removida, uma nova linha com casas novas inserida no topo, e mais pontos acumulados;
- se o tabuleiro ficar vazio, o partida é encerrada.

### Inicialização de uma partida

A metade inferior do tabuleiro (últimas 6 linhas) é preenchida com números aleatórios entre 1 e 9, o restante do tabuleiro contém casas novas. Nenhuma casa é "selecionada".

### Desenho da tela durante uma partida

A tela deve conter o tabuleiro, no qual deve ser possível identificar as casas novas, vazias e ocupadas.
A casa "selecionada", se houver, deve ser distinguível.
Devem ser visíveis as regiões para abandono e repovoamento.
Caso não haja jogada possível, essa situação deve também ser identificada visualmente.
O número de pontos deve ser mostrado.

Nas casas ocupadas, devem ser usadas cores distintas para os números que somam 10 (1 e 9 têm a mesma cor, 2 e 8 têm outra cor, etc.)

### Recordes

O programa deve manter as 10 maiores pontuações em um arquivo.
Ao final de uma partida, o programa deve mostrar essas pontuações juntamente com a pontuação atual, e atualizar a lista cado a pontuação atual esteja entre as 10 maiores.

O programa não deve acusar erro caso o arquivo de pontuações não exista.

Não é necessário o nome do jogador no arquivo de pontuações, só o número de pontos.

A tela de apresentação das maiores pontuações deve oferecer a opção de encerramento do programa ou de jogar outra partida.

### Organização do código

O programa deve ser modularizado, com funções que têm objetivo bem definido.

Uma função não deve ser muito longa. 30 linhas é muito longa.

Uma função não deve ter muitos níveis de indentação.

Deve ter pelo menos uma função para o desenho (e só o desenho) de cada tela, e para o processamento de entrada para cada tela. Essas funções podem (devem?) usar subfunções para partes do que têm que fazer (desenho só do tabuleiro, desenho de uma casa, por exemplo).

Os dados necessários para uma partida devem ser colocados em uma struct. As funções principais, pelo menos (inicialização de uma partida, desenho da tela principal de jogo, processamento de entrada durante uma partida), devem receber um ponteiro para essa estrutura como argumento.

O programa não deve usar variáveis globais.

A formatação do programa deve ser coerente (usar sempre a mesma forma de indentação e colocação dos elementos de organização do código). Deve ser usada a indentação para sinalizar o nível de dependência entre os comandos.
Por exemplo, se um comando for formatado assim:
```c
  if (a < j) {
    printf("a é menor!");
  }
```
não formata outro assim:
```c
  if(v>x)
  {
      printf ("x é menor");
  }
```
e vice-versa.

### Sugestões

- mantenha em memória um vetor com as 10 maiores pontuações (não esqueça que podem existir menos de 10)
- faça uma função para inicializar esse vetor. Se houver arquivo, inicializa a partir do arquivo, se não, inicializa como vazio. Chama essa função uma vez no início do programa.
- quando terminar uma partida, verifica se precisa atualizar o vetor (porque a pontuação foi suficiente), e se for o caso, grava o arquivo.
