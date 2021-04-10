#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define m 37

float probeSum = 0;
void insertLP(int* a, int data){
    int i = 0;
    int key = (data % m + i)%m;
    if (a[key] == NULL)
        a[key] = data;
    else if (a[key] != NULL) {
        i++;
        while (a[key] != NULL) {
            key = ((data%m) + i) % m;
            if (a[key] == NULL) {
                a[key] = data;
                break;
            }
            else
                i++;
        }
    }
    probeSum += i+1;
}
void insertQP(int* a, int data) {
    int i = 0;
    int key = ((data % m) + i + 3 * i * i) % m;
    if (a[key] == NULL)
        a[key] = data;
    else if (a[key] != NULL) {
        i++;
        while (a[key] != NULL) {
            key = ((data%m) + i + 3*i*i) % m;
            if (a[key] == NULL) {
                a[key] = data;
                break;
            }
            else
                i++;
        }
    }
    probeSum += i+1;
}
void insertDH(int* a, int data) {
    int i = 0;
    int key = ((data % m) + i * (1 + (data % (m - 1)))) % m;
    if (a[key] == NULL)
        a[key] = data;
    else if (a[key] != NULL) {
        i++;
        while (a[key] != NULL) {
            key = ((data%m) + i*(1+(data % (m-1)))) % m;
            if (a[key] == NULL) {
                a[key] = data;
                break;
            }
            else
                i++;
        }
    }
    probeSum += i+1;
}

void print(int* a) {
    int tempsum = 0;
    int cluster = 0;
    for (int i = 0; i < m; i++) {
        if (a[i] == NULL) {
            printf("%d : NULL\n", i + 1);
            if (cluster > tempsum) {
                tempsum = cluster;
                cluster = 0;
            }
            else if (cluster < tempsum)
                cluster = 0;
        }
        else {
            printf("%d : %d\n", i + 1, a[i]);
            cluster++;
        }
    }
    if (cluster > tempsum)
        tempsum = cluster;
    printf("\nPrimary cluster : %d", tempsum);
    printf("\n");
}

int main() {
    int* lp = (int*)malloc(sizeof(int) * m);
    int* qp = (int*)malloc(sizeof(int) * m);
    int* dh = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        lp[i] = NULL;
        qp[i] = NULL;
        dh[i] = NULL;
    }
    srand(time(NULL));
    int* input = (int*)malloc(sizeof(int) * 90);
    input[0] = rand() % 1000;
    for (int i = 0; i < 90; i++) {
        for (int j = 0; j < i; j++) {
            input[i] = rand() % 1000;
            if (input[i] == input[j])
                i--;
        }
    }
    probeSum = 0;
    for (int i = 0; i < 30; i++) {
        insertLP(lp, input[i]);
    }
    printf("Linear Probing\n\n");
    print(lp);
    printf("Average number of probes : %.2f\n", probeSum/30);
    probeSum = 0;
    for (int i = 30; i < 60; i++) {
        insertQP(qp, input[i]);
    }
    printf("\n\nQuadratic Probing\n\n");
    print(qp);
    printf("Average number of probes : %.2f\n", probeSum / 30);
    probeSum = 0;
    for (int i = 60; i < 90; i++) {
        insertQP(dh, input[i]);
    }
    printf("\n\nDouble Hashing\n\n");
    print(dh);
    printf("Average number of probes : %.2f", probeSum / 30);
 
}