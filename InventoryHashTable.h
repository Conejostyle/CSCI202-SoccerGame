#ifndef INVENTORYHASHTABLE_H
#define INVENTORYHASHTABLE_H

#include <string>

class InventoryItemNode {
public:
    //Storing the item name as the key used by the hash table.
    std::string itemName;
    //Storing how many copies of that item are in the inventory.
    int quantity;
    //Storing the bonus that item gives when used.
    int chanceBonus;
    //Creating the pointer to the next item in the same bucket chain.
    InventoryItemNode* next;

    InventoryItemNode(const std::string& name, int itemQuantity, int bonus)
        : itemName(name), quantity(itemQuantity), chanceBonus(bonus), next(nullptr) {
    }
};

class InventoryHashTable {
private:
    //Creating a fixed number of buckets for the hash table.
    static const int TABLE_SIZE = 7;
    InventoryItemNode* table[TABLE_SIZE];

    int hashFunction(const std::string& itemName) const;

public:
    InventoryHashTable();
    ~InventoryHashTable();
    void clear();
    void addItem(const std::string& itemName, int quantity, int chanceBonus);
    int useItem(const std::string& itemName);
    void displayInventory() const;
};

#endif
