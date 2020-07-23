#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
#include <vector>

struct Todo {
    std::string text;
};

class TodoList
{
public:
    void addTodo(Todo todo);
    void removeTodo(std::string todoText);
    const std::vector<Todo> getTodos() const;
private:
    std::vector<Todo> todos;
};

#endif // TODOLIST_H
