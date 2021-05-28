#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "functions.cpp"
#include "menuItemTypeModified.cpp"
#include "menuItemTypeNew.cpp"

using namespace std;
const int NO_OF_ITEMS = 8;

int menuItemTypeModified::numbersOfItemInArray = 0;

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




    
    menuItemTypeNew menuListNew[NO_OF_ITEMS];
    int choiceListNew[NO_OF_ITEMS];
    int choiceListLengthNew;
    ifstream inFileNew;
    inFileNew.open("breakfasts.txt");
    if (!inFileNew)
    {
        cout << "Cannot open the input file. Program Terminates!"
            << endl;
        return 1;
    }
    for (int i = 0; i < NO_OF_ITEMS; i++)
    {
        choiceListNew[i] = 0;
    }

    
    
    (*menuListNew).getDataNew(inFileNew, menuListNew, NO_OF_ITEMS);
    (*menuListNew).showMenuNew(menuListNew, NO_OF_ITEMS);
    (*menuListNew).makeSelectionNew(menuListNew, NO_OF_ITEMS, choiceListNew, choiceListLengthNew);
    (*menuListNew).printCheckNew(menuListNew, NO_OF_ITEMS, choiceListNew, choiceListLengthNew);

    return 0;
}