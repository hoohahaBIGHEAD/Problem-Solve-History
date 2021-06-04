#include <stdio.h>
#include <string.h>
//#include <libgen.h>
#include "log_util.h"

int my_test_test_func(int value)
{
    LOG_TRACE("TRACE LOG...1");
    LOG_DEBUG("TEST");
    printf("%d\n", value);
    LOG_TRACE("TRACE LOG...2");
    LOG_DEBUG("%s", "sample test");
    return 111;
}

//int main(int argc, char** argv)
int main()
{
    int ret;
    int value = 0;
    //LOGsetLevel(30);
    /*
    * �α��� ��ġ�� ���� ���丮�� �����ϰ� �α� ���ϸ��� �������ϸ�-yyyymmdd.log
    * �� �����մϴ�.
    */
    //LOGsetInfo(".", basename(argv[0]));
    //LOGsetInfo(".", argv[0]);
    LOGsetInfo(".", "case");

    LOG_TRACE("TRACE LOG...1");
    LOG_DEBUG("TEST");
    LOG_TRACE("TRACE LOG...2");
    LOG_CALL(ret = my_test_test_func(value));
    LOG_DEBUG("%s", "sample test");
    LOG_TRACE("TRACE LOG...3");
    LOG_ERROR("%s �����Դϴ�.", "sample test");
    LOG_TRACE("TRACE LOG...4");

    return 0;
}