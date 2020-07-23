import QtQuick 2.0
import QtQuick.Controls 2.12

Button {
    highlighted: activeFocus
    Keys.onReturnPressed: clicked()
    Keys.onEnterPressed: clicked()
}
