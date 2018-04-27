#ifndef MYTASK_H
#define MYTASK_H

#include <QRunnable>
#include <QObject>
#include <QRunnable>

class MyTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    MyTask();

signals:
    // notify to the main thread when we're done
    void Result(void);

protected:
    void run();
};


#endif // MYTASK_H
