#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

class menuItemTypeModified
{

public:
    static int numbersOfItemInArray;

    string menuItem;
    double menuPrice;
    int orderNumInClass;

    //링크드 리스트로 변경
    menuItemTypeModified* next = nullptr;
    menuItemTypeModified* prev = nullptr;

    menuItemTypeModified(string menuItem, double menuPrice) {
        this->menuItem = menuItem;
        this->menuPrice = menuPrice;
        this->orderNumInClass = 0;
        //1개 생성될 때마다 어레이의 갯수 추가
        //this->numbersOfItemInArray++;
    }
    
    menuItemTypeModified() {
    }

    // node_initialize : 노드를 초기화하고 메모리를 동적으로 할당
    static menuItemTypeModified* menuItemType_initialize(string menuItem, double menuPrice) {
        // 새로운 노드의 메모리를 힙 영역에 할당
        //menuItemTypeModified* new_node = (menuItemTypeModified*)malloc(sizeof(menuItemTypeModified));
        //menuItemTypeModified* new_node = new menuItemTypeModified();
        menuItemTypeModified* new_node = new menuItemTypeModified(menuItem, menuPrice);
        // 노드의 공간을 힙 영역에 할당
        //new_node->menuItem = menuItem;
        //new_node->menuPrice = menuPrice;
        //new_node->orderNumInClass = 0;

        // 노드의 포인터를 지정
        new_node->next = NULL;
        new_node->prev = NULL;

        // 메모리가 할당된 새로운 노드를 node_pointer 형으로 리턴
        return new_node;
    }

    void getDataInClass(ifstream& inFile) {
        menuItemTypeModified* temp = menuItemType_initialize("temp", 0.0);
        menuItemTypeModified* tail = menuItemType_initialize("tail", 0.0);

        while (!inFile.eof())
        {
            string name, str;
            double price;

            ifstream Info;
            int index = 0;

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
            tail = menuItemType_initialize(name, price);
            temp = this;
            while (temp!=NULL && temp->next != NULL) {
                    temp = temp->next;
                }
            
            //temp->next = tail;

            //this->next = menuItemType_initialize(name, price);
            if (numbersOfItemInArray == 0)
            {
                this->next = tail;
                tail->prev = this;
            }
            else
            {
                temp->next = tail;
                tail->prev = temp;
            }
            numbersOfItemInArray++;
            if (inFile.eof())
            {
                Info.close();
            }
        }
    }

    //메뉴를 보여준다.
    inline void showMenu()
    {
        menuItemTypeModified* temp = menuItemType_initialize("temp", 0.0);

        cout << "Welcome to Johnny's Restaurant" << endl;
        temp = this;
        int Numbs = 0;
        while (temp != NULL) {
            if (temp->menuItem == "head")
            {
                temp = temp->next;
                continue;
            }
            else
            {
                cout << left << "# " << Numbs++ + 1 << " ";
                cout << setw(20) << temp->menuItem << '$' << temp->menuPrice << endl;
                temp = temp->next;
            }
        }
    }

    //메뉴가 기존에 선택되었는지 확인
    inline bool isItemSelected()
    {
        int totalSelected = 0;
        menuItemTypeModified* temp = menuItemType_initialize("temp", 0.0);
        temp = this;
        while (temp != NULL) {
            if (temp->menuItem == "head")
            {
                temp = temp->next;
                continue;
            }
            else
            {
                totalSelected += temp->orderNumInClass;
                temp = temp->next;
            }
        }
        //메뉴의 숫자가 0개가 아니라면 참을 반환
        if (totalSelected == 0)
            return false;
        else
            return true;
    }

    void makeSelection()
    {
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
            if (ChooseMenuString == "finish") {
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
                //입력 값이 다른 문자열이라면 에러를 반환하라
                try
                {
                    ChooseMenu = stoi(ChooseMenuString);
                    //메뉴를 제대로 선택하지 않았다면
                    if (!(ChooseMenu > 0 && ChooseMenu <= numbersOfItemInArray-1))
                        cout << "Wrong input. choose correctly" << endl;
                    //메뉴를 제대로 선택했다면
                    else
                    {
                        //입력이 0 이상이고 메뉴 리스트 안에 존재한다면
                        if (ChooseMenu > 0 && ChooseMenu <= numbersOfItemInArray-1)
                        {
                            //얼마나 주문할지 입력한다.
                            cout << "Enter how many Orders: ";
                            cin >> orderNumString;
                            //제대로 된 정수를 입력하지 않았다면 에러를 반환해라
                            try
                            {
                                orderNum = stoi(orderNumString);
                                //0 이상의 제대로 된 정수가 아니라면
                                if (!(orderNum > 0))
                                    cout << "Wrong input. choose correctly" << endl;
                                else
                                {
                                    int index = 1;
                                    menuItemTypeModified* temp = menuItemType_initialize("temp", 0.0);
                                    temp = this->next;
                                    while (temp != NULL && index != ChooseMenu) {
                                        if (temp->menuItem == "head")
                                        {
                                            temp = temp->next;
                                            continue;
                                        }
                                        else
                                        {
                                            temp = temp->next;
                                            index++;
                                        }
                                    }
                                    //입력이 0 이상이고 메뉴 리스트 안에 존재하고 기존에 선택한 메뉴라면
                                    if (isItemSelected())
                                    {
                                        
                                        //기존의 주문량에 추가한다.
                                        temp->orderNumInClass += orderNum;

                                        //주문이 제대로 되었음을 입력한다.
                                        correctOrderDone = true;
                                    }
                                    else
                                    {
                                        //초이스 리스트 숫자에 주문량을 할당한다.
                                        temp->orderNumInClass = orderNum;
                                        //주문이 제대로 되었음을 입력한다.
                                        correctOrderDone = true;
                                    }
                                }
                            }
                            catch (const std::exception&)
                            {
                                cout << "Wrong input. choose correctly" << endl;
                            }
                        }
                    }
                }
                catch (const std::exception&)
                {
                    cout << "Wrong input. choose correctly" << endl;
                }
            }

        }
    }

    void printCheck()
    {
        double Total = 0;
        double Tax = 0;

        const double TAX = .05;

        menuItemTypeModified* temp = menuItemType_initialize("temp", 0.0);

        cout << "Welcome to Johnny's Restaurant" << endl;
        temp = this;
        int Numbs = 0;
        while (temp != NULL) {
            if (temp->menuItem == "head")
            {
                temp = temp->next;
                continue;
            }
            else
            {
                if (temp->orderNumInClass != 0) {
                    cout << setw(25) << temp->menuItem << temp->orderNumInClass << "\t" << '$' << temp->menuPrice * temp->orderNumInClass << endl;
                    Total += (temp->menuPrice * temp->orderNumInClass);
                }
                temp = temp->next;
            }
        }
        Tax = Total * TAX;
        Total += Tax;

        cout << setw(32) << "Tax " << "$" << Tax << endl;
        cout << setw(32) << "Total Cost " << "$" << Total << endl;
    }
};