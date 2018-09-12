## Descrição

O problema consiste em 3 fumantes que se sentam ao redor de uma mesa. Assumimos então que são necessários apenas 3 ingredientes para se fazer e fumar um cigarro, sendo eles: tabaco, papel e fósforos. Cada um dos fumantes possui um estoque infinito de um dos ingredientes, mas não possui os outros dois.

Existe um quarto agente não-fumante que permite que os fumantes façam seus cigarros. Ele faz isso selecionando arbitrariamente dois dos ingredientes para serem colocados na mesa. O fumante cujo ingrediente não foi selecionado pode então preparar um cigarro usando os ingredientes colocados na mesa e o seu próprio. Após preparar e fumar o cigarro, os ingredientes são devolvidos aos seus donos e o agente não-fumante seleciona novamente dois ingredientes arbitrariamente. Esse processo então continua indefinidamente.

### Solução

A solução do problema requer certa atenção para evitar deadlocks. Como cada fumante espera dois ingredientes, se, quando o agente distribuir, dois fumantes diferentes pegarem cada um um ingrediente, o programa estará em deadlock. Por isso, quando um ingrediente é obito, mas o outro está travado, o fumante deve soltar o ingrediente que pegou para que o outro posso utilizá-lo. Devido à maneira como o agente distribui os ingredientes, não foram encontrados problemas de starvation.
