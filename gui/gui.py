from PyQt5 import QtCore, QtGui, QtWidgets
import serial

class Ui_Dialog(object):
    def setupUi(self, Dialog):
  
        self.current_braille = ""
        self.braille_dict = {
            ' ': ' ',
            'a': '⠁',
            'b': '⠃',
            'c': '⠉',
            'd': '⠙',
            'e': '⠑',
            'f': '⠋',
            'g': '⠛',
            'h': '⠓',
            'i': '⠊',
            'j': '⠚',
            'k': '⠅',
            'l': '⠇',
            'm': '⠍',
            'n': '⠝',
            'o': '⠕',
            'p': '⠏',
            'q': '⠟',
            'r': '⠗',
            's': '⠎',
            't': '⠞',
            'u': '⠥',
            'v': '⠧',
            'w': '⠺',
            'x': '⠭',
            'y': '⠽',
            'z': '⠵',
            '\n': '\n'
        }
        self.ser = serial.Serial(port='COM3', baudrate = 9600)

        Dialog.setObjectName("Dialog")
        Dialog.resize(1200, 900)
        self.textEdit = QtWidgets.QTextEdit(Dialog)
        self.textEdit.setGeometry(QtCore.QRect(100, 100, 1000, 350))
        self.textEdit.setObjectName("textEdit")
        self.printbutton = QtWidgets.QPushButton(Dialog)
        self.printbutton.setGeometry(QtCore.QRect(425, 800, 151, 41))
        self.printbutton.setObjectName("printbutton")
        self.cancelbutton = QtWidgets.QPushButton(Dialog)
        self.cancelbutton.setGeometry(QtCore.QRect(625, 800, 151, 41))
        self.cancelbutton.setAutoFillBackground(False)
        self.cancelbutton.setObjectName("cancelbutton")
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(100, 40, 200, 70))
        font = QtGui.QFont()
        font.setFamily("Yu Gothic UI Semibold")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.groupBox = QtWidgets.QGroupBox(Dialog)
        self.groupBox.setGeometry(QtCore.QRect(100, 500, 1000, 250))
        self.groupBox.setTitle("")
        self.groupBox.setObjectName("groupBox")
        self.groupBox.setStyleSheet("background: #f1d83d")
        self.label = QtWidgets.QLabel(self.groupBox)
        self.label.setGeometry(QtCore.QRect(0, 0, 47, 16))
        self.label.setText("")
        self.label.setObjectName("label")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

        self.printbutton.clicked.connect(self.printbutton_clicked)
        self.textEdit.textChanged.connect(self.update_braille)


    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Braille-iant", "Braille-iant"))
        self.label.setText(_translate("Dialog", ""))
        self.printbutton.setText(_translate("Dialog", "PRINT"))
        self.cancelbutton.setText(_translate("Dialog", "CANCEL"))
        self.label_2.setText(_translate("Dialog", "Enter Text:"))

    def printbutton_clicked(self):
        for char in str(self.textEdit.toPlainText()).lower():
            self.ser.write(char.encode())
            print(char)

    def update_braille(self):
        self.current_braille = " "
        print(str(self.textEdit.toPlainText()))
        for char in str(self.textEdit.toPlainText()).lower():
            if char in self.braille_dict:
                self.current_braille = self.current_braille + self.braille_dict[char]
                if len(self.current_braille) % 83 == 0:
                    self.current_braille = self.current_braille + "\n"
            
        self.label.setText(self.current_braille)
        self.label.adjustSize()

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())
