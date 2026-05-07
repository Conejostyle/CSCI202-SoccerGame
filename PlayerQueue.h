#ifndef PLAYERQUEUE_H
#define PLAYERQUEUE_H

#include "player.h"

class PlayerQueueNode {
public:
    //Storing one player inside a queue node.
    Player player;
    //Creating the pointer variable to the next player in the queue.
    PlayerQueueNode* next;

    explicit PlayerQueueNode(const Player& newPlayer)
        : player(newPlayer), next(nullptr) {
    }
};

class PlayerQueue {
private:
    //Creating the front pointer for the queue so turns are taken in order.
    PlayerQueueNode* front;
    //Creating the rear pointer so new players can be added to the back of the queue.
    PlayerQueueNode* rear;

public:
    PlayerQueue();
    ~PlayerQueue();
    void enqueue(const Player& player);
    Player dequeue();
    bool isEmpty() const;
};

#endif
