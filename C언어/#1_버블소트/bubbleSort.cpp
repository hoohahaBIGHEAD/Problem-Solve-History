#include<stdio.h>   //printf 함수 포함

void line_up(int a[], int length);

int main() {
    int a[] = { 1,2,-4,3,2,123,4 };     //여기에 배열을 넣어주세요.
    int length; //배열의 길이를 넣어주기 위한 변수
    length = sizeof(a) / sizeof(a[0]);  //배열의 길이를 구합니다.
    line_up(a, length); //정렬 함수 실행
    return 0;
}

void line_up(int a[], int length) {
    //버블 솔트 사용할 것
    //max :: 비교 후 큰 값을 저장할 곳
    //i, j :: 반복문을 시행하기 위한 인덱스 변수
    int max, i, j;

    //length-1회 시행
    for (i = 0; i < length - 1; i++) {
        //a[length-i]까지 크기를 비교하여 max 값을 a[length-i]에 저장한다
        for (j = 0; j < length - i - 1; j++){
            //만약 앞의 원소가 크다면
            if (a[j] > a[j + 1])
            {
                //앞의 원소를 max에 저장해라
                max = a[j];
                //뒤의 원소를 앞에 저장해라
                a[j] = a[j + 1];
                //뒤의 원소에 max를 저장해라
                a[j + 1] = max;
            }
        }
    }
    printf("정렬된 숫자는 : \n");
    //배열 출력
    for (i = 0; i < length; i++)
    {
        printf("% d", a[i]);
    }
    printf("\n입니다. \n");
}
