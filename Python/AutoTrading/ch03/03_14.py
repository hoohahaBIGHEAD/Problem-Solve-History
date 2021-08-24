# ch03/03_14.py
import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic
from PyQt5.QtCore import *
import pyupbit

"""


upbit = pyupbit.Upbit(access_key,secret_key)
print(upbit.get_balances())

#ret = upbit.cancel_order('aa4642f5-6fb1-4251-a0ae-64035f31e86d')
#print(ret)


#df = pyupbit.get_ohlcv("KRW-ETH", count=5)
#print(df)

#orderbook = pyupbit.get_orderbook("KRW-ETH")
bids_asks = orderbook[0]['orderbook_units']
for bid_ask in bids_asks:
    print(bid_ask)
"""

form_class = uic.loadUiType("uiMyWindow.ui")[0]


class MyWindow(QMainWindow, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.timer = QTimer(self)
        self.timer.start(1000)
        self.timer.timeout.connect(self.inquiry)

    def inquiry(self):
        cur_time = QTime.currentTime()
        str_time = cur_time.toString("hh:mm:ss")
        self.statusBar().showMessage(str_time)
        price = pyupbit.get_current_price(["KRW-ETH"])['KRW-ETH']
        self.lineEdit.setText(str(price))


# QApplication 객체 생성 및 이벤트 루프 생성 코드
app = QApplication(sys.argv)
window = MyWindow()
window.show()
app.exec_()
