#include <stdio.h>
#include <stdlib.h>

#define SIZE(arr) (sizeof(arr)/sizeof(arr[0]))


struct Node
{
    int data;
    struct Node *next;
    struct Node *down;
};
void push(struct Node** headRef, int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;
    newNode->down = *headRef;
    *headRef = newNode;
}
struct Node* sortedMerge(struct Node* a, struct Node* b)
{
    if (a == NULL) {
        return b;
    }
    else if (b == NULL) {
        return a;
    }
    struct Node* result = NULL;
    if (a->data <= b->data)
    {
        result = a;
        result->down = sortedMerge(a->down, b);
    }
    else {
        result = b;
        result->down = sortedMerge(a, b->down);
    }

    return result;
}

struct Node* flatten(struct Node* head)
{

    if (head == NULL) {
        return head;
    }
    struct Node* sorted = sortedMerge(head, flatten(head->next));
    head->next = NULL;

    return sorted;
}


void printList(struct Node *node)
{
    while (node)
    {
        printf("%d —> ", node->data);
        node = node->down;
    }
    printf("NULL");
}


void createVerticalList(struct Node **head, int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        push(head, arr[i]);
    }
}

int main(void)
{
    struct Node* head = NULL;

    int arr1[] = { 30, 8, 7, 5 };
    int arr2[] = { 20, 10 };
    int arr3[] = { 50, 22, 19 };
    int arr4[] = { 45, 40, 35, 28 };

    createVerticalList(&(head), arr1, SIZE(arr1));
    createVerticalList(&(head->next), arr2, SIZE(arr2));
    createVerticalList(&(head->next->next), arr3, SIZE(arr3));
    createVerticalList(&(head->next->next->next), arr4, SIZE(arr4));

    // flatten the list
    flatten(head);

    printList(head);

    return 0;
}
