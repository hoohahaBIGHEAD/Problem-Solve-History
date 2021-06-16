/*


#include <stdio.h>
#include <string.h>
int main()
{
    int T = 0;
    scanf("%d", &T);
    int i = 0;
    printf("%d", T);
    char string[100][100];
    for (i = 0; i < T; i++) {
        scanf("%[^\n]s", string[i]);   //%[^\n] 공백 제외 입력
    }
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (string[i][j] >= 'A' && string[i][j] <= 'Z')
            {
                string[i][j] -= 32;
            }
        }
    }

    char temp[100];
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            char* ptr = strtok(&string[i][j], " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
            ptr[i] += 32;
            string[i][j] = ptr[i];
        }
    }


    for (i = 0; i < T; i++) {
        printf("%s\n", string[i]);
    }


    return 0;
}

*/

#include <stdio.h>


int main() {
    int N;
    int K;
    scanf("%d%d", &N, &K);
    printf("%d, %d\n", N, K);

    int array[100][100] = { 0 };
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &array[i][j]);
        }
    }

    int count = 0;
    int countmin = 101;
    for (int i = 0; i < N - K + 1; i++)
    {
        for (int j = 0; j < K; j++)
        {

            for (int k = 0; k < K; k++)
            {
                if (array[i + j][k] == 1) {
                    count++;
                }
            }
        }
        if (countmin >= count)
        {
            countmin = count;
        }
        count = 0;

    }
    printf("%d", countmin);
    return 0;
}