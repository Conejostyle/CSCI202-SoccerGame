#ifndef STAGENODE_H
#define STAGENODE_H

#include <string>

class StageNode {
public:
    //Storing the name of the current tournament stage.
    std::string stageName;
    //Storing the opponent tied to this stage.
    std::string opponentName;
    //Creating the pointer variable to the next stage in the linked list.
    StageNode* next;

    StageNode(const std::string& stage, const std::string& opponent)
        : stageName(stage), opponentName(opponent), next(nullptr) {
    }
};

#endif
