#ifndef PLAYERQUEUE_H
#define PLAYERQUEUE_H

#include "player.h"

class PlayerQueueNode {
public:
    Player player;
    PlayerQueueNode* next;

    explicit PlayerQueueNode(const Player& newPlayer)
        : player(newPlayer), next(nullptr) {
    }
};

class PlayerQueue {
private:
    PlayerQueueNode* front;
    PlayerQueueNode* rear;

public:
    PlayerQueue();
    ~PlayerQueue();
    void enqueue(const Player& player);
    Player dequeue();
    bool isEmpty() const;
};

#endif
