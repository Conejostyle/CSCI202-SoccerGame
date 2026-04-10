/*
    Program name: Soccer Game Simulation
    Author: Benjamin Munoz
    Date last updated: 4/10/2026
    Purpose: This program simulates a soccer tournament, match by match as an RPG type of game.
*/
#include "player.h"
#include "matchDay.h"
#include "PlayerQueue.h"
#include "StageNode.h"

#include <iostream>

int main(){
    std::cout << "Welcome to the Soccer Game Simulation!" << std::endl;
    std::cout << "You will begin by simulating games, starting at the round of 16." << std::endl;
    std::cout << "Your goal is to win the final and become the champion!" << std::endl;
    int userChoice = 0;
    while (userChoice != 3){
        std::cout << "Press 1 to start the simulation." << std::endl;
        std::cout << "Press 2 for instructions." << std::endl;
        std::cout << "Press 3 to exit." << std::endl;
        std::cin >> userChoice;
        if (userChoice == 1) {
            std::cout << "Starting the simulation..." << std::endl;

            MatchDay matchDay;
            std::string teamName;
            std::cout << "Enter your team name: ";
            std::cin >> teamName;
            matchDay.setUserTeam(teamName);

            Player goalKeeper;
            Player defender;
            Player midfielder;
            Player forward;

            std::cout << "Enter your goalkeeper's name: ";
            std::string gkName;
            std::cin >> gkName;
            goalKeeper.setName(gkName);
            goalKeeper.setPosition("Goalkeeper");
            goalKeeper.setShootingStat(35);

            std::cout << "Enter your defender's name: ";
            std::string defenderName;
            std::cin >> defenderName;
            defender.setName(defenderName);
            defender.setPosition("Defender");
            defender.setShootingStat(50);

            std::cout << "Enter your midfielder's name: ";
            std::string midfielderName;
            std::cin >> midfielderName;
            midfielder.setName(midfielderName);
            midfielder.setPosition("Midfielder");
            midfielder.setShootingStat(70);

            std::cout << "Enter your forward's name: ";
            std::string forwardName;
            std::cin >> forwardName;
            forward.setName(forwardName);
            forward.setPosition("Forward");
            forward.setShootingStat(90);

            PlayerQueue turns;
            turns.enqueue(goalKeeper);
            turns.enqueue(defender);
            turns.enqueue(midfielder);
            turns.enqueue(forward);

            StageNode* stage1 = new StageNode("Round of 16", "Roma FC");
            StageNode* stage2 = new StageNode("Quarterfinal", "Manchester Reds");
            StageNode* stage3 = new StageNode("Semifinal", "Milan FC");
            StageNode* stage4 = new StageNode("Final", "Barcha");
            StageNode* stage5 = new StageNode("Champion Match", "Legends FC");

            stage1->next = stage2;
            stage2->next = stage3;
            stage3->next = stage4;
            stage4->next = stage5;

            StageNode* currentStage = stage1;
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

            delete stage5;
            delete stage4;
            delete stage3;
            delete stage2;
            delete stage1;
        }
        else if (userChoice == 2) {
            std::cout << "Instructions: " << std::endl;
            std::cout << "1. Five tournament stages are stored in a linked list." << std::endl;
            std::cout << "2. Match events are stored in a stack and resolved one by one." << std::endl;
            std::cout << "3. Your four players take turns through a queue." << std::endl;
            std::cout << "4. Your goal is to win the final and become the champion!" << std::endl;
        }
        else if (userChoice != 3) {
            std::cout << "Please enter a valid choice (1, 2, or 3)." << std::endl;
        }
    }
    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}
