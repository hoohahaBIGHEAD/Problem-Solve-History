# ch03/03_12.py
import sys
from PyQt5.QtWidgets import *

app = QApplication(sys.argv)
label = QLabel("Hello")
label.show()
btn = QPushButton("Hi")
btn.show()
app.exec_()