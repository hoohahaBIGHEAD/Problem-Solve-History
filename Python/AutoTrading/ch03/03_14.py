# ch03/03_14.py
import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic
from PyQt5.QtCore import *
import pyupbit

access_key = ""
secret_key = ""

# 계좌 및 주문 연결, 잔고 조회
upbit = pyupbit.Upbit(access_key, secret_key)
print(upbit.get_balances())

'''
# 매수 코인, 매수 가격, 갯수
ret = upbit.buy_limit_order("KRW-ETH", 100, 20)
print(ret)

# 매수 코인, 매수 가격, 갯수
ret = upbit.sell_limit_order("KRW-XRP", 1000, 20)
print(ret)
'''


'''
# 티커 조회
tickers = pyupbit.get_tickers()
print(tickers)
'''

'''
# 한화 티커 조회
tickers = pyupbit.get_tickers(fiat="KRW")
print(tickers)

# 코인 현재가 조회 - 이더리움
price = pyupbit.get_current_price("KRW-ETH")
print(price)

# 코인 현재가 여러 개 조회
#price = pyupbit.get_current_price(["BTC-XRP", "KRW-XRP"])
#print(price)


# 코인 전체 가격 조회
tickers = pyupbit.get_tickers(fiat="KRW")
price = pyupbit.get_current_price(tickers)
for i in price:
    print(i + ":\t" + str(price[i]))
'''



# 이동평균 구하는 함수
def bull_market(ticker):
    df = pyupbit.get_ohlcv(ticker)
    ma5 = df['close'].rolling(window=5).mean()
    price = pyupbit.get_current_price(ticker)
    last_ma5 = ma5[-2]

    if price is not None:
        if price > last_ma5:
            print(ticker, "상승장")
    #        return True
        else:
            print(ticker, "하락장")
    #        return False

tickers = pyupbit.get_tickers(fiat="KRW")
for ticker in tickers:
    bull_market(ticker)
    '''
    is_bull = bull_market(ticker)
    if is_bull:
        print(ticker, "상승장")
    else:
        print(ticker, "하락장")
    '''
'''
# 과거 데이터 조회
# interval= 월(month), 주(week), 분(minute+숫자), 일(day) 중 선택
# count= 가져오려는 데이터의 갯수
#df = pyupbit.get_ohlcv("KRW-BTC", interval="month")
df = pyupbit.get_ohlcv("KRW-ETH")
#df = df.drop(columns=['volume', 'value'], axis=1)
# 열 1개만 가져오기
close = df['close']
# 이동평균 구하기
window = close.rolling(5)
ma5 = window.mean()
print(ma5)
last_ma5 = ma5[-2]

price = pyupbit.get_current_price("KRW-ETH")

if price > last_ma5:
    print("상승장")
else:
    print("하락장")

'''

'''
# 호가 조회
orderbook = pyupbit.get_orderbook("KRW-BTC")
print(orderbook)

# 10호가 표로 조회
orderbook = pyupbit.get_orderbook("KRW-ETH")
bids_asks = orderbook[0]['orderbook_units']

for bid_ask in bids_asks:
    print(bid_ask)
'''

'''
df = pyupbit.get_ohlcv("KRW-ETH", count=5)
print(df)

orderbook = pyupbit.get_orderbook("KRW-ETH")
bids_asks = orderbook[0]['orderbook_units']
for bid_ask in bids_asks:
    print(bid_ask)
'''

'''
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

'''
'''
class MySignal(QObject):
    signal1 = pyqtSignal()
    signal2 = pyqtSignal(int, int)

    def run(self):
        self.signal1.emit()
        self.signal2.emit(1, 2)


class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        mysignal = MySignal()
        mysignal.signal1.connect(self.signal1_emitted)
        mysignal.signal2.connect(self.signal2_emitted)
        mysignal.run()

    @pyqtSlot()
    def signal1_emitted(self):
        print("signal1 emitted")

    @pyqtSlot(int, int)
    def signal2_emitted(self, arg1, arg2):
        print("signal2 emitted", arg1, arg2)

# QApplication 객체 생성 및 이벤트 루프 생성 코드
app = QApplication(sys.argv)
window = MyWindow()
window.show()
app.exec_()

import requests
from bs4 import BeautifulSoup

url = "http://finance.naver.com/item/main.nhn?code=000660"
html = requests.get(url).text
soup = BeautifulSoup(html, "html5lib")
tags = soup.select("#_per")
tag = tags[0]
print(tag.text)
'''