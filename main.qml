import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 350
    height: 480
    minimumWidth: 350
    title: qsTr("ToDo list app")
    StackView {
        id: stack
        anchors.fill: parent
        focus: true
        initialItem: "list.qml"
    }
}
