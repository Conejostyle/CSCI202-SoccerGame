#include "FieldGraph.h"

#include <iostream>

//Creating the graph that maps where the ball can move on the field.
FieldGraph::FieldGraph() {
    for (int row = 0; row < ZONE_COUNT; row++) {
        for (int column = 0; column < ZONE_COUNT; column++) {
            connections[row][column] = false;
        }
    }

    zoneNames[0] = "Defense";
    zoneNames[1] = "Midfield";
    zoneNames[2] = "Wing";
    zoneNames[3] = "Box";
    zoneNames[4] = "Goal Chance";

    zoneBonuses[0] = 0;
    zoneBonuses[1] = 0;
    zoneBonuses[2] = 10;
    zoneBonuses[3] = 20;
    zoneBonuses[4] = 30;

    //Connecting the field zones so the user can only move the ball along valid paths.
    connectZones(0, 1);
    connectZones(1, 0);
    connectZones(1, 2);
    connectZones(2, 1);
    connectZones(1, 3);
    connectZones(3, 1);
    connectZones(2, 3);
    connectZones(3, 2);
    connectZones(3, 4);
    connectZones(4, 3);
}

void FieldGraph::connectZones(int fromZone, int toZone) {
    connections[fromZone][toZone] = true;
}

//Starting every event in midfield so the attacking play can build from there.
int FieldGraph::getStartZone() const {
    return 1;
}

std::string FieldGraph::getZoneName(int zoneIndex) const {
    return zoneNames[zoneIndex];
}

int FieldGraph::getZoneBonus(int zoneIndex) const {
    return zoneBonuses[zoneIndex];
}

bool FieldGraph::canMove(int fromZone, int toZone) const {
    return connections[fromZone][toZone];
}

//Displaying the valid next zones the ball can move to from the current location.
void FieldGraph::displayMoves(int fromZone) const {
    int optionNumber = 1;
    for (int zoneIndex = 0; zoneIndex < ZONE_COUNT; zoneIndex++) {
        if (connections[fromZone][zoneIndex]) {
            std::cout << optionNumber << ". " << zoneNames[zoneIndex] << std::endl;
            optionNumber++;
        }
    }
}

//Translating the user's numbered move choice into the actual connected zone index.
int FieldGraph::getConnectedZoneByChoice(int fromZone, int choice) const {
    int optionNumber = 1;
    for (int zoneIndex = 0; zoneIndex < ZONE_COUNT; zoneIndex++) {
        if (connections[fromZone][zoneIndex]) {
            if (optionNumber == choice) {
                return zoneIndex;
            }
            optionNumber++;
        }
    }

    return -1;
}
