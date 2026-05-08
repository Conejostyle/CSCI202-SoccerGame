#include "InventoryHashTable.h"

#include <iostream>

//Creating an empty hash table before any inventory items are added.
InventoryHashTable::InventoryHashTable() {
    for (int bucket = 0; bucket < TABLE_SIZE; bucket++) {
        table[bucket] = nullptr;
    }
}

//Removing all chained inventory nodes when the hash table is destroyed.
InventoryHashTable::~InventoryHashTable() {
    clear();
}

int InventoryHashTable::hashFunction(const std::string& itemName) const {
    int total = 0;
    for (int index = 0; index < static_cast<int>(itemName.length()); index++) {
        total += itemName[index];
    }

    return total % TABLE_SIZE;
}

void InventoryHashTable::clear() {
    for (int bucket = 0; bucket < TABLE_SIZE; bucket++) {
        InventoryItemNode* current = table[bucket];

        while (current != nullptr) {
            InventoryItemNode* nextItem = current->next;
            delete current;
            current = nextItem;
        }

        table[bucket] = nullptr;
    }
}

//Adding starter items into the inventory by hashing them into a bucket.
void InventoryHashTable::addItem(const std::string& itemName, int quantity, int chanceBonus) {
    int bucket = hashFunction(itemName);
    InventoryItemNode* current = table[bucket];

    while (current != nullptr) {
        if (current->itemName == itemName) {
            current->quantity += quantity;
            return;
        }
        current = current->next;
    }

    InventoryItemNode* newItem = new InventoryItemNode(itemName, quantity, chanceBonus);
    newItem->next = table[bucket];
    table[bucket] = newItem;
}

//Using an item removes one copy and returns the bonus it gives for the current stage.
int InventoryHashTable::useItem(const std::string& itemName) {
    int bucket = hashFunction(itemName);
    InventoryItemNode* current = table[bucket];

    while (current != nullptr) {
        if (current->itemName == itemName && current->quantity > 0) {
            current->quantity--;
            return current->chanceBonus;
        }
        current = current->next;
    }

    return 0;
}

//Displaying the current inventory so the user can decide whether to use an item.
void InventoryHashTable::displayInventory() const {
    for (int bucket = 0; bucket < TABLE_SIZE; bucket++) {
        InventoryItemNode* current = table[bucket];

        while (current != nullptr) {
            std::cout << current->itemName << " (x" << current->quantity << ") gives +"
                      << current->chanceBonus << " chance." << std::endl;
            current = current->next;
        }
    }
}
