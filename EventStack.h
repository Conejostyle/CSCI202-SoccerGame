#ifndef EVENTSTACK_H
#define EVENTSTACK_H

#include "matchEvent.h"

class EventStackNode {
public:
    //Storing one match event inside a stack node.
    MatchEvent event;
    //Creating the pointer variable to the next event below it in the stack.
    EventStackNode* next;

    explicit EventStackNode(const MatchEvent& newEvent)
        : event(newEvent), next(nullptr) {
    }
};

class EventStack {
private:
    //Creating the top pointer for the stack so the newest event is resolved first.
    EventStackNode* top;

public:
    EventStack();
    ~EventStack();
    void push(const MatchEvent& event);
    MatchEvent pop();
    bool isEmpty() const;
};

#endif
