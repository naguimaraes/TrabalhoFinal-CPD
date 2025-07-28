#include <cmath>
#include <string>
#include <vector>
#include "hashtable.hpp"
using std::to_string;

HashPlayer::HashPlayer(){
    for(int i = 0; i < HASH_SIZE ; i++){
        hash_table.push_back(vector<Player>());
    }
}
int HashPlayer::getKey(string id, int size){
    long long int hash_key = 0;
    int a = 31;

    for(int i = 0; i < size; i++){
        hash_key += id[i] * pow(a, i);
    }
        
    hash_key %= HASH_SIZE;

    return hash_key;
}
void HashPlayer::insert(Player player)
{
    int key = getKey(player.getId(), player.getId().size());
    hash_table[key].push_back(player);        
}
Player* HashPlayer::search(string id){
    int size = id.size();
    int key = getKey(id, size);

    for(size_t i = 0; i < hash_table[key].size(); i++){
        if(hash_table[key][i].getId() == id)
            return &hash_table[key][i];
    }

    return NULL;    
}



HashUser::HashUser(){
    for(int i = 0; i < HASH_SIZE ; i++){
        hash_table.push_back(vector<User>());
    }
}
int HashUser::getKey(string id, int size){
    long long int hash_key = 0;
    int a = 31;

    for(int i = 0; i < size; i++){
        hash_key += id[i] * pow(a, i);
    }
        
    hash_key %= HASH_SIZE;

    return hash_key;
}
void HashUser::insert(User user){
    int key = getKey(user.getId(), user.getId().size());

    for(size_t i = 0; i < hash_table[key].size(); i++)
    {
        if(hash_table[key].at(i).getId() == user.getId())
        {
            hash_table[key].at(i).insertRatedPlayer(user.getRatedPlayerBuffer());
            return;
        }
    }   
    user.insertRatedPlayer(user.getRatedPlayerBuffer());
    hash_table[key].push_back(user);
}
User* HashUser::search(string id){
    int size = id.size();
    int key = getKey(id, size);

    for(size_t i = 0; i < hash_table[key].size(); i++){
        if(hash_table[key][i].getId() == id)
            return &hash_table[key][i];
    }

    return NULL;    
}