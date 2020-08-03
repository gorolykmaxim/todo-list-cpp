#include "listviewmodel.h"
#include "addtodoviewmodel.h"
#include "todolist.h"

#include <filesystem>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QString fontsDir = ":/fonts/";
    for (const auto& font: QDir(fontsDir).entryList()) {
        QFontDatabase::addApplicationFont(fontsDir + font);
    }
    auto databaseFilePath = std::filesystem::temp_directory_path() / "todo-list.db";
    TodoList list(databaseFilePath);
    QThreadPool threadPool;
    threadPool.setMaxThreadCount(1);
    ListViewModel listViewModel(list, threadPool);
    AddTodoViewModel addTodoViewModel(list, threadPool);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("listVM", &listViewModel);
    engine.rootContext()->setContextProperty("addTodoVM", &addTodoViewModel);
    engine.load(url);

    return app.exec();
}
