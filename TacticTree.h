#ifndef TACTICTREE_H
#define TACTICTREE_H

#include <string>

class TacticNode {
public:
    //Storing the tactic name used as the value in the tree.
    std::string tacticName;
    //Storing how much this tactic helps shot chance.
    int shootBonus;
    //Storing how much this tactic helps passing buildup.
    int passBonus;
    //Creating the left child pointer for the tree.
    TacticNode* left;
    //Creating the right child pointer for the tree.
    TacticNode* right;

    TacticNode(const std::string& name, int shoot, int pass)
        : tacticName(name), shootBonus(shoot), passBonus(pass), left(nullptr), right(nullptr) {
    }
};

class TacticTree {
private:
    TacticNode* root;

    void insert(TacticNode*& current, const std::string& name, int shootBonus, int passBonus);
    TacticNode* findNode(TacticNode* current, const std::string& name) const;
    void destroyTree(TacticNode* current);

public:
    TacticTree();
    ~TacticTree();
    void displayTactics() const;
    void chooseTacticByNumber(int choice, std::string& tacticName, int& shootBonus, int& passBonus) const;
};

#endif
