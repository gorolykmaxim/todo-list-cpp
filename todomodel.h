#ifndef TODOMODEL_H
#define TODOMODEL_H

#include "todolist.h"

#include <QObject>

class TodoModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString text READ getText NOTIFY textChanged)
public:
    explicit TodoModel(const Todo& todo);
    const QString getText() const;
signals:
    void textChanged(QString& newText);
private:
    QString text;
};

#endif // TODOMODEL_H
