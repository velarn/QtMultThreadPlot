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


