#ifndef MATCHEVENT_H
#define MATCHEVENT_H
#include <string>
class MatchEvent {
private:
    std::string eventType;
    //std::string eventDescription;
    int chanceAtGoal;
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