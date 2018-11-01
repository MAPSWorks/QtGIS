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
}



void MyWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offsetX,offsetY,0);
    glScalef(scale,scale,0);


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


void MyWidget::mousePressEvent(QMouseEvent *event){
    if (event->buttons() == Qt::LeftButton)
    {
        // 切换光标样式
        setCursor(Qt::OpenHandCursor);
        mouseX = event->x();
        mouseY = event->y();
    }
    if (event->buttons() == Qt::RightButton)
    {
        offsetX = 0;
        offsetY = 0;
        update();
    }
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        // 计算图像偏移量
        newOffsetX = 2*(event->x() - mouseX) / this->width();
        newOffsetY = 2*(mouseY - event->y()) / this->height();
        offsetX += newOffsetX;
        offsetY += newOffsetY;
        update();
    }
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    unsetCursor();
    offsetX += newOffsetX;
    offsetY += newOffsetY;
    newOffsetX = 0;
    newOffsetY = 0;
}

void MyWidget::wheelEvent(QWheelEvent *event)
{
    scale -= 0.01 * event->delta();
    // 限制缩小倍数
    if (scale < 0.9f)
    {
        scale = 0.9f;
    }
    update();
}

