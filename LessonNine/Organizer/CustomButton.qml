import QtQuick 2.3
import QtQuick.Controls 2.12

Button
{
    anchors.centerIn: addNewTask

    id:addNewTaskButton

    background:
        Rectangle
        {
            width: parent.width
            height: parent.height
            color: "lightgrey"
            border.color: "black"
            border.width: 1
        }
}
