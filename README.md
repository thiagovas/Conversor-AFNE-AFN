Conversor-AFNE-AFN
==================

Conversor que pega um autômato finito não-determinístico estendido(AFNE ou também conhecido como AFN-lambda) e transforma em um autômato finito não-determinístico(AFN).

Exemplo de input:

1 2 3 ; // estados do AFNE 0 1 ; // alfabeto reconhecido pelo automato

// Cada linha representa uma transição.

// Para cada transição temos a origem e o destino da transição e sobre qual palavra a transição é feita.

// - ’v’ representa a palavra vazia.

1 2 v ; // Transição de 1 para 2 sobre a palavra vazia

2 2 00 ; // Transição de 2 para 2 sobre a palavra 00

2 2 01 ;

1 3 1 ;

3 3 11 ;

3 3 10 ;

; // indica o final das transições

1 ; // estados iniciais

2 3 ; // estados finais

0000 00000 010101 1111 11111 1101011 ; // palavras a serem verificadas

Os comentários no input devem ser ignorados, coloquei eles aqui somente com o intuito de explicar o que significa cada linha do input.
