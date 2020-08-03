#include "todolist.h"
#include <filesystem>
#include <sstream>

TodoList::TodoList(const std::filesystem::path& databaseFilePath) {
    try {
        auto onError = [=] {throw TodoListInitializationError(sqlite3_errmsg(db));};
        execute([&] {return sqlite3_open(databaseFilePath.string().c_str(), &db);}, onError);
        execute([&] {return sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS TODO(\"TEXT\" TEXT)", nullptr, nullptr, nullptr);}, onError);
        execute([&] {return sqlite3_prepare_v2(db, "INSERT INTO TODO VALUES(?)", -1, &addStatement, nullptr);}, onError);
        execute([&] {return sqlite3_prepare_v2(db, "DELETE FROM TODO WHERE rowid = ?", -1, &removeStatement, nullptr);}, onError);
        execute([&] {return sqlite3_prepare_v2(db, "SELECT rowid, \"TEXT\" FROM TODO", -1, &retrieveStatement, nullptr);}, onError);
        initializeIfEmpty(onError);
    } catch (TodoListInitializationError &e) {
        freeResources();
        throw e;
    }
}

void TodoList::freeResources() {
    sqlite3_finalize(addStatement);
    sqlite3_finalize(removeStatement);
    sqlite3_finalize(retrieveStatement);
    sqlite3_close(db);
}

TodoList::~TodoList() {
    freeResources();
}

void TodoList::addTodo(const std::string& todoText) {
    auto onError = [&] {throw TodoListError::addition(todoText, sqlite3_errmsg(db));};
    execute([=] {return sqlite3_reset(addStatement);}, onError);
    execute([&] {return sqlite3_bind_text(addStatement, 1, todoText.c_str(), -1 , nullptr);}, onError);
    step(addStatement, onError);
}

void TodoList::removeTodo(int todoId)
{
    auto onError = [=] {throw TodoListError::removal(todoId, sqlite3_errmsg(db));};
    execute([=] {return sqlite3_reset(removeStatement);}, onError);
    execute([=] {return sqlite3_bind_int64(removeStatement, 1, todoId);}, onError);
    step(removeStatement, onError);
}

std::vector<Todo> TodoList::getTodos() const {
    execute([=] {return sqlite3_reset(removeStatement);}, [=] {throw TodoListError::retrieval(sqlite3_errmsg(db));});
    std::vector<Todo> todos;
    while (sqlite3_step(retrieveStatement) == SQLITE_ROW) {
        int todoId = sqlite3_column_int64(retrieveStatement, 0);
        std::string text = reinterpret_cast<const char*>(sqlite3_column_text(retrieveStatement, 1));
        todos.push_back({todoId, std::move(text)});
    }
    return todos;
}

void TodoList::initializeIfEmpty(const std::function<void()>& onError) {
    sqlite3_stmt *sizeStatement;
    try {
        execute([&] {return sqlite3_prepare_v2(db, "SELECT COUNT(*) FROM TODO", -1, &sizeStatement, nullptr);}, onError);
        if (sqlite3_step(sizeStatement) != SQLITE_ROW) {
            onError();
        }
        int todosCount = sqlite3_column_int(sizeStatement, 0);
        if (todosCount == 0) {
            addTodo("Chill");
            addTodo("Try to finish this app");
            addTodo("Chill a bit more");
        }
    } catch (TodoListInitializationError &e) {
        sqlite3_finalize(sizeStatement);
        throw e;
    }
}

void TodoList::execute(const std::function<int()>& exec, const std::function<void()>& throwError) const {
    if (exec() != SQLITE_OK) {
        throwError();
    }
}

void TodoList::step(sqlite3_stmt *statement, const std::function<void()> &onError) {
    int result;
    do {
        result = sqlite3_step(statement);
    } while (result == SQLITE_BUSY);
    if (result != SQLITE_DONE) {
        onError();
    }
}

TodoListInitializationError::TodoListInitializationError(const char *reason) : std::runtime_error(std::string("Failed to initialize todo list: ") + reason) {}


TodoListError TodoListError::addition(const std::string& newTodo, const char *reason) {
    auto action = std::stringstream() << "add item '" << newTodo << "' to list";
    return TodoListError(action.str(), reason);
}

TodoListError TodoListError::removal(int todoId, const char *reason) {
    auto action = std::stringstream() << "remove item with ID '" << todoId << "' from the list";
    return TodoListError(action.str(), reason);
}

TodoListError TodoListError::retrieval(const char *reason) {
    return TodoListError("load the list" , reason);
}

TodoListError::TodoListError(const std::string& action, const char *string) : std::runtime_error((std::stringstream() << "Failed to " << action << ": " << string).str()) {}
