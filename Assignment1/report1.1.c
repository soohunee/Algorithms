#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printarray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

void bubble_sort(int* arr, int n)
{
    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            cnt++;
            if (arr[j] > arr[j + 1]) {
                int temp;
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\n# of comparisons : %d\n", cnt);
}

int main() {
    srand(time(NULL));
    int n = 100;
    int* arr = (int*)(malloc(sizeof(int) * n));
    arr[0] = rand() % 1000;


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            arr[i] = rand() % 1000;
            if (arr[i] == arr[j])
                i--;


        }
    }


    int* arr2 = (int*)(malloc(sizeof(int) * n));
    for (int i = 0; i < n; i++) {
        arr2[i] = i + 1;
    }


    int* arr3 = (int*)(malloc(sizeof(int) * n));
    for (int i = 0; i < n; i++) {
        arr3[i] = n - i;
    }


    printf("1) filled by rand()\n");
    printf("before sorting : \n");
    printarray(arr, n);
    printf("after sorting : ");
    bubble_sort(arr, n);
    printarray(arr, n);


    printf("\n\n\n\n2) already sorted\n");
    printf("before sorting : \n");
    printarray(arr2, n);
    printf("after sorting : ");
    bubble_sort(arr2, n);
    printarray(arr2, n);


    printf("\n\n\n\n3) reversely sorted\n");
    printf("before sorting : \n");
    printarray(arr3, n);
    printf("after sorting : ");
    bubble_sort(arr3, n);
    printarray(arr3, n);
}

