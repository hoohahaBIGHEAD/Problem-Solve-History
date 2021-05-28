#include <string>
#include <iostream>
#include <fstream>	//ifstream
#include <sstream>  // istringstream
#include <algorithm>    // sort()
#include <map>

using namespace std;

#define MAXCHAR 30
#define MAXSTUDENTNUMBER 100

typedef struct _Student_node* student_pointer;
typedef struct _Student_node {
	int ID;
	char Major[MAXCHAR];
	char Name[MAXCHAR];

	student_pointer pInput, pYear, pMajor, pAlphabet;

} Student_node;


//���ǵǴ� Ŭ������ ���� ���ø��� ����
//���ڷ� T ����
//T :: ��� Ÿ���� �̸�
//���ø��� ���� Ÿ���� ������ �� ����
template <typename T>
student_pointer List2d(T a) {
	typedef struct List2d {

		List2d(T _value) {
			value = _value;
		}

		T value;
		List2d* nextT;
		student_pointer Student;
	};
}

// node_initialize : ��带 �ʱ�ȭ�ϰ� �޸𸮸� �������� �Ҵ�
student_pointer nodeInitialize(int ID, string Major, string Name) {
	// ���ο� ����� �޸𸮸� �� ������ �Ҵ�
	student_pointer new_node = (student_pointer)malloc(sizeof(Student_node));

	new_node->ID = ID;
	strcpy_s(new_node->Major, Major.c_str());
	strcpy_s(new_node->Name, Name.c_str());

	new_node->pInput = NULL;
	new_node->pYear = NULL;
	new_node->pMajor = NULL;
	new_node->pAlphabet = NULL;

	// �޸𸮰� �Ҵ�� ���ο� ��带 student_pointer ������ ����
	return new_node;
}

//���Ͽ��� �л� ������ �о���� ù ��° ��带 �����Ѵ�.
student_pointer getData(ifstream& inFile) {
	int ID;
	string Major;
	string Name;

	ifstream Info;

	string tempString;
	string token[3];
	//ù ��带 ��ȯ���ֱ� ���� ������
	student_pointer first = NULL;
	//ù ������� Ȯ�ο�
	bool isFirst = true;
	//
	student_pointer newTail = NULL;
	student_pointer previousTail = NULL;


	while (!inFile.eof())
	{
		getline(inFile, tempString);  //���ڿ� ���鵵 �Է¹޾� temp�� �� ���� �����ϴ� �Լ�
		istringstream stringStream(tempString);	//temp�� ������ ���ۿ��� stream���� �����Ѵ�.
		getline(stringStream, token[0], ',');   //���ڿ����� ù , ���� �о� token[0]�� �����Ѵ�
		getline(stringStream, token[1], ',');   //���ڿ����� ���� , ���� �о� token[1]�� �����Ѵ�.
		getline(stringStream, token[2], ',');   //���ڿ����� ���� , ���� �о� token[1]�� �����Ѵ�. ��� ������ ������ ������ ������.

		//�ش� ���ڿ��� �Ʒ��� �����Ѵ�.
		ID = stoi(token[0]);
		Major = token[1];
		Name = token[2];

		//���ο� ��� ���� temp�� �Ҵ�
		newTail = nodeInitialize(ID, Major, Name);

		//ù ����� first�� �����ض�
		if (isFirst)
		{
			isFirst = false;
			first = newTail;
		}
		else
		{
			//������ ��忡�� �� ������ ��带 ã�ƶ�
			previousTail = first;
			while (previousTail != NULL && previousTail->pInput != NULL) {
				previousTail = previousTail->pInput;
			}
			//�������� newTail�� �ٿ���
			previousTail->pInput = newTail;
		}
		// ���� ������ ������ �о��ٸ� ���� ��Ʈ���� �ݰ� ������.
		if (inFile.eof())
		{
			Info.close();
			break;
		}
	}
	//ù ��� �����͸� ��ȯ�ض�
	return first;

}


template<typename T> struct CNode
{
	CNode(T _value)
	{
		value = _value;
	}
	student_pointer pStudentLeaf;
	CNode* next;
	T value;
};
template<typename T> class CLinkedList {
private:

	CNode<T>* head;
	CNode<T>* tail;
	int count;
public:
	CLinkedList() : head(NULL), tail(NULL), count(0)
	{
	}
	~CLinkedList()
	{
	}
public:
	//�ش� �ٱⰡ ����Ű�� �����͸� �������ְ�, �ۿ����� �� �������� ���� ��忡 �ش� ��带 ����������
	//���ĵ� �ؽ����� ��ǲ���� �޾Ƽ�, �ش� ���� ���� �ٱ� ��带 ã��
	//���� �⵵, �а�, �̴ϼ��̴�.
	CNode<T>* returnMiddle(T value) {
		CNode<T>* pThis = head;

		//�⵵, �а�, �̴ϼ� �� ������ ã���� �ϴ� �Լ�
		//ã���� break�� ������
		while (pThis)
		{
			//�ش� ����� value�� ���� ���� ���ٸ�
			if (pThis->value == value)
				return pThis;
			else
				pThis = pThis->next;
		}
	}

	int add(T item)
	{
		CNode<T>* newNode = new CNode<T>(item);
		if (count == 0)
		{
			head = newNode;
			tail = newNode;
			newNode->pStudentLeaf = NULL;
			newNode->next = NULL;
		}
		else
		{
			newNode->pStudentLeaf = NULL;
			newNode->next = NULL;
			tail->next = newNode;
			tail = newNode;
		}
		++count;
		return count;
	}

	int getSize()
	{
		return count;
	}

	void printAll()
	{
		if (count > 0)
		{
			CNode<T>* pThis = head;
			while (pThis)
			{
				cout << pThis->value << endl;
				pThis = pThis->next;
			}
		}
	}

	CNode<T>* getHead()
	{
		return head;
	}
	CNode<T>* getTail()
	{
		return tail;
	}
};

void PrintFile(student_pointer pHead) {
	student_pointer Head = pHead;
	printf("Print File\n");
	printf("==========================================================\n");
	printf("StudentID\tMajor\t\t\t\tName\n");
	while (Head != NULL)
	{
		if (strlen(Head->Major) < 15)
			cout << Head->ID << "\t" << Head->Major << "\t\t\t" << Head->Name << endl;
		else
			cout << Head->ID << "\t" << Head->Major << "\t\t" << Head->Name << endl;
		Head = Head->pInput;
	}
	printf("==========================================================\n");
}

void PrintByID(CLinkedList<int> cl) {
	CNode<int>* pThis = cl.getHead();
	student_pointer Head;
	printf("Print by ID\n");
	printf("==========================================================\n");
	while (pThis)
	{
		cout << pThis->value << endl;
		printf("StudentID\tMajor\t\t\t\tName\n");
		Head = pThis->pStudentLeaf;
		while (Head)
		{
			if (strlen(Head->Major) < 15)
				cout << Head->ID << "\t" << Head->Major << "\t\t\t" << Head->Name << endl;
			else
				cout << Head->ID << "\t" << Head->Major << "\t\t" << Head->Name << endl;
			Head = Head->pYear;
		}
		cout << endl;
		pThis = pThis->next;
	}
	printf("==========================================================\n");
}

void PrintByMajor(CLinkedList<string> cl) {
	CNode<string>* pThis = cl.getHead();
	student_pointer Head;
	printf("Print by Major\n");
	printf("==========================================================\n");
	while (pThis)
	{
		cout << pThis->value << endl;
		printf("StudentID\tMajor\t\t\t\tName\n");
		//���� 
		Head = pThis->pStudentLeaf;
		while (Head)
		{
			if (strlen(Head->Major) < 15)
				cout << Head->ID << "\t" << Head->Major << "\t\t\t" << Head->Name << endl;
			else
				cout << Head->ID << "\t" << Head->Major << "\t\t" << Head->Name << endl;
			Head = Head->pMajor;
		}
		cout << endl;
		pThis = pThis->next;
	}
	printf("==========================================================\n");
}

void PrintByName(CLinkedList<char> cl) {
	CNode<char>* pThis = cl.getHead();
	student_pointer Head;
	printf("Print by Name\n");
	printf("==========================================================\n");
	while (pThis)
	{
		cout << pThis->value << endl;
		printf("StudentID\tMajor\t\t\t\tName\n");
		//���� 
		Head = pThis->pStudentLeaf;
		while (Head)
		{
			if (strlen(Head->Major) < 15)
				cout << Head->ID << "\t" << Head->Major << "\t\t\t" << Head->Name << endl;
			else
				cout << Head->ID << "\t" << Head->Major << "\t\t" << Head->Name << endl;
			Head = Head->pAlphabet;
		}
		cout << endl;
		pThis = pThis->next;
	}
	printf("==========================================================\n");
}

int main() {

	student_pointer temp, pHead;
	student_pointer tempStudent[MAXSTUDENTNUMBER];

	int Year[10] = { 0 };
	string Major[10];
	char Alphabet[10];
	int YearIndex, MajorIndex, AlphabetIndex;
	YearIndex = 0;
	MajorIndex = 0;
	AlphabetIndex = 0;

	//�ؽ�Ʈ ������ �о�鿩��
	ifstream inFile;
	inFile.open("students.txt");
	//������ ������ �ʾҴٸ�
	if (!inFile)
	{
		cout << "Cannot open the input file. Program Terminates!"
			<< endl;
		return 1;
	}

	pHead = getData(inFile);

	//�� �ڷᱸ��
	map<int, student_pointer> mapStudentPointerID;
	map<string, student_pointer> mapStudentPointerName;

	temp = pHead;
	//�ʿ� �ֱ�
	while (temp) {
		//���̵��� �������� �����Ѵ�.
		mapStudentPointerID[temp->ID] = temp;
		mapStudentPointerName[temp->Name] = temp;

		temp = temp->pInput;
	}

	temp = pHead;

	//�⵵�� �ߺ� ���� �����Ѵ�.
	bool isIn = false;
	int count = 0;
	while (temp)
	{
		if (YearIndex == 0)
		{
			Year[0] = temp->ID / 1000000;
			YearIndex++;
		}
		else
		{
			for (size_t i = 0; i < YearIndex; i++)
				if (Year[i] == (temp->ID / 1000000)) {
					isIn = true;
					break;
				}
			if (!isIn) {
				Year[YearIndex] = temp->ID / 1000000;
				YearIndex++;
			}
			isIn = false;
		}
		temp = temp->pInput;
		count++;
	}

	// ����
// ù��° ���� = �迭�� ������
	CLinkedList<int> Year_Head;
	// �ι�° ���� = �迭�� ������ + �迭�� ũ��
	//�⵵ ����
	sort(Year, Year + YearIndex);
	//������� ��忡 �߰��Ѵ�.
	for (size_t i = 0; i < YearIndex; i++)
		Year_Head.add(Year[i]);
	//Year_Head.printAll();



	//��带 ó������ �˻�
	temp = pHead;
	//�а��� �ߺ� ���� �����Ѵ�.
	isIn = false;
	count = 0;  //��ü�л���
	while (temp)
	{
		if (MajorIndex == 0)
		{
			Major[0] = temp->Major;
			MajorIndex++;
		}
		else
		{
			for (size_t i = 0; i < MajorIndex; i++)
				if (Major[i] == (temp->Major)) {
					isIn = true;
					break;
				}
			if (!isIn) {
				Major[MajorIndex] = temp->Major;
				MajorIndex++;
			}
			isIn = false;
		}
		temp = temp->pInput;
		count++;
	}

	// ����
// ù��° ���� = �迭�� ������
// �ι�° ���� = �迭�� ������ + �迭�� ũ��
	//�⵵ ����
	sort(Major, Major + MajorIndex);
	//������� ��忡 �߰��Ѵ�.
	CLinkedList<string> Major_Head;
	for (size_t i = 0; i < MajorIndex; i++)
		Major_Head.add(Major[i]);
	//Major_Head.printAll();


	//��带 ó������ �˻�
	temp = pHead;
	//�а��� �ߺ� ���� �����Ѵ�.
	isIn = false;
	count = 0;  //��ü�л���
	while (temp)
	{
		if (AlphabetIndex == 0)
		{
			Alphabet[0] = temp->Name[0];
			AlphabetIndex++;
		}
		else
		{
			for (size_t i = 0; i < AlphabetIndex; i++)
				if (Alphabet[i] == (temp->Name[0])) {
					isIn = true;
					break;
				}
			if (!isIn) {
				Alphabet[AlphabetIndex] = temp->Name[0];
				AlphabetIndex++;
			}
			isIn = false;
		}
		temp = temp->pInput;
		count++;
	}

	// ����
// ù��° ���� = �迭�� ������
// �ι�° ���� = �迭�� ������ + �迭�� ũ��
	//�⵵ ����
	sort(Alphabet, Alphabet + AlphabetIndex);
	//������� ��忡 �߰��Ѵ�.
	CLinkedList<char> Alphabet_Head;
	for (size_t i = 0; i < AlphabetIndex; i++)
		Alphabet_Head.add(Alphabet[i]);
	//Alphabet_Head.printAll();



	//�ؽø��� ����� �ٱ��带 �����ϱ�
	//year �Է�
	map<int, student_pointer>::iterator itID;
	for (itID = mapStudentPointerID.begin(); itID != mapStudentPointerID.end(); ++itID) {
		//���� NULL ���̶�� �ش� �����͸� �Ѱ��ֶ�
		temp = Year_Head.returnMiddle(itID->second->ID / 1000000)->pStudentLeaf;
		if (temp == NULL)
			Year_Head.returnMiddle(itID->second->ID / 1000000)->pStudentLeaf = itID->second;
		//����� ������ ���� 
		else
		{
			while (temp->pYear) //���� ĭ�� ���� �� ������ <> ������ ������ ����
				temp = temp->pYear;
			temp->pYear = itID->second;   //������ ����� ���� ���� �긦 �־��.

		}
	}

	//�ؽø��� ����� �ٱ��带 �����ϱ�
	//major �Է�
	map<int, student_pointer>::iterator itMajor;
	for (itMajor = mapStudentPointerID.begin(); itMajor != mapStudentPointerID.end(); ++itMajor) {
		//���� NULL ���̶�� �ش� �����͸� �Ѱ��ֶ�
		temp = Major_Head.returnMiddle(itMajor->second->Major)->pStudentLeaf;
		if (temp == NULL)
			Major_Head.returnMiddle(itMajor->second->Major)->pStudentLeaf = itMajor->second;
		//����� ������ ���� 
		else
		{
			while (temp->pMajor) //���� ĭ�� ���� �� ������ <> ������ ������ ����
				temp = temp->pMajor;
			temp->pMajor = itMajor->second;   //������ ����� ���� ���� �긦 �־��.
		}
	}

	//�̸����� �̸������� ����
	//�ؽø��� ����� �ٱ��带 �����ϱ�
	//name �Է�
	map<string, student_pointer>::iterator itName;
	for (itName = mapStudentPointerName.begin(); itName != mapStudentPointerName.end(); ++itName) {
		//���� NULL ���̶�� �ش� �����͸� �Ѱ��ֶ�
		temp = Alphabet_Head.returnMiddle(itName->second->Name[0])->pStudentLeaf;
		if (temp == NULL)
			Alphabet_Head.returnMiddle(itName->second->Name[0])->pStudentLeaf = itName->second;
		//����� ������ ���� 
		else
		{
			while (temp->pAlphabet) //���� ĭ�� ���� �� ������ <> ������ ������ ����
				temp = temp->pAlphabet;
			temp->pAlphabet = itName->second;   //������ ����� ���� ���� �긦 �־��.
		}
	}

	//�޴��� ����Ѵ�.
	int menuIndex = 0;
	while (true)
	{
		printf("1. Print File\n");
		printf("2. Print by ID\n");
		printf("3. Print by Major\n");
		printf("4. Print by Name\n");
		printf("5. Program End\n");
		cin >> menuIndex;
		if (menuIndex == 1)
		{
			PrintFile(pHead);
		}
		else if (menuIndex == 2)
		{
			PrintByID(Year_Head);
		}
		else if (menuIndex == 3)
		{
			PrintByMajor(Major_Head);
		}
		else if (menuIndex == 4)
		{
			PrintByName(Alphabet_Head);
		}
		else if (menuIndex == 5)
		{
			break;
		}
		else
		{
			printf("�߸��� �Է��Դϴ�.\n");
		}
	}

	return 0;
}