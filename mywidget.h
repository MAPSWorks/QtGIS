#ifndef MYWIDGET_H
#define MYWIDGET_H
#include "QOpenGLWidget"
#include "geomap.h"
#include "geopoint.h"


class MyWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyWidget();
    ~MyWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int width,int height);
    GeoPoint xy2screen(GeoPoint pt);
   // void mousePressEvent(QMouseEvent *event);
    GeoMap *map;

};

#endif // MYWIDGET_H
