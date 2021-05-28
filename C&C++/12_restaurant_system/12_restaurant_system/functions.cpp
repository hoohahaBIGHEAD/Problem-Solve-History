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

//���Ͽ��� �޴��� �о�´�.
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
            //���ڶ�� �ε��� ���Ѵ�.
            if (isdigit(str.at(j))) // use isdigit() to check that character is a numeric character or not
            {
                index = j;
                break;
            }
        }

        name = str.substr(0, index);
        //�� ���� �ε������� ������ �о�´�.
        price = atof(str.substr(index, str.length()).c_str()); // use atof(), it interprets the contents of a string as a floating point number 
                                                              // and return its value as a double.
        mList[i].menuItem = name;
        mList[i].menuPrice = price;
    }

    Info.close();
}

//�޴��� �����ش�.
inline void showMenu(menuItemType mList[], int listSize)
{
    cout << "Welcome to Johnny's Restaurant" << endl;

    for (int Numbs = 0; Numbs < listSize; Numbs++)
    {
        cout << left << "# " << Numbs + 1 << " ";
        //����ĭ�� 20���� ���� �� �̸��� ������ ����Ѵ�.
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

//�޴��� ������ ���õǾ����� Ȯ��
inline bool isItemSelected(int cList[], int cListLength, int itemNo)
{
    //�޴��� ���ڰ� 0���� �ƴ϶�� ���� ��ȯ
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

    //�޴� ���� ���̶��
    while (true)
    {
        cout << "What Menu are you going to order? {(Enter the number), (if you are finished, enter finsh) ";
        cin >> ChooseMenuString;
        if (ChooseMenuString == "finish"){
            //�ֹ��� 1���� �Ϸ�� ���¶�� while���� ���´�.
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
                //�޴��� ����� �������� �ʾҴٸ�
                if (!(ChooseMenu > 0 && ChooseMenu <= listSize))
                    cout << "Wrong input. choose correctly" << endl;
                //�޴��� ����� �����ߴٸ�
                else
                {
                    //�Է��� 0 �̻��̰� �޴� ����Ʈ �ȿ� �����Ѵٸ�
                    if (ChooseMenu > 0 && ChooseMenu <= listSize)
                    {
                        //�󸶳� �ֹ����� �Է��Ѵ�.
                        cout << "Enter how many Orders: ";
                        cin >> orderNumString;
                        
                            orderNum = stoi(orderNumString);
                            //0 �̻��� ����� �� ������ �ƴ϶��
                            if (!(orderNum > 0))
                                cout << "Wrong input. choose correctly" << endl;
                            else
                            {
                                //�Է��� 0 �̻��̰� �޴� ����Ʈ �ȿ� �����ϰ� ������ ������ �޴����
                                if (isItemSelected(choiceList, cListLength, ChooseMenu))
                                {
                                    //������ �ֹ����� �߰��Ѵ�.
                                    choiceList[ChooseMenu - 1] += orderNum;
                                    //�ֹ��� ����� �Ǿ����� �Է��Ѵ�.
                                    correctOrderDone = true;
                                }
                                else
                                {
                                    //���̽� ����Ʈ ���ڿ� �ֹ����� �Ҵ��Ѵ�.
                                    choiceList[ChooseMenu - 1] = orderNum;
                                    //�ֹ��� ����� �Ǿ����� �Է��Ѵ�.
                                    correctOrderDone = true;
                                }
                            }
                        
                    }
                }
         
        }
        
    }
}