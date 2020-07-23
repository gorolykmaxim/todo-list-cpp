import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    StackView.onStatusChanged: {
        if (StackView.status == StackView.Activating) {
            listVM.load()
        }
    }
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20

        Label {
            text: "Today's Tos-Dos:"
            font.pixelSize: 20
        }
        ListView {
            id: todoList
            Layout.fillHeight: true
            Layout.fillWidth: true
            KeyNavigation.tab: addTodoBtn
            KeyNavigation.down: addTodoBtn
            model: listVM.todos
            delegate: FocusScope {
                width: parent.width
                height: listViewItem.height
                RowLayout {
                    id: listViewItem
                    width: parent.width
                    Label {
                        Layout.alignment: Qt.AlignLeft
                        text: modelData.text
                    }
                    MyButton {
                        Layout.alignment: Qt.AlignRight
                        text: "Delete"
                        focus: true
                        onClicked: listVM.removeTodo(modelData);
                    }
                }
            }
        }
        MyButton {
            id: addTodoBtn
            text: "Add ToDo"
            focus: true
            onClicked: stack.push("add-todo.qml")
            KeyNavigation.tab: todoList
        }
    }
}
