#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <string>
using std::string, std::vector;

// Includes all upper and lowercase letters and space character.
const int ALPHABET_SIZE = 91;

typedef struct sTrieNode
{
    struct sTrieNode *children[ALPHABET_SIZE];
    int id;
}TrieNode;

class Trie{
private:
    TrieNode *root;

    TrieNode *getNode(void);

public:
    Trie();
    vector<int> vector_id;

    // Inserts the given name in the Trie, using the player's ID as its leaf flag.
    void insert(string name, int id);

    // Returns the ID of the given player name, if it's stored in the Trie. If it isn't, returns "-1". 
    int search(string name);

    void searchPrefix(string prefix);
}; 

#endif