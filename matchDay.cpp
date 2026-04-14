#include "matchDay.h"
#include "EventStack.h"
#include "PlayerQueue.h"

#include <cstdlib>
#include <iostream>
//setters
void MatchDay::setTournamentRound(int round) {
    tournamentRound = round;
}
void MatchDay::setUserTeam(const std::string& team) {
    userTeam = team;
}
void MatchDay::setOpponentTeam(const std::string& team) {
    opponentTeam = team;
}
void MatchDay::setUserTeamScore(int score) {
    userTeamScore = score;
}
void MatchDay::setOpponentTeamScore(int score) {
    opponentTeamScore = score;
}

//getters
int MatchDay::getTournamentRound() const {
    return tournamentRound;
}
std::string MatchDay::getUserTeam() const {
    return userTeam;
}
std::string MatchDay::getOpponentTeam() const {
    return opponentTeam;
}
int MatchDay::getUserTeamScore() const {
    return userTeamScore;
}
int MatchDay::getOpponentTeamScore() const {
    return opponentTeamScore;
}

//MatchDay does most of the carrying for the game logic itself.
std::string MatchDay::runMatch(PlayerQueue& turns, const std::string& stageName) {
    setUserTeamScore(0);
    setOpponentTeamScore(getTournamentRound() - 1);

    std::cout << "\n=== " << stageName << " ===" << std::endl;
    std::cout << getUserTeam() << " vs. " << getOpponentTeam() << std::endl;

    EventStack events;
    MatchEvent event1;
    event1.setEventType("Long Shot");
    event1.setChanceAtGoal(75);
    events.push(event1);

    MatchEvent event2;
    event2.setEventType("Corner Kick");
    event2.setChanceAtGoal(10);
    events.push(event2);

    MatchEvent event3;
    event3.setEventType("Counter Attack Opportunity");
    event3.setChanceAtGoal(70);
    events.push(event3);

    MatchEvent event4;
    event4.setEventType("Penalty Kick");
    event4.setChanceAtGoal(85);
    events.push(event4);

    MatchEvent event5;
    event5.setEventType("Free Kick");
    event5.setChanceAtGoal(70);
    events.push(event5);

    MatchEvent event6;
    event6.setEventType("One-on-One with Goalkeeper");
    event6.setChanceAtGoal(90);
    events.push(event6);

    MatchEvent event7;
    event7.setEventType("Defender's Clearance");
    event7.setChanceAtGoal(20);
    events.push(event7);

    while (!events.isEmpty()) {
        MatchEvent currentEvent = events.pop();
        Player currentPlayer = turns.dequeue();
        std::cout << currentEvent.getEventType() << "!" << std::endl;
        std::cout << currentPlayer.getName() << " has the ball..." << std::endl;

        int playerChoice = 0;
        while (playerChoice != 1 && playerChoice != 2) {
            std::cout << "Enter 1 to shoot or 2 to pass: ";
            std::cin >> playerChoice;
        }

        int eventChance = currentEvent.getChanceAtGoal();

        if (playerChoice == 2) {
            int interceptRoll = rand() % 100 + 1;

            if (interceptRoll <= 25) {
                std::cout << "The pass was intercepted!" << std::endl;
                turns.enqueue(currentPlayer);
                continue;
            } else {
                std::cout << "Pass completed successfully!" << std::endl;
                eventChance += 15;

                if (eventChance > 95) {
                    eventChance = 95;
                }
            }
        }

        int finalChance = (currentPlayer.getShootingStat() * eventChance) / 100;
        int shotRoll = rand() % 100 + 1;

        std::cout << "Shot success chance: " << finalChance << "/100" << std::endl;

        if (shotRoll <= finalChance) {
            std::cout << "Goal for " << getUserTeam() << "!" << std::endl;
            setUserTeamScore(getUserTeamScore() + 1);
        } else {
            std::cout << "No goal on this chance." << std::endl;
        }

        turns.enqueue(currentPlayer);
    }

    std::cout << "Final Score: " << getUserTeam() << " " << getUserTeamScore()
              << " - " << getOpponentTeamScore() << " " << getOpponentTeam() << std::endl;

    if (getUserTeamScore() >= getOpponentTeamScore()) {
        return "Congratulations! You won the match!";
    }

    return "Sorry, you lost the match. The journey ends here...";
}
