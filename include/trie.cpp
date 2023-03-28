#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include "trie.hpp"
using std::string, std::to_string, std::cout, std::vector;

TrieNode* Trie::getNode(void)
{
    TrieNode *pNode =  new TrieNode;
 
    pNode->id_vector.clear();
 
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
    int count = 0;

    for (int i = 0; i < name.length(); i++){
        int index = name[i] - ' ';
        if (!pAux->children[index]){
                pAux->children[index] = getNode();
        }
        
        pAux = pAux->children[index];
    }

    pAux->id_vector.push_back(id);
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
    
        if(pAux->id_vector.size() > 0){
            for(int i = 0; i < (pAux->id_vector.size()); i++){
                print_vector.push_back(pAux->id_vector[i]);
            }
        }
    }
}

int Trie::partition(vector<int> &v ,int left, int right){
    int key, i, j;
    key = v[left]; i = left; j = right;

    while (i<j) {
        while(v[j] > key && i < j) j--;
        {
            v[i] = v[j];
        }
        while(v[i] <= key && i < j) i++ ;
        {
            v[j] = v[i];
        }
    }
    v[j] = key;
    return i;
}

void Trie::sort(vector<int> &v, int left, int right){
    if (left < right) {   
        int pi = partition(v ,left, right);

        sort(v, left, pi - 1);
        sort(v, pi + 1, right);
    }
}

vector<int> Trie::findIntersection(int tags_number){
    int count = 0;
    vector<int> intersection;
    sort(print_vector, 0, print_vector.size()-1);



    for(int i = 0; i < print_vector.size(); i++){
        if(print_vector[i] == print_vector[i+1]){
            count++;
        }
        else{
            count = 0;
        }
        if(count == tags_number-1){
            intersection.push_back(print_vector[i]);
        }
    }

    return intersection;
}

void Trie::removeDuplicates(string str){
    TrieNode *pAux = root;
    vector<int>::iterator it;
    
    for (int i = 0; i < str.length(); i++)
    {
        int index = str[i] - ' ';
        if (!pAux->children[index]){
            return;
        }
    
        pAux = pAux->children[index];
    }
    
    sort(pAux->id_vector, 0, pAux->id_vector.size()-1);


    pAux->id_vector.erase(std::unique(pAux->id_vector.begin(), pAux->id_vector.end()), pAux->id_vector.end());

}
