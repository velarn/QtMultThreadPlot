#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <qcustomplot.h>
#include "vthread.h"

namespace Ui {
class MainWindow;
class myThread;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btn_st_clicked();
    void receiveMessage(const int aiNum);
private:
    Ui::MainWindow *ui;
    myThread *myth;

};

#endif // MAINWINDOW_H
