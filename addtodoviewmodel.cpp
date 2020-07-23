#include "addtodoviewmodel.h"

AddTodoViewModel::AddTodoViewModel(TodoList& todoList, QThreadPool& threadPool)
    : todoList(todoList), threadPool(threadPool)
{

}

void AddTodoViewModel::setText(QString text) {
    this->text = text;
    emit textChanged(text);
}

QString AddTodoViewModel::getText() const {
    return text;
}

void AddTodoViewModel::addTodo() {
    QString todoText = text;
    threadPool.tryStart([=] () {
        todoList.addTodo({todoText.toStdString()});
        dispose();
    });
}

void AddTodoViewModel::cancel() {
    threadPool.tryStart(std::bind(&AddTodoViewModel::dispose, this));
}

void AddTodoViewModel::dispose()
{
    text.clear();
    emit closeView();
}
