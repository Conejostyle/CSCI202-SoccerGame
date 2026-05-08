#ifndef FIELDGRAPH_H
#define FIELDGRAPH_H

#include <string>

class FieldGraph {
private:
    //Storing the total number of field zones used in the graph.
    static const int ZONE_COUNT = 5;

    //Storing the names of each zone in the field graph.
    std::string zoneNames[ZONE_COUNT];
    //Storing the chance bonus tied to each field zone.
    int zoneBonuses[ZONE_COUNT];
    //Storing which zones are connected to each other in the graph.
    bool connections[ZONE_COUNT][ZONE_COUNT];

    void connectZones(int fromZone, int toZone);

public:
    FieldGraph();
    int getStartZone() const;
    std::string getZoneName(int zoneIndex) const;
    int getZoneBonus(int zoneIndex) const;
    bool canMove(int fromZone, int toZone) const;
    void displayMoves(int fromZone) const;
    int getConnectedZoneByChoice(int fromZone, int choice) const;
};

#endif
