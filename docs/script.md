# Script do Video

## Introdução

Olá! Hoje vamos analisar uma implementação do Algoritmo de Dijkstra em C, especificamente adaptada para encontrar a rota mais rápida para um caminhão de bombeiros chegar até um incêndio. 

Vamos entender como o código foi estruturado e as decisões tomadas durante sua implementação.

## 1. Estruturas de Dados

Primeiro, vamos analisar as estruturas fundamentais do código:

- A estrutura `Street` representa uma rua, conectando duas esquinas com um tempo de percurso

- A estrutura `RouteInfo` mantém três arrays essenciais:
  - `times[]`: armazena o menor tempo até cada esquina
  - `previous[]`: guarda o caminho percorrido
  - `visited[]`: controla quais esquinas já foram processadas

Estas estruturas foram escolhidas para facilitar o acesso às informações necessárias e otimizar a legibilidade e manutenção do código.

## 2. Inicialização

A função `initRouteInfo` prepara o estado inicial do algoritmo:

- Todos os tempos são inicializados com infinito (INT_MAX)
- Todos os `previous` são marcados como -1
- Nenhuma esquina é marcada como visitada
- A esquina inicial (posto dos bombeiros) recebe sempre tempo 0

Esta inicialização é fundamental para garantir o comportamento esperado do algoritmo durante a sua execução.

## 3. Encontrando a Próxima Esquina

A função `findMinTimeCorner` implementa uma parte fundamental do algoritmo:

- Percorre todas as esquinas não visitadas
- Encontra aquela com menor tempo acumulado
- Este processo garante que sempre expandimos pelo caminho mais promissor
- Caso não haja mais esquinas alcançáveis, é retornado -1

## 4. O Coração do Algoritmo 

A função `findFastestRoute` implementa a essência do algoritmo de Dijkstra:

1. Para cada esquina no conjunto de ruas:
   - Seleciona a esquina não visitada com menor tempo
   - Marca como visitada
   - Atualiza os tempos das esquinas vizinhas a partir da soma dos tempos das esquinas anteriores ao ponto em questão
   
2. A atualização só ocorre se:
   - A esquina destino não foi visitada
   - Existe um caminho válido até a esquina atual
   - O novo caminho é mais rápido que o anterior

Este processo garante que sempre encontramos o caminho mais rápido.

## 5. Reconstrução e Impressão da Rota

A função `printRoute` reconstrói e exibe o caminho encontrado:

- Usa o array `previous` para reconstruir o caminho do fim para o início
- Armazena temporariamente o caminho invertido
- Imprime na ordem correta (do início ao fim)
- Mostra o tempo total calculado

## Conclusão

Esta implementação é eficiente principalmente porque:
- Utiliza arrays estáticos ao invés de grafos para facilitar o entendimento do algoritmo
- Código organizado ao separar claramente as responsabilidades entre as funções

O resultado é um código eficiente e de fácil compreensão para encontrar a rota mais rápida em uma situação de emergência.
