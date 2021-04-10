#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cnt;
void merge(int* arr, int l, int m, int r) {

    int first = m - l + 1;
    int second = r - m;
    int F[100];
    int S[100];


    for (int i = 0; i < first; i++) {
        F[i] = arr[l + i];
    }
    for (int i = 0; i < second; i++) {
        S[i] = arr[m + i + 1];
    }
    int a = 0, b = 0;
    int k = l;
    while (a < first && b < second) {
        if (F[a] > S[b]) {
            arr[k] = F[a];
            a++;
            k++;
        }
        else {
            arr[k] = S[b];
            b++;
            k++;
        }
        cnt++;
    }
    while (a < first) {
        arr[k] = F[a];
        a++;
        k++;
    }
    while (b < second) {
        arr[k] = S[b];
        b++;
        k++;
    }
}

void merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;


        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);


        merge(arr, l, m, r);
    }


}


void printarray(int* arr, int n) {
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

int main() {
    srand(time(NULL));
    int n = 100;
    int* arr = (int*)(malloc(sizeof(int) * n));



    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                i--;
            }
                


        }
    }


    int* arr2 = (int*)(malloc(sizeof(int) * n));
    for (int i = 0; i < n; i++) {
        arr2[i] = n-i;
    }


    int* arr3 = (int*)(malloc(sizeof(int) * n));
    for (int i = 0; i < n; i++) {
        arr3[i] = i+1;
    }

    cnt = 0;
    printf("1) filled by rand()\n");
    printf("before sorting : ");
    printarray(arr, n);
    printf("after sorting : ");
    merge_sort(arr, 0, n - 1);
    printf("\n# of comparisons : %d", cnt);
    printarray(arr, n);
    

    cnt = 0;
    printf("\n\n\n\n2) already sorted\n");
    printf("before sorting : ");
    printarray(arr2, n);
    printf("after sorting : ");
    merge_sort(arr2, 0, n - 1);
    printf("\n# of comparisons : %d", cnt);
    printarray(arr2, n);

    cnt = 0;
    printf("\n\n\n\n3) reversely sorted\n");
    printf("before sorting : ");
    printarray(arr3, n);
    printf("after sorting : ");
    merge_sort(arr3, 0, n - 1);
    printf("\n# of comparisons : %d", cnt);
    printarray(arr3, n);
}
