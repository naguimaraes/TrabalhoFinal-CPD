#ifndef POSITIONS_H
#define POSITIONS_H

#include <iostream>
#include <vector>
#include "player.hpp"
#include "hashtable.hpp"
using std::string, std::vector;

typedef struct sTopRatedPlayers 
{
    string player_id;
    float player_rating{0};
}TopRatedPlayers;

class Positions
{
private:
    
    vector<vector<TopRatedPlayers>> top_positions_vector;
    vector<string> positions{"GK", "RB", "RWB", "CB",
                            "LB", "LWB", "CDM", "CM",
                            "CAM", "RM", "RW", "LM", 
                            "LW", "RF",	"CF", "LF",	"ST"};

    int getKey(string player_position);

public:
    
    void insert(string player_id, string positions);
    int partition(int left, int right, int positions);
    void sortTopPlayersVector(int left, int right, int positions);
    void getRatings(string position, HashPlayer player_hash);
    vector<TopRatedPlayers> getRatedPlayerVector(string position);
    Positions();
};

#endif