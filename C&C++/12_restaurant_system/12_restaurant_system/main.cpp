#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "functions.cpp"
using namespace std;
const int NO_OF_ITEMS = 8;
int main()
{
    menuItemType menuList[NO_OF_ITEMS];
    int choiceList[NO_OF_ITEMS];
    int choiceListLength;
    ifstream inFile;
    cout << fixed << showpoint << setprecision(2);
    inFile.open("breakfasts.txt");
    if (!inFile)
    {
        cout << "Cannot open the input file. Program Terminates!"
            << endl;
        return 1;
    }

    for (int i = 0; i < NO_OF_ITEMS; i++)
    {
        choiceList[i] = 0;
    }

    getData(inFile, menuList, NO_OF_ITEMS);
    showMenu(menuList, NO_OF_ITEMS);
    makeSelection(menuList, NO_OF_ITEMS, choiceList, choiceListLength);
    printCheck(menuList, NO_OF_ITEMS, choiceList, choiceListLength);

    // call getData
    // call showMenu
    // call makeSelection
    // call printCheck
    return 0;
}