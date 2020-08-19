#include <QtConcurrent>
#include "addtodoviewmodel.h"

AddTodoViewModel::AddTodoViewModel(TodoList& todoList, QThreadPool& threadPool)
    : todoList(todoList), threadPool(threadPool)
{
    connect(&additionWatcher, &QFutureWatcher<void>::finished, this, &AddTodoViewModel::cancel);
}

void AddTodoViewModel::setText(QString text) {
    this->text = std::move(text);
    emit textChanged(this->text);
}

QString AddTodoViewModel::getText() const {
    return text;
}

void AddTodoViewModel::addTodo() {
    QFuture<void> todoAdded = QtConcurrent::run(&threadPool, &todoList, &TodoList::addTodo, text.toStdString());
    additionWatcher.setFuture(todoAdded);
}

void AddTodoViewModel::cancel() {
    text.clear();
    emit closeView();
}
