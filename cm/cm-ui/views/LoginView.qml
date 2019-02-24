import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import assets 1.0
import components 1.0
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4

Window {
    id: login
    visible: true
    width: 355
    height: 200
    title: qsTr("Login")
    flags: Qt.Dialog
    color: "#2d2d2d"

    property bool changed: show.checkState
    signal registerClicked()

    Item {
         Rectangle {
             id: pic
             x: 10
             y:20
             width: 128
             height:128
             color: "#ffffff"
         }

         TextField {
             id: username
             x:150
             y:37
             width: 130
             anchors.topMargin: 15
             anchors.leftMargin: 4
             height:25
             placeholderText: focus? "":"Username"
             Label
             {
                 Text {
                     color: "#ffffff"
                     id: name
                     text: qsTr("Username")
                 }
                 anchors.bottom : username.top
             }
         }
         TextField {
             id: password
             x:150
             y:82
             width: 130
             anchors.leftMargin: 4
             height:25

             echoMode: changed? TextInput.Normal:TextInput.Password
             Label
             {
                 Text {
                     color: "#ffffff"
                     id: passwrd
                     text: qsTr("Password")
                 }
                 anchors.bottom : password.top
             }

             placeholderText: focus? "":"Password"
         }

             CheckBox {

                 anchors.left: password.right
                 anchors.top : password.top
                 anchors.leftMargin: 10
                 padding: -5
                 id:show
                 Text{
                    color: "#ffffff"
                    text: qsTr("Show")
                    anchors.left: show.right
                    anchors.leftMargin: 10
                    padding:0
                 }
                 indicator.width: 16
                 indicator.height: 16

             }
             Button {
                 id:button1
                 anchors.top: password.bottom
                 anchors.topMargin: 15
                 anchors.left: password.left
                 width:95
                 height:20
                 RoundButton {
                     radius:4
                     text: "Login"
                     onClicked: model.revert()
                     anchors.fill: parent
                 }
             }
             Button{
                 id:button2
                 anchors.top: password.bottom
                 anchors.topMargin: 15
                 anchors.leftMargin: 5
                 anchors.left: button1.right
                 width: 95
                 height:20

                 RoundButton {
                     radius:4
                     text: "Register"
                     onClicked: contentFrame.replace("qrc:/views/RegisterView.qml")
                     anchors.fill: parent

                 }

        }
     }

}

