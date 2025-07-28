#include <cmath>
#include <string>
#include <vector>
#include "hashtable.hpp"

// HashPlayer implementation
int HashPlayer::getKey(const string& id, int size){
    long long int hash_key = 0;
    int a = 31;

    for(int i = 0; i < size; i++){
        hash_key += id[i] * pow(a, i);
    }
        
    hash_key %= HASH_SIZE;

    return hash_key;
}

// HashUser implementation  
int HashUser::getKey(const string& id, int size){
    long long int hash_key = 0;
    int a = 31;

    for(int i = 0; i < size; i++){
        hash_key += id[i] * pow(a, i);
    }
        
    hash_key %= HASH_SIZE;

    return hash_key;
}
