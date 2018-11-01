#ifndef MYWIDGET_H
#define MYWIDGET_H
#include "QOpenGLWidget"
#include "geomap.h"
#include "geopoint.h"
#include <QMouseEvent>


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
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    GeoMap *map;

    double mouseX, mouseY, offsetX = 0, offsetY = 0, newOffsetX = 0, newOffsetY = 0;
    double scale=0.9;

};

#endif // MYWIDGET_H
