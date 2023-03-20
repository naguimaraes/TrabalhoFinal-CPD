#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

using std::string;

class Player{
private:
    string id;
    string name;
    string pos;
    float rating {0};
    int count {0};

public:

    // Getters

    // Returns the ID of the player.
    string getId();
    // Returns the full name of the player.
    string getName();
    // Returns the positions of the player.
    string getPositions();
    // Returns the average rating of the player.
    float getRating();
    // Returns number of ratings the player has been given.
    int getCount();

    // Setters

    // Sets the ID of the player.
    void setId(string player_id);
    // Sets the full name of the player.
    void setName(string player_name);
    // Sets the positions of the player.
    void setPositions(string player_position);
    // Sets the average rating of the player.
    void addRating(float player_rating);
};

#endif