# **Trabalho Final - Classificação e Pesquisa de Dados (INF01124)**
## **Descrição**
O trabalho consiste na implementação de certas estruturas de dados vistas em aulas para auxiliar e agilizar a pesquisa de jogadores dentro do dataset do FIFA 21, [aqui disponível](https://www.kaggle.com/stefanoleone992/fifa-21-complete-player-dataset). O código foi feito por @neitaans e @jvhendrix, inteiramente na linguagem C++, levando aproximadamente 40 segundos para construir todas as estruturas.

Como entrada, o código recebe 3 arquivos do dataset, sendo eles:

1. `players.csv`: contém as informações sobre o ID, nome completo e posições de cada um dos quase 19 mil jogadores contidos no jogo;
2. `rating.csv`: contém 24 milhões de avaliações de usuários, que podem atribuir uma nota de 0 a 5 para um jogador específico do jogo. Como este arquivo é muito pesado para o GitHub, ele não está disponível no repositório, mas pode ser baixado no site do dataset;
3. `tags.csv`: contém 360 mil características atribuídas aos jogadores do jogo, para caracterizá-los.

## **Pesquisas**

### 1. Pesquisa por nome do jogador

- Sintaxe e modo de uso: `player <nome do jogador>` ou `player <iniciais do nome>`.
- Retorno: lista com todos os jogadores cujo nome se iniciam com o argumento passado.
- Exemplo:

```
> player Cristiano

---------------------------------------------------------------------------------------------------
| Player ID | Full Name                                        | Positions     | Rating  | Count  |
---------------------------------------------------------------------------------------------------
|    201389 | Cristiano Biraghi                                | LM, LB        |    2.81 |   1588 |
|    205068 | Cristiano Pereira Figueiredo                     | GK            |    2.60 |   1205 |
|    201939 | Cristiano Piccini                                | RB            |    2.86 |   1650 |
|     20801 | Cristiano Ronaldo dos Santos Aveiro              | ST, LW        |    4.25 |  11144 |
|    207722 | Cristiano da Silva                               | LM, ST, LW    |    2.74 |   1427 |
---------------------------------------------------------------------------------------------------
```

### 2. Pesquisa por sobrenome do jogador

- Sintaxe e modo de uso: `surname <sobrenome do jogador>` ou `surname <iniciais do sobrenome>`.
- Retorno: lista com todos os jogadores que tenham pelo menos um dos sobrenomes se iniciando com o argumento passado.
- Exemplo:

```
> surname Messi

---------------------------------------------------------------------------------------------------
| Player ID | Full Name                                        | Positions     | Rating  | Count  |
---------------------------------------------------------------------------------------------------
|    202350 | Fabricio dos Santos Messias                      | CF, ST        |    2.68 |   1519 |
|    240938 | Junior Messias                                   | CF, ST        |    2.48 |    701 |
|    233774 | Alexis Nahuel Messidoro                          | CAM, RM       |    2.57 |   1386 |
|    236341 | Nicolas Ariel Messiniti                          | ST            |    2.54 |    743 |
|    158023 | Lionel Andres Messi Cuccittini                   | RW, ST, CF    |    4.26 |  12887 |
---------------------------------------------------------------------------------------------------
```

### 3. Pesquisa por avaliação de usuário

- Sintaxe e modo de uso: `user <Número do usuário>`.
- Retorno: lista com os 20 jogadores mais bem avaliados pelo dado usuário.
- Exemplo:

```
> user 2469

-----------------------------------------------------------------------------------------------------
| User ID | Full Name                                        | Global Rating | Count | User Rating  |
-----------------------------------------------------------------------------------------------------
|  172871 | Jan Bert Lieve Vertonghen                        |          3.71 |  7040 |         5.00 |
|  182521 | Toni Kroos                                       |          4.02 | 10184 |         5.00 |
|  211688 | Jose Luis Gaya Pena                              |          3.49 |  4894 |         5.00 |
|  205569 | James Ward-Prowse                                |          3.37 |  5221 |         5.00 |
|  168542 | David Josue Jimenez Silva                        |          3.99 |  8717 |         5.00 |
|  178603 | Mats Hummels                                     |          3.98 | 11787 |         5.00 |
|  193082 | Juan Guillermo Cuadrado Bello                    |          3.66 |  5013 |         5.00 |
|  183907 | Jerome Boateng                                   |          3.92 | 12164 |         5.00 |
|  200888 | Danilo Luis Helio Pereira                        |          3.67 |  8673 |         5.00 |
|  189509 | Thiago Alcantara do Nascimento                   |          3.75 |  4242 |         4.50 |
|  176009 | Sven Kums                                        |          3.14 |  3427 |         4.50 |
|  193847 | Osmar Ibanez Barba                               |          3.15 |  4301 |         4.50 |
|  159171 | Jose Manuel Jurado Marin                         |          2.98 |  5068 |         4.50 |
|  202652 | Raheem Shaquille Sterling                        |          3.85 |  9643 |         4.50 |
|  216201 | Inaki Williams Arthuer                           |          3.40 |  4934 |         4.50 |
|  197655 | Sebastian Coates Nion                            |          3.64 |  8554 |         4.50 |
|  205175 | Arkadiusz Milik                                  |          3.69 |  8349 |         4.50 |
|  213400 | Diego Sebastian Laxalt Suarez                    |          3.22 |  5146 |         4.50 |
|  207664 | Carlos Arturo Bacca Ahumada                      |          3.53 |  8974 |         4.50 |
|  209658 | Leon Goretzka                                    |          3.76 |  8973 |         4.00 |
-----------------------------------------------------------------------------------------------------
```

### 4. Pesquisa por melhores jogadores

- Sintaxe e modo de uso: `top<N> '<posição do jogador>'`.
- Retorno: lista com os `N` melhores jogadores para a dada posição, ordenados pelas suas médias de avaliações.
- Exemplo:

```
> top5 'GK'

---------------------------------------------------------------------------------------------------
| Player ID | Full Name                                        | Positions     | Rating  | Count  |
---------------------------------------------------------------------------------------------------
|    167495 | Manuel Neuer                                     | GK            |    4.21 |   8017 |
|    192119 | Thibaut Courtois                                 | GK            |    4.07 |   9996 |
|    167948 | Hugo Lloris                                      | GK            |    4.00 |  13895 |
|    193080 | David De Gea Quintana                            | GK            |    3.99 |  12873 |
|      1179 | Gianluigi Buffon                                 | GK            |    3.90 |  11980 |
---------------------------------------------------------------------------------------------------
```

### 5. Pesquisa por piores jogadores

- Sintaxe e modo de uso: `bottom<N> '<posição do jogador>'`.
- Retorno: lista com os `N` piores jogadores para a dada posição, ordenados pelas suas médias de avaliações.
- Exemplo:

```
> bottom5 'GK'

---------------------------------------------------------------------------------------------------
| Player ID | Full Name                                        | Positions     | Rating  | Count  |
---------------------------------------------------------------------------------------------------
|    250978 | Ma Zhen                                          | GK            |    1.98 |   1854 |
|    243073 | Teng Shangkun                                    | GK            |    1.99 |   1797 |
|    252519 | Li Xuebo                                         | GK            |    2.04 |   1396 |
|    255986 | Patrick McGarvey                                 | GK            |    2.07 |   1432 |
|    247524 | Daniel Enrique Retamal Vargas                    | GK            |    2.09 |   1220 |
---------------------------------------------------------------------------------------------------
```

### 6. Pesquisa por tags de jogadores

- Sintaxe e modo de uso: `tags '<tag1>' '<tag2>' ... '<tagN>'`.
- Retorno: lista com a intersecção de jogadores que contenham todas as dadas tags.
- Exemplo:

```
> tags 'Brazil' 'Manchester City'

---------------------------------------------------------------------------------------------------
| Player ID | Full Name                                        | Positions     | Rating  | Count  |
---------------------------------------------------------------------------------------------------
|    135507 | Fernando Luiz Rosa                               | CB, CDM       |    3.72 |   6402 |
|    210257 | Ederson Santana de Moraes                        | GK            |    3.60 |   3346 |
|    230666 | Gabriel Fernando de Jesus                        | ST            |    3.48 |   4340 |
---------------------------------------------------------------------------------------------------
```

## **Estruturas de dados utilizadas**

Para a realização da função de pesquisa `player`, foi montada uma **Árvore Trie**, que armazena o nome completo de todos os jogadores e guarda seus IDs nas folhas. Juntamente à árvore, foi necessária a implementação de uma **Tabela Hash**, que armazena todos os dados satélites dos jogadores e que usa como chave de pesquisa o ID do jogador. Assim, primeiro o nome dado é pesquisado dentro da árvore, retornando o ID do jogador. Este ID é usado na tabela para se obter os demais dados que serão impressos na tela.

Na função `surname`, também montamos uma **Árvore Trie**, que contém todos os sobrenomes existentes no jogo. Diferentemente da árvore da primeira pesquisa, suas folhas armazenam um vetor de IDs pois mais de um jogador pode conter o mesmo sobrenome. Assim, se pesquisa na árvore o sobrenome dado, e é retornado uma lista com todos os IDs de jogadores que contém esse nome. De forma análoga, os IDs são utilizados para fazer uma busca na mesma tabela da função `player`, afim de se imprimir os dados satélites.

Já na função `user`, uma estratégia semelhante foi utilizada. Foi criada um **Tabela Hash** que utiliza como chave o número do usuário, e que armazena os dados satélites daquele usuário: os jogadores que ele avaliou e a nota que lhes foi dada. Portanto, assim que a pesquisa recebe o número do usuário, é feita uma busca na tabela, que retorna e imprime todos os daddos do usuário dado.

Na função `top` e `bottom`, criamos outra **Tabela Hash** que separa todos os jogadores em suas devidas posições. Portanto, a chave da tabela é justamente a posição do jogador. Assim, conseguimos vetores que contém dentro de si todos os jogadores para cada posição do jogo. Mas, antes de imprimir os dados, o vetor da posição dada é ordenado conforme a avaliação média dos jogadores, e seus dados satélites são novamente retirados da mesma tabela montada na função `players`.

Por fim, na função `tags`, nos valemos de outra **Árvore Trie**, que guarda em suas folhas todos os IDs de jogadores que receberam a dada tag. Assim, é feita a pesquisa na árvore para todas as tags passadas para a função; é feita a intersecção delas, afim de se encontrar quais jogadores receberam ambas as tags; e, na hora de imprimir, os dados satélites são novamente retirados da tabela de jogadores.

Ou seja, ao todo, foram utilizadas:

- 3 Árvores Trie;
- 3 Tabelas Hash;
- 1 Algoritmo de sorting, sendo ele o quicksort.
