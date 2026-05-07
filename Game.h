#ifndef GAME_H
#define GAME_H

#include "matchDay.h"
#include "StageNode.h"
#include "player.h"

#include <string>

class Game {
private:
    MatchDay matchDay;

    //Creating the four player objects that will make up the user's team.
    Player goalKeeper;
    Player defender;
    Player midfielder;
    Player forward;

    //Creating the head pointer for the linked list of tournament stages.
    StageNode* stageHead;

    void showWelcome() const;
    void showInstructions() const;
    void setupTeam();
    void setupPlayers();
    void buildStages();
    void playTournament();
    void cleanupStages();

public:
    Game();
    void start();
};

#endif
