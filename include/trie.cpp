#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "trie.hpp"
using std::string, std::to_string, std::cout, std::vector;

TrieNode* Trie::getNode(void)
{
    TrieNode *pNode =  new TrieNode;
 
    pNode->id = -1;
 
    for (int i = 0; i < ALPHABET_SIZE; i++){
        pNode->children[i] = NULL;
    }
    return pNode;
}
Trie::Trie()
{
    root = getNode();
}

    // Inserts the given name in the Trie, using the player's ID as its leaf flag.
void Trie::insert(string name, int id)
 {
    TrieNode *pAux = root;

    for (int i = 0; i < name.length(); i++)
    {
        int index = name[i] - ' ';
        if (!pAux->children[index]){
                pAux->children[index] = getNode();
        }
        
        pAux = pAux->children[index];
    }

        pAux->id = id;
    }

    // Returns the ID of the given player name, if it's stored in the Trie. If it isn't, returns "-1". 
int Trie::search(string name)
{
    TrieNode *pAux = root;
    
    for (int i = 0; i < name.length(); i++)
    {
        int index = name[i] - ' ';
        if (!pAux->children[index]){
                return -1;
        }
    
        pAux = pAux->children[index];
    }
    
    return (pAux->id);
}

// Stores in the vector_id all the player's ID whose name starts with the given prefix.
void Trie::searchPrefix(string prefix){
    
    TrieNode *pAux = root;
    int i;
    int length = prefix.length();
    
    for (i = 0; i < length; i++){
        int index = prefix[i] - ' ';
        if(pAux->children[index] != NULL){
            pAux = pAux->children[index];
        }
        else{
            break;
        }
    }

    if(i == length){
        for(int j = 0; j < ALPHABET_SIZE; j++){
            if(pAux->children[j] != NULL){
                char c = j + ' ' + 0;
                searchPrefix(prefix + c);
            }
        }
    
        if(pAux->id != -1){
            vector_id.push_back(pAux->id);
        }
    }
    else{
        vector_id.clear();
    }
}
