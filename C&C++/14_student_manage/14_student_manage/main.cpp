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


//정의되는 클래스에 대해 템플릿을 정의
//인자로 T 받음
//T :: 어떠한 타입의 이름
//템플릿을 통해 타입을 전달할 수 있음
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

// node_initialize : 노드를 초기화하고 메모리를 동적으로 할당
student_pointer nodeInitialize(int ID, string Major, string Name) {
	// 새로운 노드의 메모리를 힙 영역에 할당
	student_pointer new_node = (student_pointer)malloc(sizeof(Student_node));

	new_node->ID = ID;
	strcpy_s(new_node->Major, Major.c_str());
	strcpy_s(new_node->Name, Name.c_str());

	new_node->pInput = NULL;
	new_node->pYear = NULL;
	new_node->pMajor = NULL;
	new_node->pAlphabet = NULL;

	// 메모리가 할당된 새로운 노드를 student_pointer 형으로 리턴
	return new_node;
}

//파일에서 학생 정보를 읽어오고 첫 번째 노드를 리턴한다.
student_pointer getData(ifstream& inFile) {
	int ID;
	string Major;
	string Name;

	ifstream Info;

	string tempString;
	string token[3];
	//첫 노드를 반환해주기 위한 포인터
	student_pointer first = NULL;
	//첫 노드인지 확인용
	bool isFirst = true;
	//
	student_pointer newTail = NULL;
	student_pointer previousTail = NULL;


	while (!inFile.eof())
	{
		getline(inFile, tempString);  //문자열 공백도 입력받아 temp에 한 줄을 저장하는 함수
		istringstream stringStream(tempString);	//temp를 복사해 버퍼에서 stream으로 제공한다.
		getline(stringStream, token[0], ',');   //문자열에서 첫 , 앞을 읽어 token[0]에 저장한다
		getline(stringStream, token[1], ',');   //문자열에서 다음 , 앞을 읽어 token[1]에 저장한다.
		getline(stringStream, token[2], ',');   //문자열에서 다음 , 앞을 읽어 token[1]에 저장한다. 없어도 문장이 끝나기 때문에 괜찮다.

		//해당 문자열을 아래에 저장한다.
		ID = stoi(token[0]);
		Major = token[1];
		Name = token[2];

		//새로운 노드 만들어서 temp에 할당
		newTail = nodeInitialize(ID, Major, Name);

		//첫 노드라면 first에 저장해라
		if (isFirst)
		{
			isFirst = false;
			first = newTail;
		}
		else
		{
			//기존의 노드에서 맨 마지막 노드를 찾아라
			previousTail = first;
			while (previousTail != NULL && previousTail->pInput != NULL) {
				previousTail = previousTail->pInput;
			}
			//마지막에 newTail을 붙여라
			previousTail->pInput = newTail;
		}
		// 만약 파일을 끝까지 읽었다면 파일 스트림을 닫고 나가라.
		if (inFile.eof())
		{
			Info.close();
			break;
		}
	}
	//첫 노드 포인터를 반환해라
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
	//해당 줄기가 가리키는 포인터를 리턴해주고, 밖에서는 이 포인터의 말단 노드에 해당 노드를 연결해주자
	//정렬된 해쉬맵을 인풋으로 받아서, 해당 값을 가진 줄기 노드를 찾자
	//값은 년도, 학과, 이니셜이다.
	CNode<T>* returnMiddle(T value) {
		CNode<T>* pThis = head;

		//년도, 학과, 이니셜 등 끝까지 찾도록 하는 함수
		//찾으면 break로 나가자
		while (pThis)
		{
			//해당 노드의 value가 현재 노드와 같다면
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
		//다음 
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
		//다음 
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

	//텍스트 파일을 읽어들여라
	ifstream inFile;
	inFile.open("students.txt");
	//파일이 열리지 않았다면
	if (!inFile)
	{
		cout << "Cannot open the input file. Program Terminates!"
			<< endl;
		return 1;
	}

	pHead = getData(inFile);

	//맵 자료구조
	map<int, student_pointer> mapStudentPointerID;
	map<string, student_pointer> mapStudentPointerName;

	temp = pHead;
	//맵에 넣기
	while (temp) {
		//아이디값을 기준으로 솔팅한다.
		mapStudentPointerID[temp->ID] = temp;
		mapStudentPointerName[temp->Name] = temp;

		temp = temp->pInput;
	}

	temp = pHead;

	//년도를 중복 없이 저장한다.
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

	// 정렬
// 첫번째 인자 = 배열의 포인터
	CLinkedList<int> Year_Head;
	// 두번째 인자 = 배열의 포인터 + 배열의 크기
	//년도 정렬
	sort(Year, Year + YearIndex);
	//순서대로 노드에 추가한다.
	for (size_t i = 0; i < YearIndex; i++)
		Year_Head.add(Year[i]);
	//Year_Head.printAll();



	//노드를 처음부터 검사
	temp = pHead;
	//학과를 중복 없이 저장한다.
	isIn = false;
	count = 0;  //전체학생수
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

	// 정렬
// 첫번째 인자 = 배열의 포인터
// 두번째 인자 = 배열의 포인터 + 배열의 크기
	//년도 정렬
	sort(Major, Major + MajorIndex);
	//순서대로 노드에 추가한다.
	CLinkedList<string> Major_Head;
	for (size_t i = 0; i < MajorIndex; i++)
		Major_Head.add(Major[i]);
	//Major_Head.printAll();


	//노드를 처음부터 검사
	temp = pHead;
	//학과를 중복 없이 저장한다.
	isIn = false;
	count = 0;  //전체학생수
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

	// 정렬
// 첫번째 인자 = 배열의 포인터
// 두번째 인자 = 배열의 포인터 + 배열의 크기
	//년도 정렬
	sort(Alphabet, Alphabet + AlphabetIndex);
	//순서대로 노드에 추가한다.
	CLinkedList<char> Alphabet_Head;
	for (size_t i = 0; i < AlphabetIndex; i++)
		Alphabet_Head.add(Alphabet[i]);
	//Alphabet_Head.printAll();



	//해시맵을 사용해 줄기노드를 추출하기
	//year 입력
	map<int, student_pointer>::iterator itID;
	for (itID = mapStudentPointerID.begin(); itID != mapStudentPointerID.end(); ++itID) {
		//만약 NULL 값이라면 해당 포인터를 넘겨주라
		temp = Year_Head.returnMiddle(itID->second->ID / 1000000)->pStudentLeaf;
		if (temp == NULL)
			Year_Head.returnMiddle(itID->second->ID / 1000000)->pStudentLeaf = itID->second;
		//노드의 끝까지 가서 
		else
		{
			while (temp->pYear) //다음 칸이 널이 될 때까지 <> 마지막 노드까지 가라
				temp = temp->pYear;
			temp->pYear = itID->second;   //마지막 노드의 다음 노드로 얘를 넣어라.

		}
	}

	//해시맵을 사용해 줄기노드를 추출하기
	//major 입력
	map<int, student_pointer>::iterator itMajor;
	for (itMajor = mapStudentPointerID.begin(); itMajor != mapStudentPointerID.end(); ++itMajor) {
		//만약 NULL 값이라면 해당 포인터를 넘겨주라
		temp = Major_Head.returnMiddle(itMajor->second->Major)->pStudentLeaf;
		if (temp == NULL)
			Major_Head.returnMiddle(itMajor->second->Major)->pStudentLeaf = itMajor->second;
		//노드의 끝까지 가서 
		else
		{
			while (temp->pMajor) //다음 칸이 널이 될 때까지 <> 마지막 노드까지 가라
				temp = temp->pMajor;
			temp->pMajor = itMajor->second;   //마지막 노드의 다음 노드로 얘를 넣어라.
		}
	}

	//이름순은 이름순으로 나열
	//해시맵을 사용해 줄기노드를 추출하기
	//name 입력
	map<string, student_pointer>::iterator itName;
	for (itName = mapStudentPointerName.begin(); itName != mapStudentPointerName.end(); ++itName) {
		//만약 NULL 값이라면 해당 포인터를 넘겨주라
		temp = Alphabet_Head.returnMiddle(itName->second->Name[0])->pStudentLeaf;
		if (temp == NULL)
			Alphabet_Head.returnMiddle(itName->second->Name[0])->pStudentLeaf = itName->second;
		//노드의 끝까지 가서 
		else
		{
			while (temp->pAlphabet) //다음 칸이 널이 될 때까지 <> 마지막 노드까지 가라
				temp = temp->pAlphabet;
			temp->pAlphabet = itName->second;   //마지막 노드의 다음 노드로 얘를 넣어라.
		}
	}

	//메뉴를 출력한다.
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
			printf("잘못된 입력입니다.\n");
		}
	}

	return 0;
}