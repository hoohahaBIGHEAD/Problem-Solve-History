/////////////////////////////////////////////////////////////////////////////
//
//  Student
//
/////////////////////////////////////////////////////////////////////////////

/*protected, virtual*/
// Student ����
class Student {
protected:
	//�Է��� �ʿ��� ����
	string name;	//�̸�
	int majorCredit;	//��������
	int minorCredit;	//��������
	float majorGPA;	//��������
	float minorGPA;	//��������

	int tuition;	//��Ϻ�



public:
	//���� ����
	bool apply = false;
	//���Ǵ� ����
	float totalGPA;	//��ü����


	//virtual �Լ� ����
// �л� ������ string���� �������ִ� �Լ�
	virtual string getStudentInfo() { return ""; }
	// ��� ������ float�� �������ִ� �Լ�
	virtual float getGPA() { return 0; }
	// ��Ϻ� int�� �������ִ� �Լ�
	virtual int getTuition() { return 0; }

};
