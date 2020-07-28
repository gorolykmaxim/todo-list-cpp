#ifndef LISTVIEWMODEL_H
#define LISTVIEWMODEL_H

#include <QObject>
#include <QThreadPool>
#include "todolist.h"
#include "todomodel.h"

class ListViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<TodoModel*> todos READ todos NOTIFY todosChanged)
public:
    explicit ListViewModel(TodoList& todoList, QThreadPool& threadPool);
    QList<TodoModel*> todos() const;
    ~ListViewModel();
public slots:
    void load();
    void removeTodo(TodoModel* model);
signals:
    void todosChanged(QList<TodoModel*>);
private:
    TodoList& todoList;
    QThreadPool& threadPool;
    QList<TodoModel*> todoListModels;
    void initialize();
    void clear();
    void reload();
};

#endif // LISTVIEWMODEL_H
