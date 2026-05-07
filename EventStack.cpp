#include "EventStack.h"

//Creating an empty stack before match events are loaded into it.
EventStack::EventStack() : top(nullptr) {
}

//Removing any remaining stack nodes when the stack object is destroyed.
EventStack::~EventStack() {
    while (!isEmpty()) {
        pop();
    }
}

//Placing a new event on top of the stack for the match to resolve later.
void EventStack::push(const MatchEvent& event) {
    EventStackNode* newNode = new EventStackNode(event);
    newNode->next = top;
    top = newNode;
}

//Removing and returning the event on top of the stack.
MatchEvent EventStack::pop() {
    EventStackNode* temp = top;
    MatchEvent event = top->event;
    top = top->next;
    delete temp;
    return event;
}

//Checking whether there are any events left to resolve.
bool EventStack::isEmpty() const {
    return top == nullptr;
}
