import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

TodoView {
    ColumnLayout {
        anchors.fill: parent
        MyButton {
            id: backBtn
            focus: true
            text: "Back"
            onClicked: stack.pop()
        }
        Label {
            Layout.fillHeight: true
            text: "Your help text to add todos"
        }
    }
}
