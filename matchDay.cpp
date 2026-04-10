#include "matchDay.h"
#include "EventStack.h"
#include "PlayerQueue.h"

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

std::string MatchDay::runMatch(PlayerQueue& turns, const std::string& stageName) {
    setUserTeamScore(0);
    setOpponentTeamScore(getTournamentRound() - 1);

    std::cout << "\n=== " << stageName << " ===" << std::endl;
    std::cout << getUserTeam() << " vs. " << getOpponentTeam() << std::endl;

    EventStack events;
    MatchEvent event1;
    event1.setEventType("Long Shot");
    event1.setChanceAtGoal(80);
    events.push(event1);

    MatchEvent event2;
    event2.setEventType("Corner Kick");
    event2.setChanceAtGoal(65);
    events.push(event2);

    MatchEvent event3;
    event3.setEventType("Breakaway");
    event3.setChanceAtGoal(55);
    events.push(event3);

    MatchEvent event4;
    event4.setEventType("Penalty Kick");
    event4.setChanceAtGoal(45);
    events.push(event4);

    while (!events.isEmpty()) {
        MatchEvent currentEvent = events.pop();
        Player currentPlayer = turns.dequeue();

        std::cout << currentPlayer.getName() << " takes the " << currentEvent.getEventType() << "." << std::endl;

        if (currentPlayer.getShootingStat() >= currentEvent.getChanceAtGoal()) {
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
