/////////////////////////////////////////////////////////////////////////////
//
//  Student
//
/////////////////////////////////////////////////////////////////////////////

/*protected, virtual*/
// Student 정의
class Student {
protected:
	//입력이 필요한 변수
	string name;	//이름
	int majorCredit;	//전공학점
	int minorCredit;	//교양학점
	float majorGPA;	//전공평점
	float minorGPA;	//교양평점

	int tuition;	//등록비



public:
	//지원 여부
	bool apply = false;
	//계산되는 변수
	float totalGPA;	//전체평점


	//virtual 함수 정의
// 학생 정보를 string으로 리턴해주는 함수
	virtual string getStudentInfo() { return ""; }
	// 평균 평점을 float로 리턴해주는 함수
	virtual float getGPA() { return 0; }
	// 등록비를 int로 리턴해주는 함수
	virtual int getTuition() { return 0; }

};
