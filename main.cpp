#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "include/parser.hpp"
#include "include/player.hpp"
#include "include/hashtable.hpp"
#include "include/trie.hpp"
#include "include/user.hpp"

using aria::csv::CsvParser;
using namespace std;


int main(void){

    int data_stat;

    string input_string;
    
    HashPlayer player_hash = HashPlayer();
    HashUser user_hash = HashUser();

    Trie player_trie = Trie();

    ifstream players_file("data/players.csv");
    ifstream ratings_file("data/rating.csv");

    CsvParser parser_players(players_file);
    CsvParser parser_ratings(ratings_file);

    // Loop para pular o título das colunas no CSV
    for (auto& row : parser_players) {
        for (auto& field : row){}
        break;
    }
    for (auto& row : parser_ratings) {
        for (auto& field : row){} 
        break;
    }


    // Loop de leitura do players.csv
    enum player_csv_values
    {
        ID, NAME, POS
    };
    data_stat = 0;

    for (auto& row : parser_players) {
        Player buffer;
        for (auto& field : row) {
            switch (data_stat){
            case ID: // id
                buffer.setId(stoi(field));
                data_stat++;
                break;
            case NAME: // name
                buffer.setName(field);
                data_stat++;
                break;
            case POS: // pos
                buffer.setPositions(field);
                data_stat = 0;
                break;
            }
        }
        player_hash.insert(buffer);
        player_trie.insert(buffer.getName(), buffer.getId());
    }

    
    // Loop de leitura do rating.csv
    enum rating_csv_values
    {
        USER_ID, PLAYER_ID, RATING
    };
    data_stat = 0;

    for (auto& row : parser_ratings) {
        User user_buffer;
        int playerId;
        float rating;
        for (auto& field : row) {
            switch (data_stat){
            case USER_ID:
                user_buffer.setId(stoi(field));
                data_stat++;
                break;
            case PLAYER_ID: 
                playerId = stoi(field);
                data_stat++;
                break;
            case RATING:
                rating = stof(field);
                user_buffer.setRatedPlayer(playerId, rating);            
                player_hash.search(playerId)->addRating(rating);
                player_hash.search(playerId)->addCount();
                data_stat = 0;              
                break;
            }
        }
        user_hash.insert(user_buffer);
    }
 


    cout << "Montagem das estruturas finalizada!\n";
    cout << "Insira a busca a ser feita: ";
    getline(cin, input_string, '\n');

    while (input_string != "-1"){
        if(!(input_string.substr(0, 6).compare("player"))){
            player_trie.searchPrefix(input_string.substr(7));

            if(player_trie.vector_id.size() < 1){
                cout << "Informe um nome valido!\n" << endl;
            }
            else{
                cout << "\n";
                cout << setw(9+48+13+7+6+15) << setfill('-') << "-" << "\n";
                cout << "| " << setw(9) << setfill(' ') << "Player ID" << " | ";
                cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                cout << left << setw(13) << setfill(' ') << "Positions" << " | ";
                cout << left << setw(7) << setfill(' ') << "Rating" << " | ";
                cout << left << setw(6) << setfill(' ') << "Count" << "|" << "\n";
                cout << setw(9+48+13+7+6+15) << setfill('-') << "-" << "\n";
                for(int i = 0; i < player_trie.vector_id.size(); i++){
                    cout << "| " << right << setw(9) << setfill(' ') << player_trie.vector_id[i] << " | ";
                    cout << left << setw(48) << setfill(' ') << player_hash.search(player_trie.vector_id[i])->getName() << " | ";
                    cout << left << setw(13) << setfill(' ') << player_hash.search(player_trie.vector_id[i])->getPositions() << " | ";
                    cout << right << setw(7) << setfill(' ') << player_hash.search(player_trie.vector_id[i])->getRating() << " | ";
                    cout << right << setw(6) << setfill(' ') << player_hash.search(player_trie.vector_id[i])->getCount() << "|" << "\n";
                }
                cout << setw(9+48+13+7+6+15) << setfill('-') << "-" << "\n" << endl;
            }

            player_trie.vector_id.clear();

        }
        else if(!(input_string.substr(0, 4).compare("user"))){
            int user_id = stoi(input_string.substr(5));
            vector<RatedPlayer> ratings_vector = (user_hash.search(user_id)->getRatedPlayerVector());

            // ORDENAR POR USER RATING
            if(ratings_vector.size() !=  0){

                cout << "\n";
                cout << setw(7+48+13+5+12+15) << setfill('-') << "-" << "\n";
                cout << "| " << setw(7) << setfill(' ') << "User ID" << " | ";
                cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                cout << left << setw(13) << setfill(' ') << "Global Rating" << " | ";
                cout << left << setw(5) << setfill(' ') << "Count" << " | ";
                cout << left << setw(12) << setfill(' ') << "User Rating" << "|" << "\n";
                cout << setw(7+48+13+5+12+15) << setfill('-') << "-" << "\n";
                
                for(int i = 0; i < ratings_vector.size() and i < 20; i++){
                    Player *player_buffer = player_hash.search(ratings_vector.at(i).player_id);
                    
                    cout << "| " << right << setw(7) << setfill(' ') << player_buffer->getId() << " | ";
                    cout << left << setw(48) << setfill(' ') << player_buffer->getName() << " | ";
                    cout << right << setw(13) << setfill(' ') << player_buffer->getRating() << " | ";
                    cout << right << setw(5) << setfill(' ') << player_buffer->getCount() << " | ";
                    cout << right << setw(12) << setfill(' ') << ratings_vector.at(i).player_rating << "|\n";
                }
                cout << setw(7+48+13+5+12+15) << setfill('-') << "-" << "\n\n";
            }
            else{
                cout << "Informe um ID de usuario valido!\n" << endl;
            }
        }
        else{
            cout << "Informe uma pesquisa valida!\n" << endl;
        }

        cout << "Insira a busca a ser feita: ";
        getline(cin, input_string, '\n');
    }
    return 0;
}
