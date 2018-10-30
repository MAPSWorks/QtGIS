#include "mywidget.h"

MyWidget::MyWidget()
{
    map = nullptr;
}

MyWidget::~MyWidget()
{
    delete map;
}

void MyWidget::initializeGL(){
    glClearColor(0.16f,0.16f,0.16f,0.0f);
}

void MyWidget::resizeGL(int width,int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
}

void MyWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    // draw data
    if(this->map!=nullptr)
    {
       for(int i=0;i<map->arcs.size();i++)
       {
           glLineWidth(1.0);
            glBegin(GL_LINE_STRIP);
            for(int j=0;j<map->arcs[i]->pts.size();j++)
            {
                glColor3d(0,0.7,0.9);
                glVertex2f(xy2screen(map->arcs[i]->pts[j]).x,xy2screen(map->arcs[i]->pts[j]).y);
            }
            glEnd();         
        }
    }
    if(this->map!=nullptr&&this->map->graph!=nullptr)
    {
      for(int i=0;i<map->graph->routeId.size()-1;i++)
       {
            for(int j=0;j<map->arcs.size();j++)
            {
                 if((map->arcs[j]->fNodeId==map->graph->routeId[i]&&map->arcs[j]->tNodeId==map->graph->routeId[i+1])||
                         (map->arcs[j]->tNodeId==map->graph->routeId[i]&&map->arcs[j]->fNodeId==map->graph->routeId[i+1]))
                 {
                      //draw
                      glLineWidth(2.0);
                      glBegin(GL_LINE_STRIP);
                      for(int k=0;k<map->arcs[j]->pts.size();k++)
                      {
                          glColor3d(1,1,0);
                          glVertex2f(xy2screen(map->arcs[j]->pts[k]).x,xy2screen(map->arcs[j]->pts[k]).y);                        
                      }
                      glEnd();
                 }
            }
        }
    }
    glFlush();
}

GeoPoint MyWidget::xy2screen(GeoPoint pt){
    // transfer point to screen coordinate
    double width=this->map->right-this->map->left;
    double height=this->map->top-this->map->bottom;
    GeoPoint screen;
    screen.x=(pt.x-this->map->left)/width*2-1;
    screen.y=(pt.y-this->map->bottom)/height*2-1;
    return screen;
}

/*
void MyWidget::mousePressEvent(QMouseEvent *event){
    // mouse click
    double x,y;
    x=event->x();
    y=event->y();
    double width=this->map->right-this->map->left;
    double height=this->map->top-this->map->bottom;
    double window_width=this->width();
    double window_height=this->height();
    double real_x,real_y;
    real_x=x/window_width*width+this->map->left;
    real_y=y/window_height*height+this->map->bottom;
}
*/





