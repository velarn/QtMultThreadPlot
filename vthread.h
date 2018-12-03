#ifndef VTHREAD_H
#define VTHREAD_H

#include <QThread>
#include <qcustomplot.h>

class myThread : public QThread
{
   Q_OBJECT
signals:
    void message(const int aiNumo);
public:
    explicit myThread(QObject *parent = nullptr);
public:
    void run();
    void init(QCustomPlot *apPlot);
public:
    bool m_blMainQuit;
    QCustomPlot *m_Plot;
};

#endif // VTHEAD_H
