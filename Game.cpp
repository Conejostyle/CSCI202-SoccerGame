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
    getline(std::cin >> std::ws, teamName);
    matchDay.setUserTeam(teamName);

    //Creating the player roster, with names as inputs, and setting their default stats.
    setupPlayers();
}

void Game::setupPlayers() {
    //Setting fixed shooting stats by position so match events can resolve simply for NOW.
    std::cout << "Enter your goalkeeper's name: ";
    std::string gkName;
    getline(std::cin >> std::ws, gkName);
    goalKeeper.setName(gkName);
    goalKeeper.setPosition("Goalkeeper");
    goalKeeper.setShootingStat(35);

    std::cout << "Enter your defender's name: ";
    std::string defenderName;
    getline(std::cin >> std::ws, defenderName);
    defender.setName(defenderName);
    defender.setPosition("Defender");
    defender.setShootingStat(50);

    std::cout << "Enter your midfielder's name: ";
    std::string midfielderName;
    getline(std::cin >> std::ws, midfielderName);
    midfielder.setName(midfielderName);
    midfielder.setPosition("Midfielder");
    midfielder.setShootingStat(70);

    std::cout << "Enter your forward's name: ";
    std::string forwardName;
    getline(std::cin >> std::ws, forwardName);
    forward.setName(forwardName);
    forward.setPosition("Forward");
    forward.setShootingStat(90);
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

        std::string result = matchDay.runMatch(turns, currentStage->stageName);
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
