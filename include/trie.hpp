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
    vector<int> id_vector;
}TrieNode;

class Trie{
private:
    TrieNode *root;
    TrieNode *getNode(void);
    int partition(vector<int> &v, int left, int right);
    void sort(vector<int> &v, int left, int right);
public:
    Trie();
    vector<int> print_vector;
    void insert(string name, int id);
    void searchPrefix(string prefix);
    vector<int> findIntersection(int tags_number);
    void removeDuplicates(string str);
}; 

#endif