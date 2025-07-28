#include <iostream>
#include <fstream>
#include <string>
#include "include/parser.hpp"

using aria::csv::CsvParser;
using namespace std;

// Function to find the size of the longest name in the `players.csv` file
int main(void){

    int max_size = 0;
    string name;
    ifstream players_file("data/players.csv");

    CsvParser parser_players(players_file);

    for (auto& row : parser_players) {
        for (auto& field : row){}
        break;
    }
    enum player_csv_values
    {
        ID, NAME, POS
    };
    int data_stat = 0;

    for (auto& row : parser_players) {
        for (auto& field : row) {
            switch (data_stat){
            case ID: 
                data_stat++;
                break;
            case NAME:
                if(field.size() > max_size){
                    max_size = field.size();
                    name = field;
                }
                data_stat++;
                break;
            case POS: 
                data_stat = 0;
                break;
            }
        }
    }

    cout << "Tamanho maximo: " << max_size << endl;
    cout << "Nome do jogador: " << name << endl;

    return 0;
}