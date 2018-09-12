Filósofos Jantando
=====================


Solução
-------

A solução foi baseada no método de hierarquia de recursos. Assim, cada filósofo pegará o garfo de maior número, entre os garfos à sua direita e à sua esquerda, primeiro, e só pegara o outro depois de ter consigo pegar o primeiro. Dessa forma, ambos os filósofos 1 e 5 tentarão pegar primeiro o garfo de número 5. Assim, será impossível que todos os filosófos tenham, ao mesmo tempo, um único garfo (a não ser que tenham acabado de comer e estejam esperando para depositá-lo na mesa). Dessa forma, o deadlock é evitado. A sincronia entre os filósofos também é evitada, evitando assim problemas de starvation.
