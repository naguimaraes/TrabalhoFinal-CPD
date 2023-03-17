#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>

using std::string, std::vector;

typedef struct sRatedPlayer{
    int player_id{0};
    float player_rating{0};
}RatedPlayer;

class User
{
private:

    int id{0};
    RatedPlayer buffer_rated_player;
    vector<RatedPlayer> rated_player_vector;

public:

    int getId();
    void setId(int id);
    void insertRatedPlayer(RatedPlayer rated_player);
    void setRatedPlayer(int player_id, float player_rating);
    vector<RatedPlayer> getRatedPlayerVector();
    RatedPlayer getRatedPlayerBuffer();
};


#endif