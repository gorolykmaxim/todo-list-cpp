#include "todomodel.h"

TodoModel::TodoModel(const Todo &todo)
    : text(QString::fromStdString(todo.text)), id(todo.id)
{

}

const QString TodoModel::getText() const {
    return text;
}

int TodoModel::getId() const
{
    return id;
}
