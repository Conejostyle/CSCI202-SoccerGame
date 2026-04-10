#ifndef PLAYER_H
#define PLAYER_H
#include <string>
class Player {
private:
    std::string name;
    std::string position;
    int defendingStat;
    int passingStat;
    int shootingStat;
    int dribblingStat;

public:
    std::string getName() const;
    std::string getPosition() const;
    int getDefendingStat() const;
    int getPassingStat() const;
    int getShootingStat() const;
    int getDribblingStat() const;

    void setName(const std::string& playerName);
    void setPosition(const std::string& playerPosition);
    void setDefendingStat(int stat);
    void setPassingStat(int stat);
    void setShootingStat(int stat);
    void setDribblingStat(int stat);

};
#endif