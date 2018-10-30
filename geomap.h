#ifndef GEOMAP_H
#define GEOMAP_H
#include <vector>
#include "geoarc.h"
#include "geonode.h"
#include <QFileDialog>
#include <QTextStream>
#include "floyd.h"

class GeoMap
{
public:
    GeoMap();
    ~GeoMap();
    void drawMap();
    double left,top,right,bottom;
    std::vector<GeoArc*> arcs;
    std::vector<GeoNode*> nodes;
    void loadFile();
    void addLine(ifstream &fs);
    void addNode(GeoArc* arc);
    void generateRoute(int start,int end);
    Graph_DG *graph;
};

#endif // GEOMAP_H
