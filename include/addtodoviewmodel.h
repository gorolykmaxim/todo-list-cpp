#ifndef ADDTODOVIEWMODEL_H
#define ADDTODOVIEWMODEL_H

#include "todolist.h"

#include <QObject>
#include <QThreadPool>

class AddTodoViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
public:
    AddTodoViewModel(TodoList& todoList, QThreadPool& threadPool);
    void setText(QString text);
    QString getText() const;
signals:
    void textChanged(const QString newText);
    void closeView();
public slots:
    void addTodo();
    void cancel();
private:
    TodoList& todoList;
    QThreadPool& threadPool;
    QString text;
    void dispose();
};

#endif // ADDTODOVIEWMODEL_H
