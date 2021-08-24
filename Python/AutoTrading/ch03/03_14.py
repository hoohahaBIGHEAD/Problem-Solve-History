# ch03/03_14.py
import sys
from PyQt5.QtWidgets import *

class Mywindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setGeometry(100,200,300,400)
        self.setWindowTitle("PyQt")

app = QApplication(sys.argv)
window = Mywindow()
window.show()
app.exec_()