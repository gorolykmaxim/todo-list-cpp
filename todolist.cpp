#include "todolist.h"

void TodoList::addTodo(std::string todoText) {
    todos.push_back({.text = todoText, .id = currentId++});
}

void TodoList::removeTodo(int todoId)
{
    todos.erase(std::remove_if(todos.begin(), todos.end(), [todoId] (Todo todo) {return todo.id == todoId;}));
}

const std::vector<Todo> TodoList::getTodos() const {
    return todos;
}
