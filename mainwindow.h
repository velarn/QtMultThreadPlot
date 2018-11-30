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
   Q_OBJECT

public:
    explicit myThread(QObject *parent = nullptr);
public:
    void run();
    void init(QCustomPlot *apPlot);
public:
    bool m_blMainQuit;
    QCustomPlot *m_Plot;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btn_st_clicked();

private:
    Ui::MainWindow *ui;
    myThread *myth;

};

#endif // MAINWINDOW_H
