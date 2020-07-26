import QtQuick 2.0
import QtQuick.Controls 2.12

Page {
    property bool rootView: false
    signal backPressed()
    Keys.onBackPressed: {
        if (!rootView) {
            backPressed()
            event.accepted = true
        } else {
            event.accepted = false
        }
    }
    onBackPressed: {
        stack.pop()
    }
    background: null
}
