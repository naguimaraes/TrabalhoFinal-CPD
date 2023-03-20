#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>

using std::string, std::vector;

typedef struct sRatedPlayer{
    string player_id{0};
    float player_rating{0};
}RatedPlayer;

class User
{
private:

    string id{0};
    RatedPlayer buffer_rated_player;
    vector<RatedPlayer> rated_player_vector;
    int partition(int left, int right);

public:

    string getId();
    void setId(string id);
    void insertRatedPlayer(RatedPlayer rated_player);
    void setRatedPlayer(string player_id, float player_rating);
    vector<RatedPlayer> getRatedPlayerVector();
    RatedPlayer getRatedPlayerBuffer();
    void sortRatedPlayerVector(int left, int right);
};


#endif