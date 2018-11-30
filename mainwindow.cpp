#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myth = new myThread;
    myth->init(ui->PlotRAW);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_st_clicked()
{

    myth->m_blMainQuit = false;
    //setupQuadraticDemo();
    //Call start() not block;
    //Call run() will be blocked;
    myth->start();
    qDebug()<<"After Run";
}

myThread::myThread(QObject *parent) :  QThread(parent)
{

}

void myThread::init(QCustomPlot *apPlot)
{
    m_Plot = apPlot;
}
void myThread::run()
{
    unsigned char liAmp = 1;
    while(1)
    {
        if(m_blMainQuit)
            break;


        QVector<double> x(2048), y(2048); // initialize with entries 0..100
        double angle = 2 * 3.14 / 360;

        for (int i=0; i<2048; ++i)
        {
          x[i] = i; // x goes from -1 to 1
          y[i] = liAmp * sin(angle * i) + liAmp;  // let's plot a quadratic function
        }
        // create graph and assign data to it:
        m_Plot->addGraph();
        m_Plot->graph(0)->setData(x, y);
        // give the axes some labels:
        m_Plot->xAxis->setLabel("x");
        m_Plot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        m_Plot->xAxis->setRange(0, 2048);
        m_Plot->yAxis->setRange(0, 2 * liAmp);
        m_Plot->replot();

        liAmp++;
        qDebug()<<"AAAA";
        sleep(5);
    }
    return;
}
