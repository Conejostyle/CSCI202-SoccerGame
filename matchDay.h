#ifndef MATCHDAY_H
#define MATCHDAY_H
#include <string>

class PlayerQueue;

class MatchDay {
    private:
        int tournamentRound = 1; // 1 for round of 16, 2 for quarterfinals, 3 for semifinals, 4 for final
        std::string userTeam;
        std::string opponentTeam;
        int userTeamScore = 0;
        int opponentTeamScore = 0;
    public:
        int getTournamentRound() const;
        std::string getUserTeam() const;
        std::string getOpponentTeam() const;
        int getUserTeamScore() const;
        int getOpponentTeamScore() const;

        void setTournamentRound(int round);
        void setUserTeam(const std::string& team);
        void setOpponentTeam(const std::string& team);
        void setUserTeamScore(int score);
        void setOpponentTeamScore(int score);

        std::string runMatch(PlayerQueue& turns, const std::string& stageName);
    };
#endif
