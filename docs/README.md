# Dijkstra Algorithm

## Problema

- Uma cidade com várias esquinas (numeradas de 1 a N)
- O quartel dos bombeiros está sempre na esquina #1
- As ruas são de mão única (só pode ir em uma direção)
- Cada rua tem um tempo para ser percorrida

## Objetivo

Encontrar o caminho mais rápido do quartel até o local do incêndio.

## Estruturas

### Street

Estrutura para armazenar as informações do custo de percorrer uma esquina (nó) de origem até uma outra de destino (rua ou aresta). Elas são especificadas em um arquivo de entrada `bombeiros.txt`.

```c
typedef struct {
    int origin;        
    int destination;
    int time;
} Street;
```

- `origin`: Esquina de origem
- `destination`: Esquina de destino
- `time`: Tempo estimado para ir da origem ao destino

### RouteInfo

Estrutura auxiliar para registrar as informações de cada tentativa de caminho percorrido pelo algoritmo até encontrar a solução (caminho de menor tempo até o local do incêndio) ou não houver caminhos possíveis.

```c
typedef struct {
    int times[MAX_CORNERS];        
    int previous[MAX_CORNERS];     
    int visited[MAX_CORNERS];      
} RouteInfo;
```
- `times`: Guarda o menor tempo encontrado até cada esquina
- `previous`: Guarda qual esquina veio antes (para reconstruir o caminho)
- `visited`: Marca quais esquinas já foram analisadas

## Algoritmo

1. Inicialização:
   - Tempo para esquina #1 (quartel) = 0
   - Tempo para todas outras esquinas = infinito
   - Nenhuma esquina foi visitada

2. Enquanto houver esquinas não visitadas:
   a. Encontre a esquina não visitada com menor tempo
   b. Marque essa esquina como visitada
   c. Para cada rua que sai dessa esquina:
      - Se podemos chegar em uma nova esquina em menos tempo
      - Atualizamos o tempo para essa nova esquina
      - Guardamos de onde viemos

3. No final:
   - Reconstruímos o caminho do destino até o quartel
   - Invertemos esse caminho para mostrar do quartel até o destino

### Exemplo

Caminhos (ruas) e o tempo para percorrer:
```
1 -> 2 (tempo: 5)
1 -> 3 (tempo: 2)
2 -> 4 (tempo: 1)
3 -> 4 (tempo: 3)
```

Início:
- Esquina 1: tempo = 0
- Outras esquinas: tempo = infinito

Primeira iteração (partindo da esquina 1):
- Analisa ruas saindo de 1
- Atualiza: esquina 2 = 5, **esquina 3 = 2**
  - `2` é o tempo para percorrer da esquina 1 até a esquina 3
  - `5` é o tempo para percorrer da esquina 1 até a esquina 2
  
  Nesse caso há duas ruas (caminhos) que podemos seguir de 1 -> 3 ou 1 -> 2. Primeiro vamos testar ir da esquina 1 -> 3 na próximo iteração e na 3º iteração vamos testar ir de 1 -> 2.

Segunda iteração (partindo da esquina 3, que tem menor tempo):
- Analisa ruas saindo de 3
- Atualiza: esquina 4 = 5 (2 + 3)
  - `2` é o tempo para percorrer da esquina 1 até a esquina 3
  - `3` é o tempo para percorrer da esquina 3 até a esquina 4
  - `5` é o tempo acumulado para percorrer da esquina 1 até a 4, passando pela esquina 3

Terceira iteração (partindo da esquina 2):
- Analisa ruas saindo de 2
- Atualiza: esquina 4 = 6 (5 + 1) [não muda pois já temos caminho mais rápido]
  - `5` é o tempo para percorrer da esquina 1 até a esquina 2
  - `1` é o tempo para percorrer da esquina 2 até a esquina 4
  - `6` é o tempo acumulado para percorrer da esquina 1 até a 4, passando pela esquina 2

## Considerações ao desenvolver o algoritmo

1. Sempre começar do quartel (esquina 1)
2. Só pode usar ruas na direção permitida (mão de via única)
3. O tempo total é a soma dos tempos de cada rua visitada
4. Sempre escolher a próxima esquina com menor tempo acumulado
5. Guardar o caminho para poder mostrar a rota completa
