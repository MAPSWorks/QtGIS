#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mywidget.h"
#include "geomap.h"
#include <qinputdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    MyWidget *myWidget;

private slots:
    void loadFile();
    void generateRoute();
};

#endif // MAINWINDOW_H
