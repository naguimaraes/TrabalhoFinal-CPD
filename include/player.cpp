#include <iostream>
#include "player.hpp"
using std::string;

string Player::getId(){
    return id;
}
string Player::getName(){
     return name;
}
string Player::getPositions(){
    return pos;
}
float Player::getRating(){
    
    if(count > 0){
        return rating/count;
    }
    else{
        return 0;
    }
}
int Player::getCount(){
    return count;
}

void Player::setId(string player_id)
{
    id = player_id;
}
void Player::setName(string player_name)
{
    name = player_name;
}
void Player::setPositions(string player_position)
{
    pos = player_position;
}
void Player::addRating(float player_rating)
{
    rating += player_rating;
    count++;
}
