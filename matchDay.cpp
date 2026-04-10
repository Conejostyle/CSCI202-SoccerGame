#include "matchDay.h"
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
