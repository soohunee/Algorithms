#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void print_matrix(int** mtr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mtr[i][j]);
        }
        printf("\n\n");
    }
}

void multiply_matrix_standard(int** mtr1, int** mtr2, int** result, int n) {
    int cnt_add = 0;
    int cnt_mult = 0;
    int temp = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += mtr1[i][k] * mtr2[k][j];
                temp += 1;
                cnt_mult +=1;
            }
            cnt_add += temp - 1;
            temp = 0;
        }

    }
    printf("\n\n# of computations (addition) : %d\n# of computations (multiplication) : %d\n", cnt_add, cnt_mult);
}

int** init_mtr(int n) {
    int** mtr = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        mtr[i] = (int*)malloc(sizeof(int) * n);
    }
    return mtr;
}

int** add_mtr(int** mtr1, int** mtr2, int n) {
    int** result = init_mtr(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = mtr1[i][j] + mtr2[i][j];
        }
    }
    return result;
}

int** mult_mtr_rec(int** a, int** b, int n) {


    int n2 = n / 2;
    int** mult_result = init_mtr(n);
    int** a11 = init_mtr(n2);
    int** a12 = init_mtr(n2);
    int** a21 = init_mtr(n2);
    int** a22 = init_mtr(n2);
    int** b11 = init_mtr(n2);
    int** b12 = init_mtr(n2);
    int** b21 = init_mtr(n2);
    int** b22 = init_mtr(n2);
    int** result11 = init_mtr(n2);
    int** result12 = init_mtr(n2);
    int** result21 = init_mtr(n2);
    int** result22 = init_mtr(n2);
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + n2];
            a21[i][j] = a[i + n2][j];
            a22[i][j] = a[i + n2][j + n2];
            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + n2];
            b21[i][j] = b[i + n2][j];
            b22[i][j] = b[i + n2][j + n2];
        }
    }
    if (n == 1) {
        mult_result[0][0] = a[0][0] * b[0][0];

    }
    else {
        result11 = add_mtr(mult_mtr_rec(a11, b11, n2), mult_mtr_rec(a12, b21, n2), n2);

        result12 = add_mtr(mult_mtr_rec(a11, b12, n2), mult_mtr_rec(a12, b22, n2), n2);


        result21 = add_mtr(mult_mtr_rec(a21, b11, n2), mult_mtr_rec(a22, b21, n2), n2);


        result22 = add_mtr(mult_mtr_rec(a21, b12, n2), mult_mtr_rec(a22, b22, n2), n2);
    }
    if (n2 >= 2) {
        printf("partial maxtix is constructed\n");
        print_matrix(result11, n2);
        printf("天天天天天天天天天天天天天天天天\n");
        print_matrix(result12, n2);
        printf("天天天天天天天天天天天天天天天天\n");
        print_matrix(result21, n2);
        printf("天天天天天天天天天天天天天天天天\n");
        print_matrix(result22, n2);
        printf("天天天天天天天天天天天天天天天天\n");
    }
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < n2; j++) {
            mult_result[i][j] = result11[i][j];
            mult_result[i][j + n2] = result12[i][j];
            mult_result[i + n2][j] = result21[i][j];
            mult_result[i + n2][j + n2] = result22[i][j];
        }
    }
    



    return mult_result;
}

int main() {

    int** A4 = init_mtr(4);
    int** B4 = init_mtr(4);
    int** C4 = init_mtr(4);
    int** A8 = init_mtr(8);
    int** B8 = init_mtr(8);
    int** C8 = init_mtr(8);


    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            A4[i][j] = rand() % 1000;
            B4[i][j] = rand() % 1000;
            for (int k = 0; k <= i; k++) {
                if (k < i) {
                    for (int z = 0; z < 4; z++) {
                        if (A4[i][j] == A4[k][z])
                            j--;
                    }
                }
                if (k == i) {
                    for (int z = 0; z < j; z++) {
                        if (A4[i][j] == A4[k][z])
                            j--;
                    }
                }

            }
        }


    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            A8[i][j] = rand() % 1000;
            B8[i][j] = rand() % 1000;
            for (int k = 0; k <= i; k++) {
                if (k < i) {
                    for (int z = 0; z < 8; z++) {
                        if (A8[i][j] == A8[k][z])
                            j--;
                    }
                }
                if (k == i) {
                    for (int z = 0; z < j; z++) {
                        if (A8[i][j] == A8[k][z])
                            j--;
                    }
                }

            }
        }

    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C4[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            C8[i][j] = 0;
        }
    }

    printf("4x4\nMatrix A : \n");
    print_matrix(A4, 4);
    printf("Matrix B : \n");
    print_matrix(B4, 4);
    printf("Matrix C (in standard algorithm) : ");
    multiply_matrix_standard(A4, B4, C4, 4);
    print_matrix(C4, 4);


    printf("Matrix C (in recursion) : \n");
    C4 = mult_mtr_rec(A4, B4, 4);
    print_matrix(C4, 4);


    printf("8x8\nMatrix A : \n");
    print_matrix(A8, 8);
    printf("Matrix B : \n");
    print_matrix(B8, 8);
    printf("Matrix C (in standard algorithm) : ");
    multiply_matrix_standard(A8, B8, C8, 8);
    print_matrix(C8, 8);


    printf("Matrix C (in recursion) : \n");
    C8 = mult_mtr_rec(A8, B8, 8);
    print_matrix(C8, 8);
}

