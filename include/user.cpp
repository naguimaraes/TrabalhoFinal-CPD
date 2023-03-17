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