#include <QtConcurrent>
#include "listviewmodel.h"

ListViewModel::ListViewModel(TodoList& todoList, QThreadPool& threadPool)
    : todoList(todoList), threadPool(threadPool)
{
    connect(&todosWatcher, &QFutureWatcher<std::vector<Todo>>::finished, this, &ListViewModel::reload);
    connect(&removalWatcher, &QFutureWatcher<void>::finished, this, &ListViewModel::load);
    load();
}

void ListViewModel::load() {
    QFuture<std::vector<Todo>> loadedTodos = QtConcurrent::run(&threadPool, &todoList, &TodoList::getTodos);
    todosWatcher.setFuture(loadedTodos);
}

void ListViewModel::removeTodo(TodoModel *model)
{
    QFuture<void> todoRemoved = QtConcurrent::run(&threadPool, &todoList, &TodoList::removeTodo, model->getId());
    removalWatcher.setFuture(todoRemoved);
}

QList<TodoModel*> ListViewModel::todos() const {
    return todoListModels;
}

ListViewModel::~ListViewModel()
{
    clear();
}

void ListViewModel::reload() {
    clear();
    initialize();
}

void ListViewModel::initialize() {
    for (const auto& todo: todosWatcher.result()) {
        todoListModels.append(new TodoModel(todo));
    }
    emit todosChanged(todoListModels);
}

void ListViewModel::clear() {
    if (!todoListModels.isEmpty()) {
        qDeleteAll(todoListModels);
        todoListModels.clear();
    }
}
