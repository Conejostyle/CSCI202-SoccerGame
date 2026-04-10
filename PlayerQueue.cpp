#include "PlayerQueue.h"

PlayerQueue::PlayerQueue() : front(nullptr), rear(nullptr) {
}

PlayerQueue::~PlayerQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

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

bool PlayerQueue::isEmpty() const {
    return front == nullptr;
}
