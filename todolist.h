#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
#include <vector>
#include <functional>
#include "third-party/sqlite-amalgamation/sqlite3.h"

struct Todo {
    int id;
    std::string text;
};

class TodoList
{
public:
    explicit TodoList(const std::string& databaseFilePath);

    void addTodo(const std::string& todoText);
    void removeTodo(int todoId);
    std::vector<Todo> getTodos() const;

    virtual ~TodoList();

private:
    sqlite3_stmt *addStatement, *removeStatement, *retrieveStatement;
    sqlite3* db;

    void initializeIfEmpty(const std::function<void()>& onError);
    void step(sqlite3_stmt *statement, const std::function<void()>& onError);
    void execute(const std::function<int()>& exec, const std::function<void()>& throwError) const;
    void freeResources();
};

class TodoListInitializationError: public std::runtime_error {
public:
    explicit TodoListInitializationError(const char* reason);
};

class TodoListError: public std::runtime_error {
public:
    static TodoListError addition(const std::string& newTodo, const char* reason);
    static TodoListError removal(int todoId, const char* reason);
    static TodoListError retrieval(const char* reason);
private:
    TodoListError(const std::string& action, const char *string);
};

#endif // TODOLIST_H
