#include <iostream>
#include "user.hpp"
using std::string;

int User::getId(void)
{
    return id;
}

void User::setId(int user_id)
{
    id = user_id;
}

void User::insertRatedPlayer(RatedPlayer rated_player)
{
    rated_player_vector.push_back(rated_player);
}

void User::setRatedPlayer(int player_id, float player_rating)
{
    buffer_rated_player.player_id = player_id;
    buffer_rated_player.player_rating = player_rating;
}

RatedPlayer User::getRatedPlayerBuffer(){
    return buffer_rated_player;
}

vector<RatedPlayer> User::getRatedPlayerVector()
{
    return rated_player_vector;
}

int User::partition(int left, int right){
    int i, j;
    RatedPlayer key;
    key = rated_player_vector[left];
    i = left; 
    j = right;

    while (i<j) {
        while(rated_player_vector[j].player_rating < key.player_rating && i < j) j--;
        {
            rated_player_vector[i] = rated_player_vector[j];
        }
        while(rated_player_vector[i].player_rating >= key.player_rating && i < j) i++ ;
        {
            rated_player_vector[j] = rated_player_vector[i];
        }
    }
    rated_player_vector[j] = key;
    return i;

}

void User::sortRatedPlayerVector(int left, int right){
    if (left < right) {

        int pi = partition(left, right);
  
        sortRatedPlayerVector(left, pi - 1);
        sortRatedPlayerVector(pi + 1, right);
    }
}