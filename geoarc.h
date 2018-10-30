#ifndef GEOARC_H
#define GEOARC_H
#include "geonode.h"
#include "geopoint.h"
#include  <math.h>
#include  <vector>
class GeoArc
{
public:
    GeoArc(int arcId,int ptSum,int fNodeId,int tNodeId);
    int arcId;
    int ptSum;
    std::vector<GeoPoint> pts;
    int fNodeId;//starting point
    int tNodeId;//ending point
    double calculateDistance();
};

#endif // GEOARC_H
