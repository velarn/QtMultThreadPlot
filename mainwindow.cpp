#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myth = new myThread;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{
  //demoName = "Quadratic Demo";
  // generate some data:
  QVector<double> x(101), y(101); // initialize with entries 0..100
  for (int i=0; i<101; ++i)
  {
    x[i] = i/50.0 - 1; // x goes from -1 to 1
    y[i] = x[i]*x[i];  // let's plot a quadratic function
  }
  // create graph and assign data to it:
  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-1, 1);
  customPlot->yAxis->setRange(0, 1);
  ui->PlotRAW->replot();
}

void MainWindow::on_btn_st_clicked()
{

    myth->m_blMainQuit = false;
    setupQuadraticDemo(ui->PlotRAW);
    //Call start() not block;
    //Call run() will be blocked;
    //myth->start();
    qDebug()<<"After Run";
}

void myThread::run()
{
    while(1)
    {
        if(m_blMainQuit)
            break;

        qDebug()<<"AAAA";
        sleep(10);
    }
    return;
}
