
#include <iostream>
#include <sstream>
#include "Logger.h"
#include "FileManage.h"

using namespace std;
int main()
{
    /// <summary>
    /// log ���� ����
    /// 3. ���α׷��� �α� ���� ��ġ�� �α��� prefix ����
    /// ���α׷��� �����ϴ� main()�Լ��� ù��°���ο� LOGsetInfo()ȣ����.
    /// LOGsetInfo(�α� ������ ���丮, �α����ϸ�); �Լ��� ������.
    /// </summary>
    /// <returns></returns>
    LOGsetInfo(".", "test");
    Logger myLog = Logger::log_create(  __FILE__, 
                                        __func__, 
                                        Mode::All, 
                                        LogType::Debug | 
                                        LogType::Error | 
                                        LogType::Event | 
                                        LogType::Warning);
    myLog.log_print(LogType::Event, "test debug start!", __LINE__);
    
    string str = "Hello World!\n";
    std::cout << str;
    myLog.log_print(LogType::Debug, "str = " + str, __LINE__);
    int* pinteger;
    int integer = 0;
    pinteger = &integer;
    ostringstream oss;
    oss << pinteger;
    string address_pinteger = oss.str();
    myLog.log_print(LogType::Error, "dangling pointer Error! pointer : " + address_pinteger, __LINE__);
    delete pinteger;
}
// ���α׷� ����: <Ctrl+F5> �Ǵ� [�����] > [��������� �ʰ� ����] �޴�
// ���α׷� �����: <F5> Ű �Ǵ� [�����] > [����� ����] �޴�

// ������ ���� ��: 
//   1. [�ַ�� Ž����] â�� ����Ͽ� ������ �߰�/�����մϴ�.
//   2. [�� Ž����] â�� ����Ͽ� �ҽ� ��� �����մϴ�.
//   3. [���] â�� ����Ͽ� ���� ��� �� ��Ÿ �޽����� Ȯ���մϴ�.
//   4. [���� ���] â�� ����Ͽ� ������ ���ϴ�.
//   5. [������Ʈ] > [�� �׸� �߰�]�� �̵��Ͽ� �� �ڵ� ������ ����ų�, [������Ʈ] > [���� �׸� �߰�]�� �̵��Ͽ� ���� �ڵ� ������ ������Ʈ�� �߰��մϴ�.
//   6. ���߿� �� ������Ʈ�� �ٽ� ������ [����] > [����] > [������Ʈ]�� �̵��ϰ� .sln ������ �����մϴ�.
