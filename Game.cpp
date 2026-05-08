#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "PlayerQueue.h"

Game::Game() : stageHead(nullptr) {
}

void Game::showWelcome() const {
    std::cout << "Welcome to the Soccer Game Simulation!" << std::endl;
    std::cout << "You will begin by simulating games, starting at the round of 16." << std::endl;
    std::cout << "Your goal is to win the final and become the champion!" << std::endl;
}

void Game::showInstructions() const {
    std::cout << "Instructions: " << std::endl;
    std::cout << "1. Five tournament stages are stored in a linked list." << std::endl;
    std::cout << "2. Match events are stored in a stack and resolved one by one." << std::endl;
    std::cout << "3. Your four players take turns through a queue." << std::endl;
    std::cout << "4. Your goal is to win the final and become the champion!" << std::endl;
}

void Game::setupTeam() {
    //Creating the team name and storing it in the MatchDay object so every stage can use it.
    std::string teamName;
    std::cout << "Enter your team name: ";
    getline(std::cin, teamName);
    matchDay.setUserTeam(teamName);

    //Creating the player roster, with names as inputs, and setting their default stats.
    setupPlayers();

    //Loading the starter inventory into the hash table before the tournament begins.
    setupInventory();
}

void Game::setupPlayers() {
    //Setting fixed shooting stats by position so match events can resolve simply for NOW.
    std::cout << "Enter your goalkeeper's name: ";
    std::string gkName;
    getline(std::cin, gkName);
    goalKeeper.setName(gkName);
    goalKeeper.setPosition("Goalkeeper");
    goalKeeper.setShootingStat(35);

    std::cout << "Enter your defender's name: ";
    std::string defenderName;
    getline(std::cin, defenderName);
    defender.setName(defenderName);
    defender.setPosition("Defender");
    defender.setShootingStat(50);

    std::cout << "Enter your midfielder's name: ";
    std::string midfielderName;
    getline(std::cin, midfielderName);
    midfielder.setName(midfielderName);
    midfielder.setPosition("Midfielder");
    midfielder.setShootingStat(70);

    std::cout << "Enter your forward's name: ";
    std::string forwardName;
    getline(std::cin, forwardName);
    forward.setName(forwardName);
    forward.setPosition("Forward");
    forward.setShootingStat(90);
}

void Game::setupInventory() {
    //Clearing any old item data so a new tournament starts with a fresh inventory.
    inventory.clear();

    //Adding a few simple inventory items into the hash table for the user to use between stages.
    inventory.addItem("Power Boots", 1, 10);
    inventory.addItem("Team Talk", 1, 5);
    inventory.addItem("Lucky Tape", 1, 15);
}

void Game::buildStages() {
    //Creating the linked list nodes that represent the five tournament stages.
    StageNode* stage1 = new StageNode("Round of 16", "Roma FC");
    StageNode* stage2 = new StageNode("Quarterfinal", "Manchester Reds");
    StageNode* stage3 = new StageNode("Semifinal", "Milan FC");
    StageNode* stage4 = new StageNode("Final", "Barcha");
    StageNode* stage5 = new StageNode("Champion Match", "Legends FC");

    //Linking each stage to the next one to form the full tournament path.
    stage1->next = stage2;
    stage2->next = stage3;
    stage3->next = stage4;
    stage4->next = stage5;

    stageHead = stage1;
}

void Game::playTournament() {
    //Creating a fresh queue for this tournament so player turns rotate cleanly each new run.
    PlayerQueue turns;
    turns.enqueue(goalKeeper);
    turns.enqueue(defender);
    turns.enqueue(midfielder);
    turns.enqueue(forward);

    //Walking through the linked list one stage at a time until the tournament ends.
    StageNode* currentStage = stageHead;
    int roundNumber = 1;

    while (currentStage != nullptr) {
        matchDay.setTournamentRound(roundNumber);
        matchDay.setOpponentTeam(currentStage->opponentName);

        //Asking the user to choose a tactic from the tactic tree before the stage begins.
        std::cout << "\nChoose a tactic for this stage:" << std::endl;
        tactics.displayTactics();
        int tacticChoice = 0;
        while (tacticChoice < 1 || tacticChoice > 3) {
            std::cout << "Enter 1, 2, or 3: ";
            std::cin >> tacticChoice;
        }

        std::string tacticName;
        int shootBonus = 0;
        int passBonus = 0;
        tactics.chooseTacticByNumber(tacticChoice, tacticName, shootBonus, passBonus);
        std::cout << "Tactic selected: " << tacticName << std::endl;

        //Showing the inventory hash table and giving the user a chance to use one item before the match.
        std::cout << "\nInventory available before the match:" << std::endl;
        inventory.displayInventory();
        std::cout << "0. No item" << std::endl;
        std::cout << "1. Power Boots" << std::endl;
        std::cout << "2. Team Talk" << std::endl;
        std::cout << "3. Lucky Tape" << std::endl;

        int itemChoice = -1;
        while (itemChoice < 0 || itemChoice > 3) {
            std::cout << "Choose an item to use before the stage: ";
            std::cin >> itemChoice;
        }

        int itemBonus = 0;
        if (itemChoice == 1) {
            itemBonus = inventory.useItem("Power Boots");
            std::cout << "Power Boots used for a +" << itemBonus << " chance bonus." << std::endl;
        } else if (itemChoice == 2) {
            itemBonus = inventory.useItem("Team Talk");
            std::cout << "Team Talk used for a +" << itemBonus << " chance bonus." << std::endl;
        } else if (itemChoice == 3) {
            itemBonus = inventory.useItem("Lucky Tape");
            std::cout << "Lucky Tape used for a +" << itemBonus << " chance bonus." << std::endl;
        } else {
            std::cout << "No item used before this stage." << std::endl;
        }

        // std::string result = matchDay.runMatch(turns, currentStage->stageName);
        std::string result = matchDay.runMatch(turns, currentStage->stageName, shootBonus, passBonus, itemBonus);
        std::cout << result << std::endl;

        if (result.find("lost") != std::string::npos) {
            break;
        }

        currentStage = currentStage->next;
        roundNumber++;
    }
}

void Game::cleanupStages() {
    //Deleting each linked-list node so the dynamically created stages do not remain in memory.
    StageNode* currentStage = stageHead;

    while (currentStage != nullptr) {
        StageNode* nextStage = currentStage->next;
        delete currentStage;
        currentStage = nextStage;
    }

    stageHead = nullptr;
}

void Game::start() {
    //Seeding random values once so event outcomes do not repeat every run.
    srand(static_cast<unsigned int>(time(0)));

    showWelcome();

    int userChoice = 0;
    while (userChoice != 3) {
        std::cout << "Press 1 to start the simulation." << std::endl;
        std::cout << "Press 2 for instructions." << std::endl;
        std::cout << "Press 3 to exit." << std::endl;
        std::cin >> userChoice;
        std::cin.ignore();

        if (userChoice == 1) {
            std::cout << "Starting the simulation..." << std::endl;

            setupTeam();
            buildStages();
            playTournament();
            cleanupStages();
        }
        else if (userChoice == 2) {
            showInstructions();
        }
        else if (userChoice != 3) {
            std::cout << "Please enter a valid choice (1, 2, or 3)." << std::endl;
        }
    }

    std::cout << "Thanks for playing!" << std::endl;
}
