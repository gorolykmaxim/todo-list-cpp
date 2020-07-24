#include "listviewmodel.h"

ListViewModel::ListViewModel(TodoList& todoList, QThreadPool& threadPool)
    : todoList(todoList), threadPool(threadPool)
{
    load();
}

void ListViewModel::load() {
    threadPool.start(std::bind(&ListViewModel::reload, this));
}

void ListViewModel::removeTodo(TodoModel *model)
{
    threadPool.tryStart([=] () {
        todoList.removeTodo(model->getId());
        reload();
    });
}

const QList<TodoModel*> ListViewModel::todos() const {
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
    for (auto todo: todoList.getTodos()) {
        todoListModels.append(new TodoModel(todo));
        todoListModels.last()->moveToThread(thread());
    }
    emit todosChanged(todoListModels);
}

void ListViewModel::clear() {
    if (!todoListModels.isEmpty()) {
        qDeleteAll(todoListModels);
        todoListModels.clear();
    }
}
