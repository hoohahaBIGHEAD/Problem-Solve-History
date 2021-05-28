#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

class menuItemType
{
public:

    string menuItem;
    double menuPrice;
};

//파일에서 메뉴를 읽어온다.
inline void getData(ifstream& inFile, menuItemType mList[], int listSize)
{
    string name, str;
    double price;

    ifstream Info;
    int index = 0;

    for (int i = 0; i < listSize; i++)
    {
        getline(inFile, str);

        for (int j = 0; j < str.length(); j++)
        {
            //숫자라면 인덱스 취한다.
            if (isdigit(str.at(j))) // use isdigit() to check that character is a numeric character or not
            {
                index = j;
                break;
            }
        }

        name = str.substr(0, index);
        //위 숫자 인덱스에서 가격을 읽어온다.
        price = atof(str.substr(index, str.length()).c_str()); // use atof(), it interprets the contents of a string as a floating point number 
                                                              // and return its value as a double.
        mList[i].menuItem = name;
        mList[i].menuPrice = price;
    }

    Info.close();
}

//메뉴를 보여준다.
inline void showMenu(menuItemType mList[], int listSize)
{
    cout << "Welcome to Johnny's Restaurant" << endl;

    for (int Numbs = 0; Numbs < listSize; Numbs++)
    {
        cout << left << "# " << Numbs + 1 << " ";
        //글자칸을 20개로 만든 후 이름과 가격을 출력한다.
        cout << setw(20) << mList[Numbs].menuItem << '$' << mList[Numbs].menuPrice << endl;
    }
}

inline void printCheck(menuItemType mList[], int listSize, int cList[], int cListLength)
{
    double Total = 0;
    double Tax = 0;

    const double TAX = .05;

    for (int i = 0; i < listSize; i++)
    {
        if (cList[i] != 0)
        {
            cout << setw(25) << mList[i].menuItem << cList[i] << "\t" << '$' << mList[i].menuPrice * cList[i] << endl;

            Total += (mList[i].menuPrice * cList[i]);
        }
    }

    Tax = Total * TAX;
    Total += Tax;

    cout << setw(32) << "Tax " << "$" << Tax << endl;
    cout << setw(32) << "Total Cost " << "$" << Total << endl;
}

//메뉴가 기존에 선택되었는지 확인
inline bool isItemSelected(int cList[], int cListLength, int itemNo)
{
    //메뉴의 숫자가 0개가 아니라면 참을 반환
    if (cList[itemNo - 1] != 0)
        return true;
    else
        return false;
}

inline void makeSelection(menuItemType mList[], int listSize, int choiceList[], int& cListLength)
{
    cListLength = listSize;
    string ChooseMenuString;
    int ChooseMenu = 0;
    string orderNumString;
    int orderNum = 0;
    bool correctOrderDone = false;

    //메뉴 오더 중이라면
    while (true)
    {
        cout << "What Menu are you going to order? {(Enter the number), (if you are finished, enter finsh) ";
        cin >> ChooseMenuString;
        if (ChooseMenuString == "finish"){
            //주문이 1개라도 완료된 상태라면 while문을 나온다.
            if (correctOrderDone)
            {
                cout << "Order is complete" << endl;
                return;
            }
            else
                cout << "You didn't select menu, choose" << endl;
        }
        else
        {
        
                ChooseMenu = stoi(ChooseMenuString);
                //메뉴를 제대로 선택하지 않았다면
                if (!(ChooseMenu > 0 && ChooseMenu <= listSize))
                    cout << "Wrong input. choose correctly" << endl;
                //메뉴를 제대로 선택했다면
                else
                {
                    //입력이 0 이상이고 메뉴 리스트 안에 존재한다면
                    if (ChooseMenu > 0 && ChooseMenu <= listSize)
                    {
                        //얼마나 주문할지 입력한다.
                        cout << "Enter how many Orders: ";
                        cin >> orderNumString;
                        
                            orderNum = stoi(orderNumString);
                            //0 이상의 제대로 된 정수가 아니라면
                            if (!(orderNum > 0))
                                cout << "Wrong input. choose correctly" << endl;
                            else
                            {
                                //입력이 0 이상이고 메뉴 리스트 안에 존재하고 기존에 선택한 메뉴라면
                                if (isItemSelected(choiceList, cListLength, ChooseMenu))
                                {
                                    //기존의 주문량에 추가한다.
                                    choiceList[ChooseMenu - 1] += orderNum;
                                    //주문이 제대로 되었음을 입력한다.
                                    correctOrderDone = true;
                                }
                                else
                                {
                                    //초이스 리스트 숫자에 주문량을 할당한다.
                                    choiceList[ChooseMenu - 1] = orderNum;
                                    //주문이 제대로 되었음을 입력한다.
                                    correctOrderDone = true;
                                }
                            }
                        
                    }
                }
         
        }
        
    }
}