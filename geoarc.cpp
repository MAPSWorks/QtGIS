#include "geoarc.h"

GeoArc::GeoArc(int arcId,int ptSum,int fNodeId,int tNodeId)
{
    this->arcId=arcId;
    this->ptSum=ptSum;
    this->fNodeId=fNodeId;
    this->tNodeId=tNodeId;
}

double GeoArc::calculateDistance()
{
    double distance=0;
    for(int i=0;i<this->pts.size()-1;i++)
    {
        distance+=sqrt((pts[i+1].x-pts[i].x)*(pts[i+1].x-pts[i].x)+(pts[i+1].y-pts[i].y)*(pts[i+1].y-pts[i].y));
    }
    return distance;
}
