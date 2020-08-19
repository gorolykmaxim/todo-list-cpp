#ifndef ADDTODOVIEWMODEL_H
#define ADDTODOVIEWMODEL_H

#include "todolist.h"

#include <QObject>
#include <QThreadPool>
#include <QFutureWatcher>

class AddTodoViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
public:
    AddTodoViewModel(TodoList& todoList, QThreadPool& threadPool);
    void setText(QString text);
    QString getText() const;
signals:
    void textChanged(QString newText);
    void closeView();
public slots:
    void addTodo();
    void cancel();
private:
    TodoList& todoList;
    QThreadPool& threadPool;
    QString text;
    QFutureWatcher<void> additionWatcher;
};

#endif // ADDTODOVIEWMODEL_H
