#include "todomodel.h"

TodoModel::TodoModel(const Todo &todo)
    : text(QString::fromStdString(todo.text)) {

}

const QString TodoModel::getText() const {
    return text;
}
