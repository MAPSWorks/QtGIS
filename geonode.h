#ifndef GEONODE_H
#define GEONODE_H
#include <vector>
#include <QDebug>

class GeoNode
{
public:
    GeoNode(int nodeId,double x,double y);
    ~GeoNode();
    double x,y;
    int nodeId=-1;
    std::vector<int> adjacentNodeId;
};

#endif // GEONODE_H
