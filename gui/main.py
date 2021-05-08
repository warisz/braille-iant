from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys

class Window(QMainWindow):
    def __init__(self):
        super(Window, self).__init__()
        self.setGeometry(200, 200, 400, 400)
        self.setWindowTitle("Braille-iant")
        self.interface()

    def interface(self):
        self.label = QtWidgets.QLabel(self)
        self.label.setText("Enter Text: ")
        self.label.move(100, 100)

        self.printbutton = QtWidgets.QPushButton(self)
        self.printbutton.setText("Print")
        self.printbutton.clicked.connect(self.print_text)

    

    def print_text(self):
        self.label.setText("PRESSED!")
        self.update()

    def update(self):
        self.label.adjustSize()

    
def window():
    #setup to check system stuff (sys.argv)
    app = QApplication(sys.argv)
    win = Window()


    win.show()
    sys.exit(app.exec_())

window()