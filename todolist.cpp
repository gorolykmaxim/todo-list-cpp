#include "todolist.h"

void TodoList::addTodo(Todo todo) {
    todos.push_back(std::move(todo));
}

void TodoList::removeTodo(std::string todoText)
{
    for (auto it = todos.begin(); it != todos.end();) {
        if (it->text == todoText) {
            todos.erase(it);
        } else {
            ++it;
        }
    }
}

const std::vector<Todo> TodoList::getTodos() const {
    return todos;
}
