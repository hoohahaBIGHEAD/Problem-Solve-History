#pragma once

#define STUDENTNUMBER 6	//�л� �� ����

//��------------------�Լ� �����------------------��
void menu();	// �޴� ��� �Լ�
//��------------------�Լ� �����------------------��


//��------------------Ŭ���� �����------------------��
/////////////////////////////////////////////////////////////////////////////
//
//  Student
//
/////////////////////////////////////////////////////////////////////////////


// Student ����
class Student {
public:
	//�Է��� �ʿ��� ����
	string name;	//�̸�
	int majorCredit;	//��������
	int minorCredit;	//��������
	float majorGPA;	//��������
	float minorGPA;	//��������

	//���Ǵ� ����
	float totalGPA;	//��ü����
	int tuition;	//��Ϻ�

	//���� ����
	bool apply = false;

	//virtual �Լ� ����
	// �л� ������ string���� �������ִ� �Լ�
	virtual string getStudentInfo() {
		return "";
	}

	// ��� ������ float�� �������ִ� �Լ�
	virtual float getGPA() {
		return 0;
	}

	// ��Ϻ� int�� �������ִ� �Լ�
	virtual int getTuition() {
		return 0;
	}
};

/////////////////////////////////////////////////////////////////////////////
//
//  UndergraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class UndergraduateStudent : public Student {
private:
	string circle;	//���Ƹ�

public:
	// to_string - ������ ���� string���� ����ȯ
	// substr(0, 4) - float�� ���ڸ��� �߶��ִ� �Լ�
	virtual string getStudentInfo() {
		return " - " +
			this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA).substr(0, 4) + " " +
			to_string(this->minorGPA).substr(0, 4) + " " +
			this->circle + " " +
			to_string(this->totalGPA).substr(0, 4) + " " +
			to_string(this->tuition) + "����\n";
	}

	virtual float getGPA() {
		return ((this->majorCredit * this->majorGPA) + (this->minorCredit * this->minorGPA)) / (this->majorCredit + this->minorCredit);
	}

	virtual int getTuition() {
		return ((this->majorCredit * 10) + (this->minorCredit) * 6);
	}

	// ������. ������ 6�� �޴´�.
	UndergraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string circle) {
		this->name = name;
		this->majorCredit = majorCredit;
		this->minorCredit = minorCredit;
		this->majorGPA = majorGPA;
		this->minorGPA = minorGPA;
		this->circle = circle;

		//�������� ����
		this->totalGPA = this->getGPA();
		this->tuition = this->getTuition();
	}
};

/////////////////////////////////////////////////////////////////////////////
//
//  GraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class GraduateStudent : public Student {
private:
	string lab;	//������
	string degreeProgram;	//����ڻ� ����

public:
	// to_string - ������ ���� string���� ����ȯ
	// substr(0, 4) - float�� ���ڸ��� �߶��ִ� �Լ�
	virtual string getStudentInfo() {
		return " - " +
			this->name + " " +
			to_string(this->majorCredit) + " " +
			to_string(this->minorCredit) + " " +
			to_string(this->majorGPA).substr(0, 4) + " " +
			to_string(this->minorGPA).substr(0, 4) + " " +
			this->lab + " " +
			this->degreeProgram + " " +
			to_string(this->totalGPA).substr(0, 4) + " " +
			to_string(this->tuition) + "����\n";
	}

	virtual float getGPA() {
		return ((this->majorCredit * this->majorGPA) * 1.1 + (this->minorCredit * this->minorGPA) * 0.9) / (this->majorCredit + this->minorCredit);
	}

	virtual int getTuition() {
		return ((this->majorCredit * 12) + (this->minorCredit) * 4);
	}

	// ������. ������ 7�� �޴´�.
	GraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string lab, string degreeProgram) {
		this->name = name;
		this->majorCredit = majorCredit;
		this->minorCredit = minorCredit;
		this->majorGPA = majorGPA;
		this->minorGPA = minorGPA;

		this->lab = lab;
		this->degreeProgram = degreeProgram;

		//�������� ����
		this->totalGPA = this->getGPA();
		this->tuition = this->getTuition();
	}
};

/////////////////////////////////////////////////////////////////////////////
//
//  ScholarshipManagement
//
/////////////////////////////////////////////////////////////////////////////

class ScholarshipManagement {
public:
	Student** studentList;	//Student �迭�� �޴� ������
	int num_of_students;	//�л��� ��

	// ������
	ScholarshipManagement(Student** student, int num_of_students) {
		this->studentList = student;
		this->num_of_students = num_of_students;
	}

	/*
	���α׷��� ���� ����
	*/
	void run() {
		while (true)
		{
			int menuIndex;	//�޴� ������ ���� �ε���
			cin >> menuIndex;
			cin.clear();	//������Ʈ ����
			cin.ignore(INT_MAX, '\n');	//\n ����

			string temp;	//Student ������ ���� ������ �޾ƿ��� �ӽ� ����
			string token[10];	//temp�� �޾ƿ� ������ ' '�� �������� �и��� �����ϱ� ���� ��ū �迭
			int tokenIndex;	// Student ���� �� ������ 
			
			/*
			menuIndex�� ���ÿ� ���� �Լ��� �����Ų��.
			menuIndex == 1 - 1. ���б� ���� : �����ϴ� �л� ���� �������� ��ȣ�� �������� �Է��Ѵ�.
			menuIndex == 2 - 2. ���б� ������ ���� : ���б� �������� ������ ����Ѵ�.
			menuIndex == 3 - 3. ���л� ���� : ������ ���� ������ 2���� �����Ѵ�.
			menuIndex == 4 - 4. �����ϱ� : �޽��� ��� �� ���α׷��� �����Ѵ�.
			*/

			//menuIndex == 1 - 1. ���б� ���� : �����ϴ� �л� ���� �������� ��ȣ�� �������� �Է��Ѵ�.
			if (menuIndex == 1) {
				//�л��� + 1��ŭ 1�پ� ������ �޾ƿ´�.
				for (int i = 0; i <= this->num_of_students; i++)
				{
					//num_of_students��ŭ �л� ������ �Է� �޴´�.
					if(i != this->num_of_students){
						cout << " " << i + 1 << ")";

						getline(cin, temp);	//���ڿ� ���鵵 �Է¹޾� temp�� �����ϴ� �Լ�
						istringstream stringStream(temp);	//temp�� ������ ���ۿ��� stream���� �����Ѵ�.
						tokenIndex = 0;	//token �迭�� �������ش�.

						//stringStream�� ���� ���� ���� ���۸� ' '�� �������� ������ token[tokenIndex]�� �����Ѵ�.
						//���� �� tokenIndex�� 1�� ������Ų��.
						//���������� token[]���� temp�� ' '�� �������� ������ �ܾ ����ȴ�.
						while (getline(stringStream, token[tokenIndex], ' '))
							tokenIndex++;

						//��ū ���� 6����� == ���� ������ 6����� == UndergraduateStudent���
						if (tokenIndex == 6) {
							//studentList[i]�� UndergraduateStudent�� �����Ѵ�.
							studentList[i] = new UndergraduateStudent(
								token[0],
								stoi(token[1]),
								stoi(token[2]),
								stof(token[3]),
								stof(token[4]),
								token[5]);
						}
						//��ū ���� 7����� == ���� ������ 7����� == GraduateStudent���
						else if (tokenIndex == 7) {
							//studentList[i]�� GraduateStudent�� �����Ѵ�.
							studentList[i] = new GraduateStudent(
								token[0],
								stoi(token[1]),
								stoi(token[2]),
								stof(token[3]),
								stof(token[4]),
								token[5],
								token[6]);
						}
					}

					//�л��� ���� �޾ƿ��� ���� ��� �л����� ���� ������ ��ȣ�� �����ؼ� �Է� �޴´�.
					else if (i == this->num_of_students) {
						cout << "* ���� ��� �л����� ���� ������ ��ȣ�� �����ؼ� �Է��Ͻÿ�: ";
						getline(cin, temp);	//���ڿ� ���鵵 �Է¹޾� temp�� �����ϴ� �Լ�
						istringstream stringStream(temp);	//temp�� ������ ���ۿ��� stream���� �����Ѵ�.
						tokenIndex = 0;	//token �迭�� �������ش�.

						//stringStream�� ���� ���� ���� ���۸� ' '�� �������� ������ token[tokenIndex]�� �����Ѵ�.
						//���� �� tokenIndex�� 1�� ������Ų��.
						//���������� token[]���� temp�� ' '�� �������� ������ �ܾ ����ȴ�.
						while (getline(stringStream, token[tokenIndex], ' '))
							tokenIndex++;

						//���б� ������ �л����� apply ���θ� true�� �ٲ۴�.
						for (int j = 1; j <= stoi(token[0]); j++)
						{
							studentList[stoi(token[j]) - 1]->apply = true;
						}
					}
				}
			}

			//menuIndex == 2 - 2. ���б� ������ ���� : ���б� �������� ������ ����Ѵ�.
			else if (menuIndex == 2)
			{
				//��ü �л��� �� ���б� ������ �л����� apply ���θ� ���� �л� ������ ����Ѵ�.
				for (int i = 0; i < this->num_of_students; i++) {
					if (studentList[i]->apply)
						cout << studentList[i]->getStudentInfo();
				}
			}
			
			//menuIndex == 3 - 3. ���л� ���� : ������ ���� ������ 2���� �����Ѵ�.
			//��ü �л����� totalGPA�� �޾ƿ� totalGPA[]�� ���� �� ���л����� ������ �ű��.
			//rank[]�� ���л��鰣�� �Ű��� ������ �����Ѵ�.
			else if (menuIndex == 3)
			{
				float totalGPA[STUDENTNUMBER];
				int rank[STUDENTNUMBER];

				//��ü �л����� totalGPA�� �޾ƿ� totalGPA[]�� �����Ѵ�.
				for (int i = 0; i < STUDENTNUMBER; i++) {
					totalGPA[i] = studentList[i]->totalGPA;
					rank[i] = 1;	// ������ �ٸ� ����� ���ϱ� ������ ��� 1���� ���ɼ��� �����Ƿ� �����迭�� 1�� �ʱ�ȭ�Ѵ�. 
				}

				//���л����� ������ �ű��.
				//i��° �л����� GPA�� ���� j��° �л��� �ְ� j��° �л��� ���б��� �����ߴٸ� i��° �л��� ������ ������Ų��.
				//���бݿ� ������ �л��鳢�� ����� ���߱� ������ rank[]���� ���л��鰣�� �Ű��� ������ ����ȴ�.
				for (int i = 0; i < STUDENTNUMBER; i++)
				{
					for (int j = 0; j < STUDENTNUMBER; j++)
						if (totalGPA[i] < totalGPA[j] &&	//i��° �л����� GPA�� ���� j��° �л��� �ְ�
							studentList[i]->apply && studentList[j]->apply)	//j��° �л��� ���б��� �����ߴٸ�
							rank[i]++;	//i��° �л��� ������ ������Ų��.
				}

				//��ü �л��� �߿��� ���б��� ������ �л��� ������ 2�� ���̶�� �ش� �л��� ������ ��½�Ų��.
				for (int i = 0; i < STUDENTNUMBER; i++)
				{
					if (rank[i] <= 2 && studentList[i]->apply)
						cout << studentList[i]->getStudentInfo();
				}
			}


			//menuIndex == 4 - 4. �����ϱ� : �޽��� ��� �� ���α׷��� �����Ѵ�.
			//break�� ���� while���� �������´�.
			else if (menuIndex == 4)
			{
				cout << " - �����մϴ�.";
				break;
			}

			//�� ���ν����� ������ �޴��� �����ش�.
			menu();
		}
	}
};
//��------------------Ŭ���� �����------------------��