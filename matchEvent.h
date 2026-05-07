#ifndef MATCHEVENT_H
#define MATCHEVENT_H
#include <string>
class MatchEvent {
private:
    //Storing the type of match event that is happening.
    std::string eventType;
    //std::string eventDescription;
    //Storing the base chance of a goal before player actions affect it.
    int chanceAtGoal;
    //Storing a possible follow-up chance value for future game expansion.
    int followUpEventChance;

public:
    std::string getEventType() const;
    //std::string getEventDescription() const;
    int getChanceAtGoal() const;
    int getFollowUpEventChance() const;

    void setEventType(const std::string& type);
    //void setEventDescription(const std::string& description);
    void setChanceAtGoal(int chance);
    void setFollowUpEventChance(int chance);
};
#endif // MATCHEVENT_H
