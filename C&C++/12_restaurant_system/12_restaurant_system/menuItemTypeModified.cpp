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

    //��ũ�� ����Ʈ�� ����
    menuItemTypeModified* next = nullptr;
    menuItemTypeModified* prev = nullptr;

    menuItemTypeModified(string menuItem, double menuPrice) {
        this->menuItem = menuItem;
        this->menuPrice = menuPrice;
        this->orderNumInClass = 0;
        //1�� ������ ������ ����� ���� �߰�
        //this->numbersOfItemInArray++;
    }
    
    menuItemTypeModified() {
    }

    // node_initialize : ��带 �ʱ�ȭ�ϰ� �޸𸮸� �������� �Ҵ�
    static menuItemTypeModified* menuItemType_initialize(string menuItem, double menuPrice) {
        // ���ο� ����� �޸𸮸� �� ������ �Ҵ�
        //menuItemTypeModified* new_node = (menuItemTypeModified*)malloc(sizeof(menuItemTypeModified));
        //menuItemTypeModified* new_node = new menuItemTypeModified();
        menuItemTypeModified* new_node = new menuItemTypeModified(menuItem, menuPrice);
        // ����� ������ �� ������ �Ҵ�
        //new_node->menuItem = menuItem;
        //new_node->menuPrice = menuPrice;
        //new_node->orderNumInClass = 0;

        // ����� �����͸� ����
        new_node->next = NULL;
        new_node->prev = NULL;

        // �޸𸮰� �Ҵ�� ���ο� ��带 node_pointer ������ ����
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

    //�޴��� �����ش�.
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

    //�޴��� ������ ���õǾ����� Ȯ��
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
        //�޴��� ���ڰ� 0���� �ƴ϶�� ���� ��ȯ
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

        //�޴� ���� ���̶��
        while (true)
        {
            cout << "What Menu are you going to order? {(Enter the number), (if you are finished, enter finsh) ";
            cin >> ChooseMenuString;
            if (ChooseMenuString == "finish") {
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
                //�Է� ���� �ٸ� ���ڿ��̶�� ������ ��ȯ�϶�
                try
                {
                    ChooseMenu = stoi(ChooseMenuString);
                    //�޴��� ����� �������� �ʾҴٸ�
                    if (!(ChooseMenu > 0 && ChooseMenu <= numbersOfItemInArray-1))
                        cout << "Wrong input. choose correctly" << endl;
                    //�޴��� ����� �����ߴٸ�
                    else
                    {
                        //�Է��� 0 �̻��̰� �޴� ����Ʈ �ȿ� �����Ѵٸ�
                        if (ChooseMenu > 0 && ChooseMenu <= numbersOfItemInArray-1)
                        {
                            //�󸶳� �ֹ����� �Է��Ѵ�.
                            cout << "Enter how many Orders: ";
                            cin >> orderNumString;
                            //����� �� ������ �Է����� �ʾҴٸ� ������ ��ȯ�ض�
                            try
                            {
                                orderNum = stoi(orderNumString);
                                //0 �̻��� ����� �� ������ �ƴ϶��
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
                                    //�Է��� 0 �̻��̰� �޴� ����Ʈ �ȿ� �����ϰ� ������ ������ �޴����
                                    if (isItemSelected())
                                    {
                                        
                                        //������ �ֹ����� �߰��Ѵ�.
                                        temp->orderNumInClass += orderNum;

                                        //�ֹ��� ����� �Ǿ����� �Է��Ѵ�.
                                        correctOrderDone = true;
                                    }
                                    else
                                    {
                                        //���̽� ����Ʈ ���ڿ� �ֹ����� �Ҵ��Ѵ�.
                                        temp->orderNumInClass = orderNum;
                                        //�ֹ��� ����� �Ǿ����� �Է��Ѵ�.
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