#include<iostream>
#include <cstring>
using namespace std;

#define NAME_SIZE 32        // 최대 이름 길이
#define MEMBER_MAX 10       // 최대 회원 수
#define LOCKER_SIZE 4       // 락커룸 크기
#define ADDRESS_SIZE 128    // 최대 주소 길이
#define PHONE_SIZE 15       // 최대 전화번호 길이

struct gym_member
{
    char str_name[NAME_SIZE]; // 이름
    char str_address[ADDRESS_SIZE]; // 주소
    char str_phone[PHONE_SIZE]; // 전화번호
    int height; // 키
    int weight; // 몸무게
    float bmi; // BMI
    int locker_number; // 현재 점유하고 있는 락커룸 번호. 점유하지 않는 경우 0
    int total_exercise_time; // 오늘의 운동시간 총합
};

enum menu
{
    MENU_NONE,
    MENU_MEMBER_INSERT,
    MENU_MEMBER_DELETE,
    MENU_MEMBER_SEARCH,
    MENU_LOCKER_OUTPUT,
    MENU_EXERCISE_TIME_CHECK,
    MENU_EXIT
};


int main()
{
    // 초기 선언
    gym_member gym_member_arr[MEMBER_MAX] = {}; // 회원 정보 배열
    int number_of_members = 0; // 현재 회원 수
    char str_name[NAME_SIZE] = {};   // 회원 검색을 할 때 사용

    cout << " ---------헬스장 회원관리---------" << endl;
    cout << " 1. 회원 등록" << endl;
    cout << " 2. 회원 삭제" << endl;
    cout << " 3. 회원 탑색" << endl;
    cout << " 4. 락커룸 사용 유무" << endl;
    cout << " 5. 총 운동 시간 체크" << endl;
    cout << " 6. 종료" << endl;

    // 종료 명령이 입력될 때까지 메뉴 입력을 반복한다.
    while (true)
    {
        cout << "\n메뉴를 선택하세요: ";

        // 입력 받기
        int iMenu;
        cin >> iMenu;

        // 입력이 정상적이지 않을 경우, 다시 입력을 받는다.
        if (cin.fail())
        {
            cin.clear();

            continue;
        }

        // 반복문 탈출
        if (iMenu == MENU_EXIT)
            break;

        switch (iMenu)
        {
            /* 회원 등록
             * 회원 정보를 입력하여 회원을 등록한다
             * 회원 수가 한계에 도달한 경우 회원가입을 하지 않는다.
             * 이름, 주소, 전화번호, 키, 몸무게, BMI, 락커룸 번호 순으로 회원 정보를 입력받는다.
             * 락커룸 번호 입력의 경우 락커룸 번호가 유효한 범위에 있는 경우에만 동작한다.
             * 등록하고자 하는 락커룸 번호에 이미 다른 회원이 등록되어 있는 경우 기존 회원의 락커룸 번호를 박탈하고 현재 가입할 회원이 해당 락커룸을 가지게 된다.
             */

        case MENU_MEMBER_INSERT:
            cout << " ==========회원정보 입력=============" << endl;
            // 현재 회원의 수가 최대 회원 수에 도달한 경우 회원정보 입력을 하지 않는다.
            if (number_of_members == MEMBER_MAX)
            {
                cout << "현재 최대 회원 수에 도달했습니다. 회원을 추가하려면 기존의 회원을 삭제해 주세요." << endl;
                break;
            }

            // 회원 정보를 차례대로 입력받는다.

            cout << "이름: ";
            cin >> gym_member_arr[number_of_members].str_name;

            cin.ignore(1024, '\n');

            cout << "주소: ";
            cin.getline(gym_member_arr[number_of_members].str_address, ADDRESS_SIZE);

            cout << "전화번호: ";
            cin.getline(gym_member_arr[number_of_members].str_phone, PHONE_SIZE);

            cout << "키: ";
            cin >> gym_member_arr[number_of_members].height;
            cout << "몸무게: ";
            cin >> gym_member_arr[number_of_members].weight;
            gym_member_arr[number_of_members].bmi = gym_member_arr[number_of_members].weight / (gym_member_arr[number_of_members].height * gym_member_arr[number_of_members].height / 10000);
            cout << "락커룸 번호: ";
            int num_locker;
            cin >> num_locker;
            // 락커룸 번호가 유효한 경우에만 동작한다.
            if (num_locker >= 1 && num_locker <= LOCKER_SIZE)
            {
                // 기존에 같은 번호를 가지고 있던 락커 주인의 권한을 없앤다.
                for (int i = 0; i < MEMBER_MAX; i++)
                {
                    if (gym_member_arr[i].locker_number == num_locker)
                    {
                        gym_member_arr[i].locker_number = 0;
                        break;
                    }
                }
                gym_member_arr[number_of_members].locker_number = num_locker;
            }

            ++number_of_members;

            cout << "회원 추가 완료 " << endl;

            break;
        case MENU_MEMBER_DELETE:
            /* 회원 삭제
             * 회원을 삭제한다.
             * 삭제할 회원의 이름을 입력한다.
             * 회원을 찾으면 해당 회원이 삭제된다.
             *
             * 회원 삭제 로직은 다음과 같다.
             * 1. 삭제하고자 하는 회원의 이름을 입력한다.
             * 만약 해당하는 회원이 존재하지 않으면, 회원이 존재하지 않는다는 메세지를 남기고 종료한다.
             * 2. 회원 배열에서 해당하는 이름의 사람을 한 명 찾는다.
             * 3. 해당 회원 뒤의 회원들을 배열에서 한 차례씩 앞으로 당겨준다.
             * 4. "회원이 삭제되었습니다" 메세지를 출력한다.
             */
            cout << "==========회원 삭제==========" << endl;

            cin.ignore(1024, '\n');
            cout << "삭제할 이름을 입력: ";
            cin.getline(str_name, NAME_SIZE);

            bool contains0;
            contains0 = false;
            // 회원 배열 순회
            for (int i = 0; i < number_of_members; ++i)
            {
                // 일치하는 회원이 나온 경우
                if (strcmp(gym_member_arr[i].str_name, str_name) == 0)
                {
                    contains0 = true;
                    // 뒤에 가입한 회원들의 번호를 한 칸씩 앞으로 당겨준다.
                    for (int j = i; j < number_of_members - 1; ++j)
                    {
                        gym_member_arr[i] = gym_member_arr[i + 1];
                    }
                    --number_of_members;

                    cout << "회원이 삭제되었습니다" << endl;
                    break;
                }
            }
            // 회원이 존재하지 않는 경우 해당 회원이 존재하지 않는다는 메세지를 남긴다.
            if (!contains0)
                cout << "회원이 존재하지 않습니다." << endl;

            break;
        case MENU_MEMBER_SEARCH:
            /* 회원 검색
             * 회원을 검색한다.
             * 검색할 회원의 이름을 입력한다.
             * 회원을 찾으면 회원의 정보를 출력한다.
             */
            cout << "==========회원 검색==========" << endl;

            cin.ignore(1024, '\n');
            cout << "검색할 회원의 이름을 입력: ";
            cin.getline(str_name, NAME_SIZE);

            bool done;
            done = false;
            for (int i = 0; i < number_of_members; ++i)
            {
                // 일치하는 회원이 나온 경우
                if (strcmp(gym_member_arr[i].str_name, str_name) == 0)
                {
                    cout << "이름: " << gym_member_arr[i].str_name << endl;
                    cout << "주소: " << gym_member_arr[i].str_address << endl;
                    cout << "전화번호: " << gym_member_arr[i].str_phone << endl;
                    cout << "키: " << gym_member_arr[i].height << endl;
                    cout << "몸무게: " << gym_member_arr[i].weight << endl;
                    cout << "BMI: " << gym_member_arr[i].bmi << endl;
                    cout << "락커룸 번호: " << gym_member_arr[i].locker_number << endl << endl;
                    done = true;
                    //break;
                }
            }
            // 회원이 존재하지 않는 경우 해당 회원이 존재하지 않는다는 메세지를 남긴다.
            if (!done)
                cout << "회원이 존재하지 않습니다." << endl;
            break;
        case MENU_LOCKER_OUTPUT:
            /* 락커룸 사용 유무
             * 모든 락커룸의 정보를 순서대로 출력한다.
             *
             * 락커룸 사용 유무 로직은 다음과 같다.
             * 1. 락커룸 배열을 선언한다. 락커룸 배열에는 해당 락커룸을 사용하는 회원 배열의 index가 저장될 것이다.
             * 2. 락커룸 배열의 모든 값을 -1로 초기화한다.
             * 3. 회원 배열을 순차적으로 탐색하며 락커룸을 사용하는지 확인한다.
             * 만약 회원이 락커룸을 사용한다면, 락커룸 배열에 해당 회원의 index를 입력한다.
             * 4, 락커룸의 정보를 순서대로 출력한다.
             */
            cout << "==========락커룸 사용 유무==========" << endl;

            // 락커룸 배열 선언. 배열에는 해당 번호의 락커룸을 소유한 회원이 위치하고 있는 index가 들어간다.
            int locker_arr[LOCKER_SIZE];
            // -1로 초기화
            for (int i = 0; i < LOCKER_SIZE; i++)
            {
                locker_arr[i] = -1;
            }

            // 회원 정보를 탐색해서 락커룸 주인들을 탐색한다.
            for (int i = 0; i < number_of_members; ++i)
            {
                if (gym_member_arr[i].locker_number != 0)
                {
                    locker_arr[gym_member_arr[i].locker_number - 1] = i;
                }
            }
            // 출력
            for (int i = 0; i < LOCKER_SIZE; i++)
            {
                cout << i + 1 << "번 락커룸:" << (locker_arr[i] != -1 ? gym_member_arr[locker_arr[i]].str_name : "") << endl;
            }

            break;
        case MENU_EXERCISE_TIME_CHECK:
            /* 총 운동 시간
             * 원하는 회원을 검색한다.
             * 해당 회원이 오늘 운동한 시간을 저장한다.
             * 해당 회원이 지금까지 운동한 시간을 출력한다.
             *
             * 총 운동 시간 로직은 다음과 같다.
             * 1. 회원 이름을 입력한다.
             * 2. 이름이 일치하는 회원을 찾는다.
             * 3. 해당 회원이 오늘 운동한 시간을 입력한다.
             * 4. 오늘 운동한 시간을 기존 운동한 시간에 더한다.
             * 5. 총 운동한 시간을 출력한다.
             */
            cout << "==========총 운동 시간==========" << endl;

            cin.ignore(1024, '\n');
            cout << "회원 이름을 입력하세요: ";
            cin.getline(str_name, NAME_SIZE);
            bool contains2;
            contains2 = false;
            int member_index;
            member_index = -1;
            // 회원 배열 순회
            for (int i = 0; i < number_of_members; ++i)
            {
                // 일치하는 회원이 나온 경우
                if (strcmp(gym_member_arr[i].str_name, str_name) == 0)
                {
                    contains2 = true;
                    member_index = i;
                    break;
                }
            }
            // 회원이 존재하지 않는 경우 해당 회원이 존재하지 않는다는 메세지를 남긴다.
            if (!contains2)
            {
                cout << "회원이 존재하지 않습니다." << endl;
                break;
            }
            cout << "오늘 운동한 시간을 입력하세요: ";
            int exercise_time;
            cin >> exercise_time;
            gym_member_arr[member_index].total_exercise_time += exercise_time;

            cout << "총 " << gym_member_arr[member_index].total_exercise_time << "시간 운동하였습니다.";
            break;
        default:
            cout << "메뉴를 잘못 선택했습니다. " << endl;
            break;
        }
    }
}