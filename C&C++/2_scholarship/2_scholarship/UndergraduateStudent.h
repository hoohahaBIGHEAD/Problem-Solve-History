/*class inheritance*/
/////////////////////////////////////////////////////////////////////////////
//
//  UndergraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class UndergraduateStudent : public Student {
private:
	string circle;	//���Ƹ�

public:
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// ������. ������ 6�� �޴´�.
	UndergraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string circle);
};
