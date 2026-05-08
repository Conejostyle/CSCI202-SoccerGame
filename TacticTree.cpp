#include "TacticTree.h"

#include <iostream>

//Creating a simple tree of tactics that can influence how the team attacks.
TacticTree::TacticTree() : root(nullptr) {
    insert(root, "Balanced Attack", 5, 5);
    insert(root, "Patient Build Up", 0, 10);
    insert(root, "Direct Attack", 10, 0);
}

//Removing the tactic tree nodes when the tree object is destroyed.
TacticTree::~TacticTree() {
    destroyTree(root);
}

void TacticTree::insert(TacticNode*& current, const std::string& name, int shootBonus, int passBonus) {
    if (current == nullptr) {
        current = new TacticNode(name, shootBonus, passBonus);
        return;
    }

    if (name < current->tacticName) {
        insert(current->left, name, shootBonus, passBonus);
    } else {
        insert(current->right, name, shootBonus, passBonus);
    }
}

TacticNode* TacticTree::findNode(TacticNode* current, const std::string& name) const {
    if (current == nullptr || current->tacticName == name) {
        return current;
    }

    if (name < current->tacticName) {
        return findNode(current->left, name);
    }

    return findNode(current->right, name);
}

void TacticTree::destroyTree(TacticNode* current) {
    if (current == nullptr) {
        return;
    }

    destroyTree(current->left);
    destroyTree(current->right);
    delete current;
}

//Displaying the tactics in a simple numbered list before the stage begins.
void TacticTree::displayTactics() const {
    std::cout << "1. Balanced Attack" << std::endl;
    std::cout << "2. Patient Build Up" << std::endl;
    std::cout << "3. Direct Attack" << std::endl;
}

//Looking up the chosen tactic inside the tree and returning its bonuses.
void TacticTree::chooseTacticByNumber(int choice, std::string& tacticName, int& shootBonus, int& passBonus) const {
    if (choice == 1) {
        tacticName = "Balanced Attack";
    } else if (choice == 2) {
        tacticName = "Patient Build Up";
    } else {
        tacticName = "Direct Attack";
    }

    TacticNode* selectedNode = findNode(root, tacticName);
    shootBonus = selectedNode->shootBonus;
    passBonus = selectedNode->passBonus;
}
