#include "PlayerQueue.h"

//Creating an empty queue before any players are added to the turn order.
PlayerQueue::PlayerQueue() : front(nullptr), rear(nullptr) {
}

//Removing any remaining queue nodes when the queue object is destroyed.
PlayerQueue::~PlayerQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

//Adding a player to the back of the queue so their turn comes later.
void PlayerQueue::enqueue(const Player& player) {
    PlayerQueueNode* newNode = new PlayerQueueNode(player);

    if (rear == nullptr) {
        front = newNode;
        rear = newNode;
        return;
    }

    rear->next = newNode;
    rear = newNode;
}

//Removing and returning the player at the front of the queue for the current turn.
Player PlayerQueue::dequeue() {
    PlayerQueueNode* temp = front;
    Player player = front->player;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    return player;
}

//Checking whether the queue has any players left in it.
bool PlayerQueue::isEmpty() const {
    return front == nullptr;
}
