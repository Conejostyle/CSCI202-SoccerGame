#ifndef GAME_H
#define GAME_H

#include "InventoryHashTable.h"
#include "matchDay.h"
#include "StageNode.h"
#include "TacticTree.h"
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

    //Creating the inventory hash table that stores stage-use items for the team.
    InventoryHashTable inventory;
    //Creating the tactic tree that stores strategic options before each stage.
    TacticTree tactics;

    //Creating the head pointer for the linked list of tournament stages.
    StageNode* stageHead;

    void showWelcome() const;
    void showInstructions() const;
    void setupTeam();
    void setupPlayers();
    void setupInventory();
    void buildStages();
    void playTournament();
    void cleanupStages();

public:
    Game();
    void start();
};

#endif
