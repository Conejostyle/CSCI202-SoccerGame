#ifndef EVENTSTACK_H
#define EVENTSTACK_H

#include "matchEvent.h"

class EventStackNode {
public:
    MatchEvent event;
    EventStackNode* next;

    explicit EventStackNode(const MatchEvent& newEvent)
        : event(newEvent), next(nullptr) {
    }
};

class EventStack {
private:
    EventStackNode* top;

public:
    EventStack();
    ~EventStack();
    void push(const MatchEvent& event);
    MatchEvent pop();
    bool isEmpty() const;
};

#endif
