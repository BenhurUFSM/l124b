## t4 - números

***Esta descrição está incompleta***

Fazer um programa que implementa um jogo semelhante a [numbers](https://poki.com/en/g/numbers), como descrito a seguir.
O programa deve usar as funções de `janela.[ch]` do t3.

### Descrição do jogo

O jogo se desenvolve em um tabuleiro com 12 linhas de nove casas cada.
Cada casa pode estar vazia ou ocupada por um número entre 1 e 9.
Uma jogada consiste em escolher 2 casas ocupadas para que sejam esvaziadas, conforme as regras do jogo.
O objetivo é esvaziar o tabuleiro inteiro.

A escolha de duas casas é válida se elas forem "vizinhas" e se contiverem dois números iguais ou dois números cuja soma seja 10.
Duas casas são consideradas "vizinhas" se:
- estiverem na mesma linha e não houver casa ocupada entre elas (podem existir casas vazias);
- estiverem na mesma coluna e não houver casa ocupada entre elas;
- estiverem na mesma diagonal e não houver casa ocupada entre elas;
- uma for a última casa ocupada de uma linha e a outra a primeira casa ocupada da linha imediatamente seguinte;
- uma for a última casa ocupada da última linha e a outra a primeira casa ocupada da primeira linha que tem alguma casa ocupada.

Quando todas as casas de uma linha forem esvaziadas, essa linha é apagada (as linhas acima dela descem e surge uma nova linha em branco no topo).

O jogador pode 
