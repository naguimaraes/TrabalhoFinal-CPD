#include <iostream>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "include/positions.hpp"
#include "include/parser.hpp"
#include "include/player.hpp"
#include "include/hashtable.hpp"
#include "include/trie.hpp"
#include "include/user.hpp"

using namespace aria::csv;
using namespace std;


int main(void){

    int data_stat;
    clock_t timer = clock();
    string input_string;
    HashPlayer player_hash;
    HashUser user_hash;
    Trie player_trie;
    Trie surname_trie;
    Trie tags_trie;
    Positions top_positions;
    ifstream players_file("data/players.csv");
    ifstream ratings_file("data/minirating.csv");
    ifstream tags_file("data/tags.csv");
    CsvParser parser_players(players_file);
    CsvParser parser_ratings(ratings_file);
    CsvParser parser_tags(tags_file);

    // Loop to skip the CSV's headings
    for (auto& row : parser_players) {
        for (auto& field : row){
            (void)field; // Suppress unused variable warning
        }
        break;
    }
    for (auto& row : parser_ratings) {
        for (auto& field : row){
            (void)field; // Suppress unused variable warning
        } 
        break;
    }
    for (auto& row : parser_tags) {
        for (auto& field : row){
            (void)field; // Suppress unused variable warning
        }
        break;
    }


    // Loop to read players.csv
    enum player_csv_values
    {
        ID, NAME, POS
    };
    data_stat = 0;

    cout << "Building player hash and player trie...\n\n";

    for (auto& row : parser_players) {
        Player buffer;
        string buffer_surname;
        for (auto& field : row) {
            switch (data_stat){
            case ID: // id
                buffer.setId(field);
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
        top_positions.insert(buffer.getId(), buffer.getPositions());
        player_hash.insert(buffer);
        player_trie.insert(buffer.getName(), stoi(buffer.getId()));

        istringstream buffer_stream(buffer.getName());
        buffer_stream >> buffer_surname;
        while(buffer_stream >> buffer_surname){
            surname_trie.insert(buffer_surname, stoi(buffer.getId()));
        }
    }

    cout << "Player hash, player trie and surname trie done!\n\n";

    
    // Loop to read rating.csv
    enum rating_csv_values
    {
        USER_ID, PLAYER_ID, RATING
    };
    data_stat = 0;

    cout << "Building user hash...\n\n"; 
    for (auto& row : parser_ratings) {
        User user_buffer;
        string playerId;
        float rating;
        for (auto& field : row) {
            switch (data_stat){
            case USER_ID:
                user_buffer.setId(field);
                data_stat++;
                break;
            case PLAYER_ID: 
                playerId = field;
                data_stat++;
                break;
            case RATING:
                rating = stof(field);
                user_buffer.setRatedPlayer(playerId, rating);            
                player_hash.search(playerId)->addRating(rating);
                data_stat = 0;              
                break;
            }
        }
        user_hash.insert(user_buffer);
    }
    cout << "User hash done!\n\n";

     // Loop to read tags.csv
    enum tags_csv_values
    {
        USER_ID2, PLAYER_ID2, TAG
    };
    data_stat = 0;

    cout << "Building tags trie...\n\n"; 

    for (auto& row : parser_tags) {
        string buffer_tag, buffer_id;
        for (auto& field : row) {
            switch (data_stat){
            case USER_ID2:
                data_stat++;
                break;
            case PLAYER_ID2:
                buffer_id = field;
                data_stat++;
                break;
            case TAG:
                buffer_tag = field;
                data_stat = 0;              
                break;
            }
        }
        tags_trie.insert(buffer_tag, stoi(buffer_id));
    }

    cout << "Tags trie done!\n\n"; 


    timer = clock() - timer;
    cout << "All structs have been built in " << fixed << setprecision(2) << ((float)timer / CLOCKS_PER_SEC) << " seconds!\n";
    cout << "\nInsert your search: ";
    getline(cin, input_string, '\n');

    while (true){
        if(!(input_string.substr(0, 6).compare("player"))){
            player_trie.searchPrefix(input_string.substr(7));

            if(player_trie.print_vector.size() < 1){
                cout << "Invalid name!\n" << endl;
            }
            else{
                cout << "\n";
                cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                cout << "| " << setw(9) << setfill(' ') << "Player ID" << " | ";
                cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                cout << left << setw(13) << setfill(' ') << "Positions" << " | ";
                cout << left << setw(7) << setfill(' ') << "Rating" << " | ";
                cout << left << setw(7) << setfill(' ') << "Count" << "|" << "\n";
                cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                for(size_t i = 0; i < player_trie.print_vector.size(); i++){
                    cout << "| " << right << setw(9) << setfill(' ') << player_trie.print_vector[i] << " | ";
                    cout << left << setw(48) << setfill(' ') << player_hash.search(to_string(player_trie.print_vector[i]))->getName() << " | ";
                    cout << left << setw(13) << setfill(' ') << player_hash.search(to_string(player_trie.print_vector[i]))->getPositions() << " | ";
                    cout << right << setw(7) << setfill(' ') << player_hash.search(to_string(player_trie.print_vector[i]))->getRating() << " | ";
                    cout << right << setw(6) << setfill(' ') << player_hash.search(to_string(player_trie.print_vector[i]))->getCount() << " |" << "\n";
                }
                cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n" << endl;
            }

            player_trie.print_vector.clear();

        }

        else if(!(input_string.substr(0, 4).compare("user"))){
            string user_id = input_string.substr(5);

            // Tests if the input after "user" only contains integer numbers
            if(user_id.find_first_not_of("0123456789") == std::string::npos){
                
                // Tests if the given user is present in the players.csv
                if(user_hash.search(user_id) != NULL){
                    int vector_size = user_hash.search(user_id)->getRatedPlayerVector().size();
                    user_hash.search(user_id)->sortRatedPlayerVector(0, vector_size-1);
                    vector<RatedPlayer> ratings_vector = (user_hash.search(user_id)->getRatedPlayerVector());

                    cout << "\n";
                    cout << setw(7+48+13+5+13+15) << setfill('-') << "-" << "\n";
                    cout << "| " << setw(7) << setfill(' ') << "User ID" << " | ";
                    cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                    cout << left << setw(13) << setfill(' ') << "Global Rating" << " | ";
                    cout << left << setw(5) << setfill(' ') << "Count" << " | ";
                    cout << left << setw(13) << setfill(' ') << "User Rating" << "|" << "\n";
                    cout << setw(7+48+13+5+13+15) << setfill('-') << "-" << "\n";
                    
                    for(size_t i = 0; i < ratings_vector.size() and i < 20; i++){
                        Player *player_buffer = player_hash.search(ratings_vector.at(i).player_id);
                        
                        cout << "| " << right << setw(7) << setfill(' ') << player_buffer->getId() << " | ";
                        cout << left << setw(48) << setfill(' ') << player_buffer->getName() << " | ";
                        cout << right << setw(13) << setfill(' ') << player_buffer->getRating() << " | ";
                        cout << right << setw(5) << setfill(' ') << player_buffer->getCount() << " | ";
                        cout << right << setw(12) << setfill(' ') << ratings_vector.at(i).player_rating << " |\n";
                    }
                    cout << setw(7+48+13+5+13+15) << setfill('-') << "-" << "\n\n";
                }
                else{
                    cout << "Invalid user ID!\n" << endl;
                }
            }
            else{
                cout << "Invalid user ID!\n" << endl;
            }
        }

        else if(!(input_string.substr(0, 3).compare("top"))){

            int n;
            vector<TopRatedPlayers> sorted_vector;
            string input_positions;       
            string buffer_n{0};
            stringstream buffer_stream(input_string.substr(3));
            getline(buffer_stream, buffer_n, ' ');
            // Checks if what comes after "top" is actually a representable integer 
            if(buffer_n.find_first_not_of("0123456789") == std::string::npos and buffer_n.size() < 10 and buffer_n.size() > 0){    
                n = stoi(buffer_n);
                input_positions = input_string.substr(3 + buffer_n.size());
                input_positions.erase(remove(input_positions.begin(), input_positions.end(), ' '), input_positions.end());
                input_positions.erase(remove(input_positions.begin(), input_positions.end(), '\''), input_positions.end());

                // Checks if the given player position is valid or not
                if(top_positions.checkPositions(input_positions)){

                    top_positions.getRatings(input_positions, player_hash);           
                    sorted_vector = top_positions.getRatedPlayerVector(input_positions);

                    cout << "\n";
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                    cout << "| " << setw(9) << setfill(' ') << "Player ID" << " | ";
                    cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                    cout << left << setw(13) << setfill(' ') << "Positions" << " | ";
                    cout << left << setw(7) << setfill(' ') << "Rating" << " | ";
                    cout << left << setw(7) << setfill(' ') << "Count" << "|" << "\n";
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";

                    for(size_t i = 0; i < static_cast<size_t>(n) and i < sorted_vector.size(); i++){
                        Player *buffer = player_hash.search(sorted_vector[i].player_id);
                        if(buffer->getCount() > 1000){
                            cout << "| " << right << setw(9) << setfill(' ') << sorted_vector[i].player_id << " | ";
                            cout << left << setw(48) << setfill(' ') << buffer->getName() << " | ";
                            cout << left << setw(13) << setfill(' ') << buffer->getPositions() << " | ";
                            cout << right << setw(7) << setfill(' ') << buffer->getRating() << " | ";
                            cout << right << setw(6) << setfill(' ') << buffer->getCount() << " |" << "\n";
                        }
                        else{
                            n++;
                        }
                    }
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n" << endl;
                }
                else{
                    cout << "Invalid player position!\n" << endl;
                }
            }
            else{
                cout << "Invalid top number!\n" << endl;
            }
        }

        else if(!(input_string.substr(0, 6).compare("bottom"))){
            int n;
            vector<TopRatedPlayers> sorted_vector;
            string input_positions;       
            string buffer_n{0};
            stringstream buffer_stream(input_string.substr(6));
             
            getline(buffer_stream, buffer_n, ' ');
            // Checks if what comes after "bottom" is actually a representable integer 
            if(buffer_n.find_first_not_of("0123456789") == std::string::npos and buffer_n.size() < 10 and buffer_n.size() > 0){    
                n = stoi(buffer_n);
                input_positions = input_string.substr(6 + buffer_n.size() + 1);
                input_positions.erase(remove(input_positions.begin(), input_positions.end(), ' '), input_positions.end());
                input_positions.erase(remove(input_positions.begin(), input_positions.end(), '\''), input_positions.end());
                // Checks if the given player position is valid or not
                if(top_positions.checkPositions(input_positions)){

                    top_positions.getRatings(input_positions, player_hash);           

                    sorted_vector = top_positions.getRatedPlayerVector(input_positions);

                    cout << "\n";
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                    cout << "| " << setw(9) << setfill(' ') << "Player ID" << " | ";
                    cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                    cout << left << setw(13) << setfill(' ') << "Positions" << " | ";
                    cout << left << setw(7) << setfill(' ') << "Rating" << " | ";
                    cout << left << setw(7) << setfill(' ') << "Count" << "|" << "\n";
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";

                    for(int i = static_cast<int>(sorted_vector.size())-1; i >= 0 && i > static_cast<int>(sorted_vector.size() - 1 - n); i--){
                        Player *buffer = player_hash.search(sorted_vector[i].player_id);
                        if(buffer->getCount() > 1000){
                            cout << "| " << right << setw(9) << setfill(' ') << sorted_vector[i].player_id << " | ";
                            cout << left << setw(48) << setfill(' ') << buffer->getName() << " | ";
                            cout << left << setw(13) << setfill(' ') << buffer->getPositions() << " | ";
                            cout << right << setw(7) << setfill(' ') << buffer->getRating() << " | ";
                            cout << right << setw(6) << setfill(' ') << buffer->getCount() << " |" << "\n";
                        }
                        else{
                            n++;
                        }
                    }
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n" << endl;
                }
                else{
                    cout << "Invalid player position!\n" << endl;
                }
            }
            else{
                cout << "Invalid top number!\n" << endl;
            }
        }

        else if(!(input_string.substr(0, 4).compare("tags"))){
            stringstream buffer_stream(input_string.substr(4));
            string buffer_string;
            vector<string> tags_vector;
            vector<int> intersection_vector;
            bool invalid_tag = false;
            while(getline(buffer_stream, buffer_string, '\'')){
                if((buffer_string.compare(" "))){
                    tags_vector.push_back(buffer_string);
                    tags_trie.removeDuplicates(buffer_string);
                }

            } 
            for(size_t i = 0; i < tags_vector.size(); i++){
                if(tags_trie.search(tags_vector[i]) == -1){
                    invalid_tag = true;
                }  
            }
            if(!invalid_tag){
                intersection_vector = tags_trie.findIntersection(tags_vector.size());
                if(intersection_vector.size() == 0){
                    cout << "No player matches the given tags!\n" << endl;
                }
                else{

                    cout << "\n";
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                    cout << "| " << setw(9) << setfill(' ') << "Player ID" << " | ";
                    cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                    cout << left << setw(13) << setfill(' ') << "Positions" << " | ";
                    cout << left << setw(7) << setfill(' ') << "Rating" << " | ";
                    cout << left << setw(7) << setfill(' ') << "Count" << "|" << "\n";
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                    for(size_t i = 0; i < intersection_vector.size(); i++){
                        cout << "| " << right << setw(9) << setfill(' ') << intersection_vector[i] << " | ";
                        cout << left << setw(48) << setfill(' ') << player_hash.search(to_string(intersection_vector[i]))->getName() << " | ";
                        cout << left << setw(13) << setfill(' ') << player_hash.search(to_string(intersection_vector[i]))->getPositions() << " | ";
                        cout << right << setw(7) << setfill(' ') << player_hash.search(to_string(intersection_vector[i]))->getRating() << " | ";
                        cout << right << setw(6) << setfill(' ') << player_hash.search(to_string(intersection_vector[i]))->getCount() << " |" << "\n";
                    }
                    cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n" << endl;
                }
            }
            else{
                cout << "Invalid tags!\n" << endl;  
            }      
            tags_trie.print_vector.clear();
        }

        else if(!(input_string.substr(0, 7).compare("surname"))){
            surname_trie.searchPrefix(input_string.substr(8));
            
            if(surname_trie.print_vector.size() == 0){
                cout << "Invalid surname!\n" << endl;
            }
            else{
                cout << "\n";
                cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                cout << "| " << setw(9) << setfill(' ') << "Player ID" << " | ";
                cout << left << setw(48) << setfill(' ') << "Full Name" << " | ";
                cout << left << setw(13) << setfill(' ') << "Positions" << " | ";
                cout << left << setw(7) << setfill(' ') << "Rating" << " | ";
                cout << left << setw(7) << setfill(' ') << "Count" << "|" << "\n";
                cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n";
                for(size_t i = 0; i < surname_trie.print_vector.size(); i++){
                    cout << "| " << right << setw(9) << setfill(' ') << surname_trie.print_vector[i] << " | ";
                    cout << left << setw(48) << setfill(' ') << player_hash.search(to_string(surname_trie.print_vector[i]))->getName() << " | ";
                    cout << left << setw(13) << setfill(' ') << player_hash.search(to_string(surname_trie.print_vector[i]))->getPositions() << " | ";
                    cout << right << setw(7) << setfill(' ') << player_hash.search(to_string(surname_trie.print_vector[i]))->getRating() << " | ";
                    cout << right << setw(6) << setfill(' ') << player_hash.search(to_string(surname_trie.print_vector[i]))->getCount() << " |" << "\n";
                }
                cout << setw(9+48+13+7+7+15) << setfill('-') << "-" << "\n" << endl;
            }

            surname_trie.print_vector.clear();
        }

        else if(!(input_string.compare("help"))){
            cout << "\nAvailable search commands:\n";
            cout << "- player <name>: Search for players by name prefix\n";
            cout << "- user <id>: Display ratings for a specific user ID\n";
            cout << "- top <n> <position>: Show top N players for a position\n";
            cout << "- bottom <n> <position>: Show bottom N players for a position\n";
            cout << "- tags '<tag1>' '<tag2>' ...: Find players matching all given tags\n";
            cout << "- surname <surname>: Search for players by surname prefix\n";
            cout << "- help: Display this help message\n";
            cout << "- exit: Exit the program\n" << endl;
        }

        else if(input_string == "exit"){
            cout << "\nExiting the program...\n";
            break;
        }

        else{
            cout << "Invalid search!\n" << endl;
        }

        cout << "Insert your search: ";
        getline(cin, input_string, '\n');
    }
    return 0;
}
