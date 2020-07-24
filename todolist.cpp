#include "todolist.h"

void TodoList::addTodo(Todo todo) {
    todos.push_back(std::move(todo));
}

void TodoList::removeTodo(std::string todoText)
{
    todos.erase(std::remove_if(todos.begin(), todos.end(), [todoText] (Todo todo) {return todo.text == todoText;}));
}

const std::vector<Todo> TodoList::getTodos() const {
    return todos;
}
