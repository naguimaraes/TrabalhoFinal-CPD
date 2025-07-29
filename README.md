# **Data Search in FIFA 21 Players Dataset**

## **Description**

This code was concieved as the final project for the Data Classification and Search class. The project consists of implementing fast searches within the FIFA 21 players dataset, [available at Kaggle](https://www.kaggle.com/stefanoleone992/fifa-21-complete-player-dataset). The code was written by students [Nathan Alonso Guimarães](https://github.com/naguimaraes) and [João Vítor Schimuneck de Souza](https://github.com/jvhendrix), entirely in C++.

The project was originally conceived in March of 2023, but it has been updated in July of 2025 to be better documented in GitHub.

## **Project Building**

To build the project, follow these steps:

1. Clone or download the repository:
   ```bash
   git clone https://github.com/naguimaraes/data-classification-and-search.git
   cd data-classification-and-search
   ```

2. Build the project using Make:
   ```bash
   make
   ```
3. Run the program:
   ```bash
   make run
   # or 
   ./main.exe
    ```

You can also clean the project by running:
   ```bash
   make clean
   ```

## **Usage**

While running the program, you will be prompted to enter a search command. The program will continue waiting for input until you type `exit` to terminate it. You can also promp `help` to see the available commands and their usage.

The available searches are listed in the [section below](#available-searches). You can type them directly into the console. The search commands are case-sensitive, so make sure to use the correct case for the commands and arguments.

## **Available Searches**

### 1. Search by player name

- Syntax and usage: `player <player_name>` or `player <name_initials>`.
- Return: a table with all players whose names start with the given argument.
- Example:

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

### 2. Search by player surname

- Syntax and usage: `surname <player_surname>` or `surname <surname_initials>`.
- Return: a table with all players who have at least one surname starting with the given argument.
- Example:

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

### 3. Search by user ratings

- Syntax and usage: `user <user_number>`.
- Return: a table with the 20 highest-rated players by the given user.
- Example:

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

### 4. Search for best players by position

- Syntax and usage: `top<N> '<player_position>'`.
- Return: a table with the `N` best players for the given position, ordered by their rating averages.
- Example:

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

### 5. Search for worst players by position

- Syntax and usage: `bottom<N> '<player_position>'`.
- Return: a table with the `N` worst players for the given position, ordered by their rating averages.
- Example:

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

### 6. Search by player tags

- Syntax and usage: `tags '<tag1>' '<tag2>' ... '<tagN>'`.
- Return: a table with the intersection of players that contain all the given tags.
- Example:

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

## **Project File Structure**

In root directory, you will find the following files:
- `aux-codes/`: a directory containing a auxiliary code that was used in the project but is not included in `main.cpp`
    - `maxsize.cpp`: a code to find the maximum size of a player's name in the dataset. It was used to correctly print the outputs in a table format with proper alignment

- `data/`: a directory containing the dataset files used in the project.
    - `minirating.csv`: a smaller version of the original `rating.csv` file, made only to test the program faster
    - `players_21.csv`: contains the full dataset information about the players in the game, including unused information such as players "body type" and "week foot" ratings
    - `players.csv`: a smaller version of `players_21.csv`, that contains only information about the ID, full name, and positions of each of the nearly 19,000 players in the game
    - `rating.csv`: contains 24 million user ratings, where users can assign a score from 0 to 5 to a specific player in the game
    - `tags.csv`: contains 360,000 characteristics assigned to players in the game to characterize them.

- `include/`: a directory containing the implementation of the data structures used in the project
    - `hashtable.cpp` and `hashtable.hpp`: implementation of the Hash Table data structure used to store player satellite data
    - `parser.cpp` and `parser.hpp`: implementation of the CSV parser used to read the dataset files
    - `players.cpp` and `players.hpp`: implementation of the Players class, which contains the data structure for storing player satellite data
    - `positions.cpp` and `positions.hpp`: implementation of the Positions class, which contains the data structure for storing players by their positions
    - `trie.cpp` and `trie.hpp`: implementation of the Trie Tree data structure used to store player names and surnames, as well as tags
    - `user.cpp` and `user.hpp`: implementation of the User class, which contains the data structure for storing user ratings

- `.gitignore`: a file that specifies which files and directories should be ignored by Git, such as compiled files and executables

- `main.cpp`: the main file that runs the program and allows the user to perform searches

- `Makefile`: a file that contains the instructions to build and run the project using `make` and `make run`, respectively

- `README.md`: this file, containing project description and instructions.

- `specifications.pdf`: a file, provided by our professor, that contains the specifications of the project and the requirements for the implementation, written in Portuguese

## **Data Structures Used**

For the `player` search function, a **Trie Tree** was built, which stores the full name of all players and keeps their IDs in the leaves. Along with the tree, it was necessary to implement a **Hash Table**, which stores all satellite data of the players and uses the player ID as the search key. Thus, first the given name is searched within the tree, returning the player's ID. This ID is used in the table to obtain the other data that will be printed on screen.

In the `surname` function, we also built a **Trie Tree**, which contains all existing surnames in the game. Unlike the tree from the first search, its leaves store a vector of IDs since more than one player can contain the same surname. Thus, the given surname is searched in the tree, and a list with all IDs of players containing that name is returned. Similarly, the IDs are used to search in the same table from the `player` function, in order to print the satellite data.

In the `user` function, a similar strategy was used. A **Hash Table** was created that uses the user number as a key, and stores that user's satellite data:

In the `top` and `bottom` functions, we created another **Hash Table** that separates all players into their respective positions. Therefore, the table key is precisely the player's position. This way, we obtain vectors that contain all players for each position in the game. However, before printing the data, the vector for the given position is sorted according to the players' average ratings, and their satellite data is again retrieved from the same table built in the `players` function.

Finally, in the `tags` function, we used another **Trie Tree**, which stores in its leaves all IDs of players who received the given tag. Thus, the tree is searched for all tags passed to the function; their intersection is performed to find which players received all the tags; and, when printing, the satellite data is again retrieved from the players table.

In other words, we used the following data structures:

- 3 Trie Trees;
- 3 Hash Tables;
- 1 Sorting algorithm, which is quicksort.
