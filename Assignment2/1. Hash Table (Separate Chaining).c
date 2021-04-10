#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Node_ {
	int data;
	struct Node_* next;
}Node;

void init(Node** table, int size) {
	for (int i = 0; i < size; i++)
		table[i] = NULL;
}
int k(int data, int m) {
	int result;
	result = data % m;
	return result;
}
Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
void insert(Node** table, int data, int size) {
	int key;
	key = k(data, size);
	Node* keyNode = createNode(data);
	if (table[key] == NULL)
		table[key] = keyNode;
	else if (table[key] != NULL) {
		Node* temp;
		temp = table[key];
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = keyNode;
	}
}
void print(Node** table, int size) {
	int* a = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
		a[i] = 0;
	Node* temp;
	int cnt;
	cnt = 0;
	for (int i = 0; i < size; i++) {
		temp = table[i];
		while (temp != NULL) {
			printf("%d ", temp->data);
			cnt++;
			temp = temp->next;
			a[i] = cnt;
		}
		printf("\n");
		cnt = 0;
	}
	int sum = 0;
	int max = a[0];
	int min = a[0];
	printf("\n");
	for (int i = 0; i < size; i++) {
		sum += a[i];
		if (max < a[i])
			max = a[i];
		if (min > a[i])
			min = a[i];
	}
	
	printf("\nAverage chain length is %d", sum / size);
	printf("\nShortest chain length is %d", min);
	printf("\nLongest chain length is %d", max);
}

int main() {
	srand(time(NULL));
	int* input = (int*)malloc(sizeof(int) * 50);
	input[0] = rand() % 1000;
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < i; j++) {
			input[i] = rand() % 1000;
			if (input[i] == input[j])
				i--;
		}
	}

	Node** hTable7;
	Node** hTable13;
	Node** hTable17;
	hTable7 = (Node**)malloc(sizeof(Node*) * 7);
	hTable13 = (Node**)malloc(sizeof(Node*) * 13);
	hTable17 = (Node**)malloc(sizeof(Node*) * 17);
	init(hTable7, 7);
	init(hTable13, 13);
	init(hTable17, 17);
	for (int i = 0; i < 50; i++) {
		insert(hTable7, input[i], 7);
		insert(hTable13, input[i], 13);
		insert(hTable17, input[i], 17);
	}
	printf("First hash function h(k) = k mod 7\n\n");
	print(hTable7, 7);
	printf("\n\nSecond hash function h(k) = k mod 13\n\n");
	print(hTable13, 13);
	printf("\n\nThird hash function h(k) = k mod 17\n\n");
	print(hTable17, 17);

}