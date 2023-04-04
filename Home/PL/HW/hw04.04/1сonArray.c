
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* top = NULL;  // инициализация вершины стека как пустой

/* функция для добавления элемента в стек */
void push(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}

/* функция для удаления элемента из стека */
int pop() {
    if (top == NULL) {  // проверка на пустой стек
        printf("Stack Underflow!");
        return -1;
    }
    int data = top->data; 
    struct Node* temp = top;
    top = top->next; // Спросить по поводу отсутствия эл-та
    free(temp);
    return data;
}

/* функция для просмотра последнего элемента стека */
int peek() {
    if (top == NULL) {  // проверка на пустой стек
        printf("Stack is Empty!");
        return -1;
    }
    return top->data;
}

int main() {
    printf("%d\n", peek()); 
    push(1);
    printf("%d\n", peek()); 
    push(2);
    printf("%d\n", peek()); 
    push(3);
    
    printf("%d\n", pop());  // выведет 3
    printf("%d\n", peek());  // выведет 2
    printf("%d", pop());  // выведет 2
    printf("\n");
    
    return 0;
}
