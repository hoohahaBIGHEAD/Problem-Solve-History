/*class inheritance*/
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
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// ������. ������ 7�� �޴´�.
	GraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string lab, string degreeProgram);
};

