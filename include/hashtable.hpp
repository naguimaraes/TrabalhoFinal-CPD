#ifndef HASHTABLE_H
#define HASHTABLE_H 

#include <iostream>
#include <vector>
#include "player.hpp"
#include "user.hpp"
using std::string, std::vector;

// base hash table template
template<typename T>
class HashTable{
protected:
    vector<vector<T>> hash_table;
    int HASH_SIZE;
    
    // get hash key for string ID
    virtual int getKey(const string& id, int size) = 0;
    
public:
    HashTable(int size) : HASH_SIZE(size) {
        hash_table.resize(HASH_SIZE);
    }
    
    virtual ~HashTable() = default;
    
    // insert item into hash table
    virtual void insert(T& item) {
        int key = getKey(item.getId(), item.getId().size());
        
        // check if item exists
        for(size_t i = 0; i < hash_table[key].size(); i++) {
            if(hash_table[key][i].getId() == item.getId()) {
                handleExistingItem(hash_table[key][i], item);
                return;
            }
        }
        
        // add new item
        prepareNewItem(item);
        hash_table[key].push_back(item);
    }
    
    // search for item by ID
    T* search(const string& id) {
        int size = id.size();
        int key = getKey(id, size);

        for(size_t i = 0; i < hash_table[key].size(); i++) {
            if(hash_table[key][i].getId() == id)
                return &hash_table[key][i];
        }

        return nullptr;
    }
    
protected:
    // handle duplicate items
    virtual void handleExistingItem(T& existing, T& newItem) = 0;
    
    // prepare item before insertion
    virtual void prepareNewItem(T& item) = 0;
};

// player hash table
class HashPlayer: public HashTable<Player>{
private:
    int getKey(const string& id, int size) override;
    
protected:
    void handleExistingItem(Player& existing, Player& newItem) override {
        // ignore duplicates
        (void)existing;
        (void)newItem;
    }
    
    void prepareNewItem(Player& item) override {
        // no preparation needed
        (void)item;
    }
    
public:
    HashPlayer() : HashTable<Player>(static_cast<int>(1.5 * 18944)) {}
};

// user hash table
class HashUser: public HashTable<User>{
private:
    int getKey(const string& id, int size) override;
    
protected:
    void handleExistingItem(User& existing, User& newItem) override {
        // merge rated players
        existing.insertRatedPlayer(newItem.getRatedPlayerBuffer());
    }
    
    void prepareNewItem(User& item) override {
        // insert buffer before adding
        item.insertRatedPlayer(item.getRatedPlayerBuffer());
    }
    
public:
    HashUser() : HashTable<User>(static_cast<int>(1.3 * 24188078)) {}
};

#endif