#include "matchDay.h"
#include "EventStack.h"
#include "FieldGraph.h"
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
// std::string MatchDay::runMatch(PlayerQueue& turns, const std::string& stageName) {
std::string MatchDay::runMatch(PlayerQueue& turns, const std::string& stageName, int shootBonus, int passBonus, int itemBonus) {
    setUserTeamScore(0);
    setOpponentTeamScore(getTournamentRound() - 1);

    std::cout << "\n=== " << stageName << " ===" << std::endl;
    std::cout << getUserTeam() << " vs. " << getOpponentTeam() << std::endl;

    //Creating the event stack so this match resolves its events in stack order.
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

    //Running the match one event at a time until the stack is empty.
    while (!events.isEmpty()) {
        MatchEvent currentEvent = events.pop();

        //Taking the next player from the front of the queue for the current turn.
        Player currentPlayer = turns.dequeue();
        std::cout << currentEvent.getEventType() << "!" << std::endl;
        std::cout << currentPlayer.getName() << " has the ball..." << std::endl;

        //Creating the field graph so the ball can move through connected zones during this event.
        FieldGraph fieldGraph;
        int currentZone = fieldGraph.getStartZone();
        int successfulPasses = 0;
        bool playerHasBall = true;

        //Keeping the same event active until the player shoots or the ball is intercepted.
        while (playerHasBall) {
            //Rebuilding the current chance from the base event, successful passes, field zone, tactic, and item.
            // int eventChance = currentEvent.getChanceAtGoal();
            int currentChanceAtGoal = currentEvent.getChanceAtGoal()
                + successfulPasses * (15 + passBonus)
                + fieldGraph.getZoneBonus(currentZone)
                + itemBonus;

            if (currentChanceAtGoal > 95) {
                currentChanceAtGoal = 95;
            }

            std::cout << "Current zone: " << fieldGraph.getZoneName(currentZone) << std::endl;
            std::cout << "Current chance at goal: " << currentChanceAtGoal << "%" << std::endl;

            int playerChoice = 0;
            while (playerChoice != 1 && playerChoice != 2) {
                std::cout << "Enter 1 to shoot or 2 to pass: ";
                std::cin >> playerChoice;
            }

            //Passing gives the player a chance to increase their shooting chance, but also a risk of losing the ball.
            if (playerChoice == 2) {
                //Basically there's a chance to lose the ball on a pass, which is a pretty big risk, but the reward is a 15% increase in shooting chance.
                int interceptRoll = rand() % 100 + 1;

                //ADJUST
                //ADJUST
                //ADJUST
                //Adjusting this consistently until it feels balanced!!!!
                if (interceptRoll <= 40) { // <-- ADJUST <--
                    std::cout << "The pass was intercepted!" << std::endl;

                    //Giving the opponent a small chance to score immediately after winning the ball.
                    int opponentCounterRoll = rand() % 3; // 0, 1, or 2 for a 1 in 3 chance at a counter-attack goal.
                    if (opponentCounterRoll == 0) {
                        std::cout << getOpponentTeam() << " scores on the counter attack!" << std::endl;
                        setOpponentTeamScore(getOpponentTeamScore() + 1);
                        std::cout << "Current Score: " << getUserTeam() << " " << getUserTeamScore()
                                  << " - " << getOpponentTeam() << " " << getOpponentTeamScore() << std::endl;
                    } else {
                        std::cout << getOpponentTeam() << " does not score from the interception." << std::endl;
                    }

                    playerHasBall = false;
                } else {
                    std::cout << "Pass completed successfully!" << std::endl;
                    successfulPasses++;

                    //Allowing the player to move the ball only to connected zones in the field graph.
                    std::cout << "Choose the next zone for the pass:" << std::endl;
                    fieldGraph.displayMoves(currentZone);

                    int moveChoice = 0;
                    int nextZone = -1;
                    while (nextZone == -1) {
                        std::cout << "Enter your move choice: ";
                        std::cin >> moveChoice;
                        nextZone = fieldGraph.getConnectedZoneByChoice(currentZone, moveChoice);
                    }
                    currentZone = nextZone;

                    //Rotating the ball to the next player in the queue after a successful pass.
                    turns.enqueue(currentPlayer);
                    currentPlayer = turns.dequeue();
                    std::cout << currentPlayer.getName() << " now has the ball..." << std::endl;
                }
            } else {
                //Shooting depends only on the player's shooting stat and the current chance at goal.
                int shotChance = currentChanceAtGoal + shootBonus;
                if (shotChance > 95) {
                    shotChance = 95;
                }

                int finalChance = (currentPlayer.getShootingStat() * shotChance) / 100;
                int shotRoll = rand() % 100 + 1;

                std::cout << "Shot success chance: " << finalChance << "/100" << std::endl;

                if (shotRoll <= finalChance) {
                    std::cout << "Goal for " << getUserTeam() << "!" << std::endl;
                    setUserTeamScore(getUserTeamScore() + 1);
                    std::cout << "Current Score: " << getUserTeam() << " " << getUserTeamScore()
                              << " - " << getOpponentTeam() << " " << getOpponentTeamScore() << std::endl;
                } else {
                    std::cout << "No goal on this chance." << std::endl;
                }

                playerHasBall = false;
            }
        }

        //Placing the current player at the back of the queue after their turn is over.
        turns.enqueue(currentPlayer);
    }

    std::cout << "Final Score: " << getUserTeam() << " " << getUserTeamScore()
              << " - " << getOpponentTeamScore() << " " << getOpponentTeam() << std::endl;

    if (getUserTeamScore() > getOpponentTeamScore()) {
        return "Congratulations! You won the match!";
    }
    else if(getUserTeamScore() == getOpponentTeamScore()) {
        std::cout << "It's a draw! On to penalties..." << std::endl;
        //50/50 chance to win the penalty shootout for simplicity.
        int penaltyRoll = rand() % 2; // 0 or 1 for a 50% chance at winning the shootout.
        if (penaltyRoll == 0) {
            return "Congratulations! You won the match!";
        }
        else {
            return "Sorry, you lost the match. The journey ends here...";
        }
    }

    return "Sorry, you lost the match. The journey ends here...";
}
