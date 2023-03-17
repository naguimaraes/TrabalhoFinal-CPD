#include <iostream>
#include <vector>
#include "player.hpp"
#include "user.hpp"
using std::string, std::vector;

// base hash class
class HashTable{
protected:
    const int HASH_SIZE = 28416;
    int getKey(int id, int size);
};


// player hash (inherit from base hash)
class HashPlayer: public HashTable{
private:
    vector<vector<Player>> hash_table;
public:
    void insert(Player player);
    Player* search(int id);
    HashPlayer();
};


// user hash (inherit from base hash)
class HashUser: public HashTable{
private:
    vector<vector<User>> hash_table;
public:
    void insert(User user);
    User* search(int id);
    HashUser();
};