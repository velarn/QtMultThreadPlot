#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <qcustomplot.h>

namespace Ui {
class MainWindow;
class myThread;
}

class myThread : public QThread
{
public:
    bool m_blMainQuit;
    QCustomPlot *customPlot;
public:
    void run();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupQuadraticDemo(QCustomPlot *customPlot);

private slots:
    void on_btn_st_clicked();

private:
    Ui::MainWindow *ui;
    myThread *myth;

};

#endif // MAINWINDOW_H
