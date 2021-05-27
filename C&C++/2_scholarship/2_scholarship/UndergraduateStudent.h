/*class inheritance*/
/////////////////////////////////////////////////////////////////////////////
//
//  UndergraduateStudent : public Student
//
/////////////////////////////////////////////////////////////////////////////

class UndergraduateStudent : public Student {
private:
	string circle;	//동아리

public:
	virtual string getStudentInfo();
	virtual float getGPA();
	virtual int getTuition();

	// 생성자. 변수를 6개 받는다.
	UndergraduateStudent(string name, int majorCredit, int minorCredit, float majorGPA, float minorGPA, string circle);
};
