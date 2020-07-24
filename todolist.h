#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
#include <vector>

struct Todo {
    int id;
    std::string text;
};

class TodoList
{
public:
    void addTodo(std::string todoText);
    void removeTodo(int todoId);
    const std::vector<Todo> getTodos() const;
private:
    std::vector<Todo> todos;
    int currentId = 1;
};

#endif // TODOLIST_H
