#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->btn_st->setText("Start");

    myth = new myThread;
    myth->init(ui->PlotRAW);
    connect(myth,&myThread::message,this,&MainWindow::receiveMessage);
}

MainWindow::~MainWindow()
{
    if(myth->isRunning())
    {
        myth->m_blMainQuit = true;
        myth->wait();
        qDebug()<<"Before Quit main Thread,kill the sub thread";
    }
    delete ui;
}

void MainWindow::on_btn_st_clicked()
{
    if(myth->isRunning())
    {
        ui->btn_st->setText("Start");
        myth->m_blMainQuit = true;
        myth->wait();
        qDebug()<<"Kill the sub thread";
    }
    else
    {
        ui->btn_st->setText("Stop");
        myth->m_blMainQuit = false;
        myth->start();
        qDebug()<<"Start a new sub thread";
    }
}

void MainWindow::receiveMessage(const int aiNum)
{
   ui->edit_1->setText(QString::number(aiNum));
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
    int liOffset = 1;
    int liPhase = 0;
    int liPerd = 0;
    while(1)
    {
        if(m_blMainQuit)
            break;


        QVector<double> x(2048), y(2048); // initialize with entries 0..100
        double angle = 2 * 3.14 / 360;


        for (int i=0; i<2048; ++i)
        {
          x[i] = i; // x goes from -1 to 1
          y[i] = liAmp * sin(angle * i * liPerd/2048 + liPhase) + liOffset;  // let's plot a sinc function
        }
        m_Plot->clearGraphs();
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

        liPerd++;
        if(liPerd >2047)
            liPerd = 0;
        //qDebug()<<"AAAA";
        emit message(liPerd);
        msleep(50);
    }
    return;
}
