/*class inheritance*/
/////////////////////////////////////////////////////////////////////////////
//
//  GraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class GraduateStudent : public Student {
private:
	string lab;	//연구실
	string degreeProgram;	//석사박사 과정

public:
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// 생성자. 변수를 7개 받는다.
	GraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string lab, string degreeProgram);
};

