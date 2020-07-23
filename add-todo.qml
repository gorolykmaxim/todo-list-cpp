import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    Connections {
        target: addTodoVM
        function onCloseView() {
            stack.pop();
        }
    }
    Component.onCompleted: {
        todoTextInput.textChanged.connect(() => addTodoVM.text = todoTextInput.text)
        todoTextInput.accepted.connect(addBtn.clicked)
        addBtn.clicked.connect(addTodoVM.addTodo)
        cancelBtn.clicked.connect(addTodoVM.cancel)
    }
    ColumnLayout {
        anchors.centerIn: parent
        width: 300
        TextField {
            id: todoTextInput
            Layout.fillWidth: true
            placeholderText: "Enter the new To-Do here..."
            text: addTodoVM.text
            focus: true
            KeyNavigation.tab: addBtn
            KeyNavigation.down: addBtn
        }
        RowLayout {
            MyButton {
                id: addBtn
                text: "Add"
                KeyNavigation.tab: cancelBtn
                KeyNavigation.right: cancelBtn
            }
            MyButton {
                id: cancelBtn
                text: "Cancel"
                KeyNavigation.tab: todoTextInput
                KeyNavigation.up: todoTextInput
            }
        }
    }
}
