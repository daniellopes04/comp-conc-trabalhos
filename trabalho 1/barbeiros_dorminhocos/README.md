Barbeiros Dorminhocos
=====================

Neste problema, temos uma barbearia com apenas um barbeiro, uma sala de corte contendo apenas uma cadeira e uma sala de espera com um número n de cadeiras. Após cortar o cabelo de um cliente, o barbeiro checa a sala de espera para ver se existem outros clientes esperando por um corte. Caso haja um ou mais clientes, o barbeiro leva um deles para a cadeira na sala de corte e corta o seu cabelo. Caso não hajam clientes esperando, o barbeiro dorme na cadeira na sala de corte.
Ao chegar à barbearia, cada cliente checa a sala de corte para ver o que o barbeiro está fazendo. Caso o barbeiro esteja dormindo, o cliente o acorda e se senta na cadeira para ter seu cabelo cortado. Caso o barbeiro já esteja com outro cliente na cadeira, o cliente vai para a sala de espera. Na sala de espera o cliente verifica as cadeiras. Caso haja pelo menos uma cadeira vaga, o cliente se senta para esperar a sua vez de ter o cabelo cortado. Se não houverem cadeiras vagas, o cliente vai embora.
O problema consiste em manter a barbearia funcionando corretamente a partir das regras citadas acima, com o barbeiro atendendo aos clientes até que a sala de espera esteja vazia e dormindo na sala de corte até que um novo cliente chegue.

Solução
-------

A solução presente aqui faz uso de exclusão mútua para impedir que o barbeiro e um ou mais clientes acessem a sala de espera ao mesmo tempo. Além disso, a sala de espera é implementada de forma a simular uma fila, de maneira que a ordem em que os clientes cheguem seja a mesma ordem em que são atendidos. Um problema é que por conta disso, uma parte grande do código fica na área de exclusão mútua, o que diminui a performance ao se utilizar multiplos processadores.
