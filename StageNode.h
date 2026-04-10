#ifndef STAGENODE_H
#define STAGENODE_H

#include <string>

class StageNode {
public:
    std::string stageName;
    std::string opponentName;
    StageNode* next;

    StageNode(const std::string& stage, const std::string& opponent)
        : stageName(stage), opponentName(opponent), next(nullptr) {
    }
};

#endif
