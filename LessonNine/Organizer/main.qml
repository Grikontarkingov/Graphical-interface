import QtQuick 2.3
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import com.lesson.filecontroller 1.0


Window {
    width: 640
    height: 480
    visible: true

    title: qsTr("Hello World")

    Rectangle
    {
        id:taskNewPanel
        width: 640
        height: 120
        border.color: "black"
        border.width: 1

        Rectangle
        {
            id:taskName
            width: 320
            height: 40
            border.color: "black"
            border.width: 1

            TextEdit {
                id: taskNameText
                width: parent.width
                height: parent.height
                verticalAlignment: TextEdit.AlignVCenter
                horizontalAlignment:  TextEdit.AlignHCenter
                text: "New Task"
                font.family: "Calibri"
                font.pointSize: 14
                color: "black"
                focus: true
            }
        }

        Rectangle
        {
            id:deadline
            width: 320
            height: 40
            border.color: "black"
            border.width: 1
            anchors.top: taskName.bottom

            TextEdit {
                id: deadlineText
                width: parent.width
                height: parent.height
                verticalAlignment: TextEdit.AlignVCenter
                horizontalAlignment:  TextEdit.AlignHCenter
                text: "00.00.0000"
                font.family: "Calibri"
                font.pointSize: 14
                color: "black"
                focus: true
            }
        }

        Rectangle
        {
            id:progress
            width: 320
            height: 40
            border.color: "black"
            border.width: 1
            anchors.top: deadline.bottom

            Slider
            {
                id:progressSlider
                width: progress.width - 20
                height: progress.height
                from: 1
                value: 1
                to: 10
                snapMode: Slider.SnapAlways
                stepSize: 1
                anchors.right: progressText.left
            }

            TextEdit
            {
                id:progressText
                width: (parent.width - progressSlider.width)
                height: parent.height
                verticalAlignment: TextEdit.AlignVCenter
                horizontalAlignment:  TextEdit.AlignHCenter
                text: progressSlider.value
                font.family: "Calibri"
                font.pointSize: 14
                color: "black"
                focus: true
                readOnly: true
                anchors.left: progressSlider.right
            }
        }

        Rectangle
        {
            id:descriptionTaskName
            width: 160
            height: 40
            border.color: "black"
            border.width: 1
            anchors.left: taskName.right
            TextEdit {
                width: parent.width
                height: parent.height
                verticalAlignment: TextEdit.AlignVCenter
                text: "     - enter name of task"
                font.family: "Times New Roman"
                font.pointSize: 10
                color: "black"
                focus: true
                readOnly: true
            }
        }

        Rectangle
        {
            id:descriptionDeadline
            width: 160
            height: 40
            border.color: "black"
            border.width: 1
            anchors.top: descriptionTaskName.bottom
            anchors.left: deadline.right

            TextEdit {
                width: parent.width
                height: parent.height
                verticalAlignment: TextEdit.AlignVCenter
                text : "     - dealine (dd.mm.yyyy)"
                font.family: "Times New Roman"
                font.pointSize: 10
                color: "black"
                focus: true
                readOnly: true
            }
        }

        Rectangle
        {
            id:descriptionProgress
            width: 160
            height: 40
            border.color: "black"
            border.width: 1
            anchors.top: descriptionDeadline.bottom
            anchors.left: progress.right

            TextEdit {
                width: parent.width
                height: parent.height
                verticalAlignment: TextEdit.AlignVCenter
                text: "     - progres 0 to 10"
                font.family: "Times New Roman"
                font.pointSize: 10
                color: "black"
                focus: true
                readOnly: true
            }
        }

        Rectangle
        {
            id:addNewTask
            width: 160
            height: 120
            anchors.left: descriptionDeadline.right
            border.color: "black"
            border.width: 1

            CustomButton
            {
                id:save
                width: 100
                height: 50
                text: "Add new task"
                font.family: "Times New Roman"
                font.pointSize: 13

                onClicked:
                {
                    var taskName_ = taskNameText.text
                    var deadline_ = deadlineText.text
                    var progress_ = progressText.text
                    fileController.writeFile(taskName_, deadline_, progress_)
                }
            }
        }
    }

    FileController
    {
        id:fileController
    }
}
