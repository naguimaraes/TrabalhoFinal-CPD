#include <string>
#include <sstream>  
#include <vector>
#include <algorithm>
#include "positions.hpp"

int Positions::getKey(string player_position)
{
    for (int i = 0; i < positions.size(); i++)
    {
        if (positions.at(i) == player_position)
        {
            return i;
        }
        
    }
    return -1;
}

void Positions::insert(string player_id, string positions){
    
    string buffer_str;
    std::stringstream buffer_stream(positions); 
    TopRatedPlayers buffer;
    buffer.player_id = player_id;

    while(std::getline(buffer_stream, buffer_str, ',')){
        if(buffer_str[0] == ' '){
            buffer_str.erase(0, 1);
        }
        top_positions_vector.at(getKey(buffer_str)).push_back(buffer);
    };
}

int Positions::partitionDescending(int left, int right, int position){
    int i, j;
    TopRatedPlayers key;
    key = top_positions_vector[position][left];
    i = left; 
    j = right;

    while (i<j) {
        while(top_positions_vector[position][j].player_rating < key.player_rating && i < j) j--;
        {
            top_positions_vector[position][i] = top_positions_vector[position][j];
        }
        while(top_positions_vector[position][i].player_rating >= key.player_rating && i < j) i++ ;
        {
            top_positions_vector[position][j] = top_positions_vector[position][i];
        }
    }

    top_positions_vector[position][j] = key;

    return i;
}

int Positions::partitionAscending(int left, int right, int position){
    int i, j;
    TopRatedPlayers key;
    key = top_positions_vector[position][left];
    i = left; 
    j = right;

    while (i<j) {
        while(top_positions_vector[position][j].player_rating > key.player_rating && i < j) j--;
        {
            top_positions_vector[position][i] = top_positions_vector[position][j];
        }
        while(top_positions_vector[position][i].player_rating <= key.player_rating && i < j) i++ ;
        {
            top_positions_vector[position][j] = top_positions_vector[position][i];
        }
    }

    top_positions_vector[position][j] = key;

    return i;
}



void Positions::sortTopPlayersVector(int left, int right, int position, bool isDescending){
    if (left < right) {   
        int pi;

        if(isDescending){
            pi = partitionDescending(left, right, isDescending);
        }
        else{
            pi = partitionAscending(left, right, isDescending);
        }

        sortTopPlayersVector(left, pi - 1, position, isDescending);
        sortTopPlayersVector(pi + 1, right, position, isDescending);
    }
}


Positions::Positions(){
    for(int i = 0; i < positions.size() ; i++){
        top_positions_vector.push_back(vector<TopRatedPlayers>());
    }
}

void Positions::sortRatings(string position, HashPlayer player_hash, bool isDescending){
    int key = getKey(position);

    for(int i = 0; i < top_positions_vector[key].size(); i++){
        top_positions_vector[key][i].player_rating = player_hash.search(top_positions_vector[key][i].player_id)->getRating();
    }
    
    sortTopPlayersVector(0, top_positions_vector[key].size()-1, key, isDescending);
}

vector<TopRatedPlayers> Positions::getRatedPlayerVector(string position)
{
    int key = getKey(position);
    return top_positions_vector[key];
}

bool Positions::checkPositions(string position){
    if (std::count(positions.begin(), positions.end(), position)){
        return true;
    }
    else{
        return false;
    }
}
