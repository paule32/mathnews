#include "mytask.h"
#include <QDebug>


MyTask::MyTask()
{
    qDebug() << "MyTask()";
}

void MyTask::run()
{
    qDebug() << "Task done";
    emit Result();
}
