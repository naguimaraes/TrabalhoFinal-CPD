#include <cmath>
#include <string>
#include <vector>
#include "hashtable.hpp"
using std::to_string;

int HashTable::getKey(int id, int size){
    
    string s = to_string(id);

    long long int hash_key = 0;
    int a = 3;

    for(int i = 0; i < size; i++){
        hash_key += s[i] * pow(a, i);
    }
        
    hash_key %= HASH_SIZE;

    return hash_key;
}
void HashPlayer::insert(Player player){
    int key = getKey(player.getId(), to_string(player.getId()).size());
    hash_table[key].push_back(player);        
}

Player* HashPlayer::search(int id){
    int size = to_string(id).size();
    int key = getKey(id, size);

    for(int i = 0; i < hash_table[key].size(); i++){
        if(hash_table[key][i].getId() == id)
            return &hash_table[key][i];
    }

    return NULL;    
}

// Preenche a hash com vetores vazios
HashPlayer::HashPlayer(){
    for(int i = 0; i < HASH_SIZE ; i++){
        hash_table.push_back(vector<Player>());
    }
}

void HashUser::insert(User user){
    int key = getKey(user.getId(), to_string(user.getId()).size());

    for(int i = 0; i < hash_table[key].size(); i++)
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

User* HashUser::search(int id){
    int size = to_string(id).size();
    int key = getKey(id, size);

    for(int i = 0; i < hash_table[key].size(); i++){
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
