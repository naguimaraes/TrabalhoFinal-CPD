#include <string>
#include <sstream>  
#include <vector>
#include <algorithm>
#include "positions.hpp"

int Positions::getKey(string player_position)
{
    for (size_t i = 0; i < positions.size(); i++)
    {
        if (positions.at(i) == player_position)
        {
            return static_cast<int>(i);
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


int Positions::partition(int left, int right, int position){
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



void Positions::sortTopPlayersVector(int left, int right, int position){
    if (left < right) {   
        int pi = partition(left, right, position);
  
        sortTopPlayersVector(left, pi - 1, position);
        sortTopPlayersVector(pi + 1, right, position);
    }
}


Positions::Positions(){
    for(size_t i = 0; i < positions.size() ; i++){
        top_positions_vector.push_back(vector<TopRatedPlayers>());
    }
}



vector<TopRatedPlayers> Positions::getRatedPlayerVector(string position)
{
    int key = getKey(position);
    return top_positions_vector[key];
}

void Positions::getRatings(string position, HashPlayer player_hash){
    int key = getKey(position);

    for(size_t i = 0; i < top_positions_vector[key].size(); i++){
        top_positions_vector[key][i].player_rating = player_hash.search(top_positions_vector[key][i].player_id)->getRating();
    }
    
    sortTopPlayersVector(0, top_positions_vector[key].size()-1, key);
}

bool Positions::checkPositions(string position){
    if (std::count(positions.begin(), positions.end(), position)){
        return true;
    }
    else{
        return false;
    }
}
