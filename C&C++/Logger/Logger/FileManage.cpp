#include <stdio.h>
#include <string>
#include <time.h>


static char log_file_prefix[64];
static char log_folder[1024] = ".";
static FILE* fp_log_file;



int LOGsetInfo(const char* dir, const char* prefix)
{
    if (dir == NULL || dir[0] == 0x00) {
        fprintf(stderr, "log folder set error.\n");
        return -1;
    }
    if (prefix == NULL || prefix[0] == 0x00) {
        fprintf(stderr, "log file prefix set error.\n");
        return -1;
    }

    if (strcmp(dir, log_folder) == 0 && strcmp(prefix, log_file_prefix) == 0) {
        return 0;
    }

    strncpy_s(log_file_prefix, prefix, 64);
    strncpy_s(log_folder, dir, 1024);

    if (fp_log_file != NULL) {
        fclose(fp_log_file);
        fp_log_file = NULL;
    }

    return 0;
}

/*
* LOGcreateFile 날짜가 변경되면 자동으로 새로운 파일이 생성됨
*/
static int LOGcreateFile(struct tm* tm1, const char* src_file)
{
    char filename[1024];
    char* ext;

    if (log_folder[0] == 0x00) {
        strcpy_s(log_folder, ".");
    }
    if (log_file_prefix[0] == 0x00) {
        strncpy_s(log_file_prefix, src_file, sizeof(src_file));
        if ((ext = strchr(log_file_prefix, '.')) != NULL) {
            *ext = 0x00;
        }
    }
    snprintf(filename, 1024, "%s/%s-%04d%02d%02d.log",
        log_folder, log_file_prefix, 1900 + tm1->tm_year, tm1->tm_mon + 1, tm1->tm_mday);

    if (fp_log_file != NULL) {
        fclose(fp_log_file);
        fp_log_file = NULL;
    }
    int isOpen = -1;
    isOpen = (fopen_s(&fp_log_file, filename, "a"));
    if (isOpen == NULL) {
        return -1;
    }
    setvbuf(fp_log_file, NULL, _IOLBF, 0);
    return 0;
}


/*
* LOGlogging(...) 로그 파일을 생성함.
* log_type, 로그생성일시분초microseconds, process id, 소스파일, 함수명, 라인수, 오류 내용
* 의 format으로 로그를 생성함.
*/

int LOGlogging(const char* src_file, const char* cmessage, const char* clog_data)
{
    //va_list ap;

    int  sz = 0;
    struct tm tm;
    struct tm* ptm;
    ptm = &tm;

    time_t current_time;
    current_time = time(NULL);
    static int   day = -1;
    char   src_info[128];

    errno_t error;
    error = localtime_s(&tm, &current_time);
    if (error != 0)
        printf("error num : %d occured.", error);
    
    // 날짜가 변경되었으면 또는 최초 실행시에 로그 파일을 새로운 날짜로 생성하라
    if (day != ptm->tm_mday) {
        if (LOGcreateFile(ptm, src_file) == 0) {
            day = ptm->tm_mday;
            //return -1;
        }
    }

    sz += fprintf(fp_log_file, "%-130.1024s : %10.1024s\n", cmessage, clog_data);
    fclose(fp_log_file);
    return sz;
}
