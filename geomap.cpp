#include "geomap.h"
#include <iostream>
#include <fstream>


GeoMap::GeoMap()
{
    this->graph=nullptr;
}

GeoMap::~GeoMap()
{
    if(graph!=nullptr) delete this->graph;
    if(arcs.size()!=0)
    for(auto arc:arcs)
    {
        delete arc;
    }
    if(nodes.size()!=0)
    for(auto node:nodes)
    {
        delete node;
    }
}

void GeoMap::loadFile()
{
    QFileDialog *fileDialog = new QFileDialog(nullptr,"open E00 File!","D:\\MyCplusProject\\TinyGIS\\data","*.e00");
    QString filePath;
    if(fileDialog->exec())
    {
        filePath = fileDialog->selectedFiles()[0];
    }
    string line;
    try
     {
        ifstream fs(filePath.toStdString(),ios::in);
        while(line!="EOS")
        {
            if(line=="ARC  2")
            {
                addLine(fs);
            }
            if(strncmp(line.c_str(),"YMAX",4) == 0)
            {
                 fs >> this->left >> this->bottom >> this->right >>this->top;
            }
            getline(fs, line);
        }
        fs.close();
     }
     catch (exception e)
     {

     }
}

void GeoMap::generateRoute(int startNode,int endNode)
{
    this->graph=new Graph_DG((int)this->nodes.size(),(int)this->arcs.size());
    int start;
    int end;
    double distance;
    int count = 0;
    for(int i=0;i<this->arcs.size();i++)
    {
        start=arcs[i]->fNodeId;
        end=arcs[i]->tNodeId;
        distance=arcs[i]->calculateDistance();
        graph->arc[start - 1][end - 1] = distance;
        graph->arc[end - 1][start - 1] = distance;
        ++count;
    }
    this->graph->Floyd();
    this->graph->printMatrix();
    this->graph->generateRoute(startNode,endNode);
    this->graph->printRoute();
}

void GeoMap::addLine(ifstream &fs)
{
    double x,y;
    int arcId;
    int fNodeId;
    int tNodeId;
    int numOfPoint;
    int go;
    while(true)
    {
        fs>>arcId;
        fs>>go>>fNodeId;
        fs>>tNodeId;
        fs>>go>>go>>numOfPoint;
        if(!numOfPoint)
        {
            break;
        }
        GeoArc *arc=new GeoArc(arcId,numOfPoint,fNodeId,tNodeId);
        for (int i = 0; i < numOfPoint; i++)
        {
            fs >> x >> y;
            GeoPoint pt(x,y);
            arc->pts.push_back(pt);            
        }
        this->arcs.push_back(arc);    
        //处理结点的存储
        addNode(arc);
    }
}

void GeoMap::addNode(GeoArc* arc)
{
    int isfNodeIn=0;//判断结点是否已经在数组中
    int istNodeIn=0;
    for(auto node:nodes)
    {
        if(arc->fNodeId==node->nodeId) isfNodeIn=1;
        if(arc->tNodeId==node->nodeId) istNodeIn=1;
    }
    if(isfNodeIn==0)
    {
        GeoNode *node=new GeoNode(arc->fNodeId,arc->pts[0].x,arc->pts[0].y);
        nodes.push_back(node);
    }
    if(istNodeIn==0)
    {
        GeoNode *node=new GeoNode(arc->tNodeId,arc->pts[arc->ptSum-1].x,arc->pts[arc->ptSum-1].y);
        nodes.push_back(node);
    }
    int fNode;int tNode;
    //取得邻接结点在数组中的索引
    int i=0;
    for(auto node:nodes)
    {
        if(arc->fNodeId==node->nodeId) fNode=i;
        if(arc->tNodeId==node->nodeId) tNode=i;
        i++;
    }
    //判断t结点是否已经与f结点邻接,若无则添加
    int istNodeInfNode=0;
    for(int i=0;i<nodes[fNode]->adjacentNodeId.size();i++)
    {
        if(nodes[fNode]->adjacentNodeId[i]==nodes[tNode]->nodeId) istNodeInfNode=1;
    }
    if(istNodeInfNode==0)
    {
        nodes[fNode]->adjacentNodeId.push_back(nodes[tNode]->nodeId);    
    }
    //判断f结点是否已经与t结点邻接，若无则添加
    int isfNodeIntNode=0;
    for(int i=0;i<nodes[tNode]->adjacentNodeId.size();i++)
    {
        if(nodes[tNode]->adjacentNodeId[i]==nodes[fNode]->nodeId) isfNodeIntNode=1;
    }
    if(isfNodeIntNode==0)
    {
        nodes[tNode]->adjacentNodeId.push_back(nodes[fNode]->nodeId);
    }
}
