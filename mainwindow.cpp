#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mywidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myWidget = new MyWidget();
    this->setCentralWidget(myWidget);
    QObject::connect(this->ui->actionLoadFile, SIGNAL(triggered()),this, SLOT(loadFile()));
    QObject::connect(this->ui->actionGenerateRoute, SIGNAL(triggered()),this, SLOT(generateRoute()));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete myWidget;
}

void MainWindow::loadFile()
{
    if(myWidget->map!=nullptr) delete myWidget->map;
    myWidget->map= new GeoMap();
    myWidget->map->loadFile();
    myWidget->update();
}

void MainWindow::generateRoute()
{
    bool startInputed;
    int startNode = QInputDialog::getInt(this, "Input Dialog","start node:", 0, 0, 100, 1, &startInputed);
    bool endInputed;
    int endNode = QInputDialog::getInt(this, "Input Dialog","end node:", 0, 0, 100, 1, &endInputed);
    if (startInputed&&endInputed)
    {
        myWidget->map->generateRoute(startNode,endNode);
        myWidget->update();
    }
}
