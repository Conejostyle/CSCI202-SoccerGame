#include "EventStack.h"

EventStack::EventStack() : top(nullptr) {
}

EventStack::~EventStack() {
    while (!isEmpty()) {
        pop();
    }
}

void EventStack::push(const MatchEvent& event) {
    EventStackNode* newNode = new EventStackNode(event);
    newNode->next = top;
    top = newNode;
}

MatchEvent EventStack::pop() {
    EventStackNode* temp = top;
    MatchEvent event = top->event;
    top = top->next;
    delete temp;
    return event;
}

bool EventStack::isEmpty() const {
    return top == nullptr;
}
