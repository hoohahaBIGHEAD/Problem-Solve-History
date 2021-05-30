#include<iostream>
#include <cstring>
using namespace std;

#define NAME_SIZE 32        // �ִ� �̸� ����
#define MEMBER_MAX 10       // �ִ� ȸ�� ��
#define LOCKER_SIZE 4       // ��Ŀ�� ũ��
#define ADDRESS_SIZE 128    // �ִ� �ּ� ����
#define PHONE_SIZE 15       // �ִ� ��ȭ��ȣ ����

struct gym_member
{
    char str_name[NAME_SIZE]; // �̸�
    char str_address[ADDRESS_SIZE]; // �ּ�
    char str_phone[PHONE_SIZE]; // ��ȭ��ȣ
    int height; // Ű
    int weight; // ������
    float bmi; // BMI
    int locker_number; // ���� �����ϰ� �ִ� ��Ŀ�� ��ȣ. �������� �ʴ� ��� 0
    int total_exercise_time; // ������ ��ð� ����
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
    // �ʱ� ����
    gym_member gym_member_arr[MEMBER_MAX] = {}; // ȸ�� ���� �迭
    int number_of_members = 0; // ���� ȸ�� ��
    char str_name[NAME_SIZE] = {};   // ȸ�� �˻��� �� �� ���

    cout << " ---------�ｺ�� ȸ������---------" << endl;
    cout << " 1. ȸ�� ���" << endl;
    cout << " 2. ȸ�� ����" << endl;
    cout << " 3. ȸ�� ž��" << endl;
    cout << " 4. ��Ŀ�� ��� ����" << endl;
    cout << " 5. �� � �ð� üũ" << endl;
    cout << " 6. ����" << endl;

    // ���� ����� �Էµ� ������ �޴� �Է��� �ݺ��Ѵ�.
    while (true)
    {
        cout << "\n�޴��� �����ϼ���: ";

        // �Է� �ޱ�
        int iMenu;
        cin >> iMenu;

        // �Է��� ���������� ���� ���, �ٽ� �Է��� �޴´�.
        if (cin.fail())
        {
            cin.clear();

            continue;
        }

        // �ݺ��� Ż��
        if (iMenu == MENU_EXIT)
            break;

        switch (iMenu)
        {
            /* ȸ�� ���
             * ȸ�� ������ �Է��Ͽ� ȸ���� ����Ѵ�
             * ȸ�� ���� �Ѱ迡 ������ ��� ȸ�������� ���� �ʴ´�.
             * �̸�, �ּ�, ��ȭ��ȣ, Ű, ������, BMI, ��Ŀ�� ��ȣ ������ ȸ�� ������ �Է¹޴´�.
             * ��Ŀ�� ��ȣ �Է��� ��� ��Ŀ�� ��ȣ�� ��ȿ�� ������ �ִ� ��쿡�� �����Ѵ�.
             * ����ϰ��� �ϴ� ��Ŀ�� ��ȣ�� �̹� �ٸ� ȸ���� ��ϵǾ� �ִ� ��� ���� ȸ���� ��Ŀ�� ��ȣ�� ��Ż�ϰ� ���� ������ ȸ���� �ش� ��Ŀ���� ������ �ȴ�.
             */

        case MENU_MEMBER_INSERT:
            cout << " ==========ȸ������ �Է�=============" << endl;
            // ���� ȸ���� ���� �ִ� ȸ�� ���� ������ ��� ȸ������ �Է��� ���� �ʴ´�.
            if (number_of_members == MEMBER_MAX)
            {
                cout << "���� �ִ� ȸ�� ���� �����߽��ϴ�. ȸ���� �߰��Ϸ��� ������ ȸ���� ������ �ּ���." << endl;
                break;
            }

            // ȸ�� ������ ���ʴ�� �Է¹޴´�.

            cout << "�̸�: ";
            cin >> gym_member_arr[number_of_members].str_name;

            cin.ignore(1024, '\n');

            cout << "�ּ�: ";
            cin.getline(gym_member_arr[number_of_members].str_address, ADDRESS_SIZE);

            cout << "��ȭ��ȣ: ";
            cin.getline(gym_member_arr[number_of_members].str_phone, PHONE_SIZE);

            cout << "Ű: ";
            cin >> gym_member_arr[number_of_members].height;
            cout << "������: ";
            cin >> gym_member_arr[number_of_members].weight;
            gym_member_arr[number_of_members].bmi = gym_member_arr[number_of_members].weight / (gym_member_arr[number_of_members].height * gym_member_arr[number_of_members].height / 10000);
            cout << "��Ŀ�� ��ȣ: ";
            int num_locker;
            cin >> num_locker;
            // ��Ŀ�� ��ȣ�� ��ȿ�� ��쿡�� �����Ѵ�.
            if (num_locker >= 1 && num_locker <= LOCKER_SIZE)
            {
                // ������ ���� ��ȣ�� ������ �ִ� ��Ŀ ������ ������ ���ش�.
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

            cout << "ȸ�� �߰� �Ϸ� " << endl;

            break;
        case MENU_MEMBER_DELETE:
            /* ȸ�� ����
             * ȸ���� �����Ѵ�.
             * ������ ȸ���� �̸��� �Է��Ѵ�.
             * ȸ���� ã���� �ش� ȸ���� �����ȴ�.
             *
             * ȸ�� ���� ������ ������ ����.
             * 1. �����ϰ��� �ϴ� ȸ���� �̸��� �Է��Ѵ�.
             * ���� �ش��ϴ� ȸ���� �������� ������, ȸ���� �������� �ʴ´ٴ� �޼����� ����� �����Ѵ�.
             * 2. ȸ�� �迭���� �ش��ϴ� �̸��� ����� �� �� ã�´�.
             * 3. �ش� ȸ�� ���� ȸ������ �迭���� �� ���ʾ� ������ ����ش�.
             * 4. "ȸ���� �����Ǿ����ϴ�" �޼����� ����Ѵ�.
             */
            cout << "==========ȸ�� ����==========" << endl;

            cin.ignore(1024, '\n');
            cout << "������ �̸��� �Է�: ";
            cin.getline(str_name, NAME_SIZE);

            bool contains0;
            contains0 = false;
            // ȸ�� �迭 ��ȸ
            for (int i = 0; i < number_of_members; ++i)
            {
                // ��ġ�ϴ� ȸ���� ���� ���
                if (strcmp(gym_member_arr[i].str_name, str_name) == 0)
                {
                    contains0 = true;
                    // �ڿ� ������ ȸ������ ��ȣ�� �� ĭ�� ������ ����ش�.
                    for (int j = i; j < number_of_members - 1; ++j)
                    {
                        gym_member_arr[i] = gym_member_arr[i + 1];
                    }
                    --number_of_members;

                    cout << "ȸ���� �����Ǿ����ϴ�" << endl;
                    break;
                }
            }
            // ȸ���� �������� �ʴ� ��� �ش� ȸ���� �������� �ʴ´ٴ� �޼����� �����.
            if (!contains0)
                cout << "ȸ���� �������� �ʽ��ϴ�." << endl;

            break;
        case MENU_MEMBER_SEARCH:
            /* ȸ�� �˻�
             * ȸ���� �˻��Ѵ�.
             * �˻��� ȸ���� �̸��� �Է��Ѵ�.
             * ȸ���� ã���� ȸ���� ������ ����Ѵ�.
             */
            cout << "==========ȸ�� �˻�==========" << endl;

            cin.ignore(1024, '\n');
            cout << "�˻��� ȸ���� �̸��� �Է�: ";
            cin.getline(str_name, NAME_SIZE);

            bool done;
            done = false;
            for (int i = 0; i < number_of_members; ++i)
            {
                // ��ġ�ϴ� ȸ���� ���� ���
                if (strcmp(gym_member_arr[i].str_name, str_name) == 0)
                {
                    cout << "�̸�: " << gym_member_arr[i].str_name << endl;
                    cout << "�ּ�: " << gym_member_arr[i].str_address << endl;
                    cout << "��ȭ��ȣ: " << gym_member_arr[i].str_phone << endl;
                    cout << "Ű: " << gym_member_arr[i].height << endl;
                    cout << "������: " << gym_member_arr[i].weight << endl;
                    cout << "BMI: " << gym_member_arr[i].bmi << endl;
                    cout << "��Ŀ�� ��ȣ: " << gym_member_arr[i].locker_number << endl << endl;
                    done = true;
                    //break;
                }
            }
            // ȸ���� �������� �ʴ� ��� �ش� ȸ���� �������� �ʴ´ٴ� �޼����� �����.
            if (!done)
                cout << "ȸ���� �������� �ʽ��ϴ�." << endl;
            break;
        case MENU_LOCKER_OUTPUT:
            /* ��Ŀ�� ��� ����
             * ��� ��Ŀ���� ������ ������� ����Ѵ�.
             *
             * ��Ŀ�� ��� ���� ������ ������ ����.
             * 1. ��Ŀ�� �迭�� �����Ѵ�. ��Ŀ�� �迭���� �ش� ��Ŀ���� ����ϴ� ȸ�� �迭�� index�� ����� ���̴�.
             * 2. ��Ŀ�� �迭�� ��� ���� -1�� �ʱ�ȭ�Ѵ�.
             * 3. ȸ�� �迭�� ���������� Ž���ϸ� ��Ŀ���� ����ϴ��� Ȯ���Ѵ�.
             * ���� ȸ���� ��Ŀ���� ����Ѵٸ�, ��Ŀ�� �迭�� �ش� ȸ���� index�� �Է��Ѵ�.
             * 4, ��Ŀ���� ������ ������� ����Ѵ�.
             */
            cout << "==========��Ŀ�� ��� ����==========" << endl;

            // ��Ŀ�� �迭 ����. �迭���� �ش� ��ȣ�� ��Ŀ���� ������ ȸ���� ��ġ�ϰ� �ִ� index�� ����.
            int locker_arr[LOCKER_SIZE];
            // -1�� �ʱ�ȭ
            for (int i = 0; i < LOCKER_SIZE; i++)
            {
                locker_arr[i] = -1;
            }

            // ȸ�� ������ Ž���ؼ� ��Ŀ�� ���ε��� Ž���Ѵ�.
            for (int i = 0; i < number_of_members; ++i)
            {
                if (gym_member_arr[i].locker_number != 0)
                {
                    locker_arr[gym_member_arr[i].locker_number - 1] = i;
                }
            }
            // ���
            for (int i = 0; i < LOCKER_SIZE; i++)
            {
                cout << i + 1 << "�� ��Ŀ��:" << (locker_arr[i] != -1 ? gym_member_arr[locker_arr[i]].str_name : "") << endl;
            }

            break;
        case MENU_EXERCISE_TIME_CHECK:
            /* �� � �ð�
             * ���ϴ� ȸ���� �˻��Ѵ�.
             * �ش� ȸ���� ���� ��� �ð��� �����Ѵ�.
             * �ش� ȸ���� ���ݱ��� ��� �ð��� ����Ѵ�.
             *
             * �� � �ð� ������ ������ ����.
             * 1. ȸ�� �̸��� �Է��Ѵ�.
             * 2. �̸��� ��ġ�ϴ� ȸ���� ã�´�.
             * 3. �ش� ȸ���� ���� ��� �ð��� �Է��Ѵ�.
             * 4. ���� ��� �ð��� ���� ��� �ð��� ���Ѵ�.
             * 5. �� ��� �ð��� ����Ѵ�.
             */
            cout << "==========�� � �ð�==========" << endl;

            cin.ignore(1024, '\n');
            cout << "ȸ�� �̸��� �Է��ϼ���: ";
            cin.getline(str_name, NAME_SIZE);
            bool contains2;
            contains2 = false;
            int member_index;
            member_index = -1;
            // ȸ�� �迭 ��ȸ
            for (int i = 0; i < number_of_members; ++i)
            {
                // ��ġ�ϴ� ȸ���� ���� ���
                if (strcmp(gym_member_arr[i].str_name, str_name) == 0)
                {
                    contains2 = true;
                    member_index = i;
                    break;
                }
            }
            // ȸ���� �������� �ʴ� ��� �ش� ȸ���� �������� �ʴ´ٴ� �޼����� �����.
            if (!contains2)
            {
                cout << "ȸ���� �������� �ʽ��ϴ�." << endl;
                break;
            }
            cout << "���� ��� �ð��� �Է��ϼ���: ";
            int exercise_time;
            cin >> exercise_time;
            gym_member_arr[member_index].total_exercise_time += exercise_time;

            cout << "�� " << gym_member_arr[member_index].total_exercise_time << "�ð� ��Ͽ����ϴ�.";
            break;
        default:
            cout << "�޴��� �߸� �����߽��ϴ�. " << endl;
            break;
        }
    }
}