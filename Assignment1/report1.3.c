#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node_ {
    int data;
    struct Node_* next;
}Node;

void insert(Node* head, int number) {


    Node* new_Node;
    new_Node = (Node*)malloc(sizeof(Node));
    new_Node->data = number;
    new_Node->next = head->next;
    head->next = new_Node;

}

void delete(Node* head) {
    Node* current = head;
    if (current->next == NULL || current->next->next == NULL)
        return;
    else {
        while (current->next->next->next != NULL) {
            current = current->next;
        }
        current->next = current->next->next;
    }
}

void print(Node* head) {
    int cnt = 0;
    Node* count = head;
    while (count->next != NULL) {
        count = count->next;
        cnt++;
    }
    Node* current = head->next;
    //갯수가 3의 배수일때
    if (cnt % 3 == 0) {
        for (int i = 1; i <= cnt / 3; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        for (int i = cnt / 3 + 1; i <= (2 * cnt) / 3; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        for (int i = (2 * cnt) / 3 + 1; i <= cnt; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
    }


    //갯수가 3의배수+1 또는 +2 일 때
    if (cnt % 3 == 1) {
        for (int i = 1; i <= (cnt + 2) / 3; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        for (int i = (cnt + 2) / 3 + 1; i <= 2 * ((cnt + 2) / 3); i++) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        for (int i = 2 * ((cnt + 2) / 3) + 1; i <= cnt; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
    }
    //cnt가 3의배수+2일때
    if (cnt % 3 == 2) {
        for (int i = 1; i <= (cnt + 1) / 3; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        for (int i = (cnt + 1) / 3 + 1; i <= 2 * ((cnt + 1) / 3); i++) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
        for (int i = 2 * ((cnt + 1) / 3) + 1; i <= cnt; i++) {
            printf("%d ", current->data);
            current = current->next;
        }
    }




}

int main() {
    Node* head = NULL;
    head = (Node*)malloc(sizeof(Node));
    head->next = NULL;


    int n = 60;
    int* arr = (int*)(malloc(sizeof(int) * n));
    srand(time(NULL));
    arr[0] = rand() % 1000;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            arr[i] = rand() % 1000;
            if (arr[i] == arr[j])
                i--;
        }
    }

    for (int i = 0; i < n; i++) {
        insert(head, arr[i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("Iteration %d\n", i + 1);
        delete(head);
        print(head);
        printf("\n\n");
    }




}

