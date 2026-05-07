#ifndef MATCHDAY_H
#define MATCHDAY_H
#include <string>

class PlayerQueue;

class MatchDay {
    private:
        //Tracking which round of the tournament the player is currently in.
        int tournamentRound = 1; // 1 for round of 16, 2 for quarterfinals, 3 for semifinals, 4 for final
        //Storing the user's team name for the current match.
        std::string userTeam;
        //Storing the opponent team name for the current match.
        std::string opponentTeam;
        //Tracking how many goals the user's team has scored.
        int userTeamScore = 0;
        //Tracking how many goals the opponent team has scored.
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
