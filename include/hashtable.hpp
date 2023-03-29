#ifndef HASHTABLE_H
#define HASHTABLE_H 

#include <iostream>
#include <vector>
#include "player.hpp"
#include "user.hpp"
using std::string, std::vector;

// base hash class
class HashTable{
protected:
};


// player hash (inherit from base hash)
class HashPlayer: public HashTable{
private:
    vector<vector<Player>> hash_table;
    const int HASH_SIZE = 1.5*18944;
    int getKey(string id, int size);
public:
    void insert(Player player);
    Player* search(string id);
    HashPlayer();
};


// user hash (inherit from base hash)
class HashUser: public HashTable{
private:
    vector<vector<User>> hash_table;
    const int HASH_SIZE = 1.3*24188078;
    int getKey(string id, int size);
public:
    void insert(User user);
    User* search(string id);
    HashUser();
};

#endif