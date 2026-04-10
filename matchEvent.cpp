#include "matchEvent.h"
//setters
void MatchEvent::setEventType(const std::string& type) {
    eventType = type;
}
void MatchEvent::setChanceAtGoal(int chance) {
    chanceAtGoal = chance;
}
void MatchEvent::setFollowUpEventChance(int chance) {
    followUpEventChance = chance;
}

//getters
std::string MatchEvent::getEventType() const {
    return eventType;
}
int MatchEvent::getChanceAtGoal() const {
    return chanceAtGoal;
}
int MatchEvent::getFollowUpEventChance() const {
    return followUpEventChance;
}