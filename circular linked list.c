#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node {
    int data;
    struct node *link;
};

struct node *head = NULL, *last = NULL;

// Function declarations
void create();
void insertatlast(int val);
void display();
void insertatbegin();
void insertatposition();
void dab(); // delete at beginning
void dae(); // delete at end
void dap(); // delete at position

int main() {
    int op, val, n;
    printf("Enter number of nodes:\n");
    scanf("%d", &n);
    while (n--) create(); // create initial list

    do {
        printf("\nMenu:\n1. Insert at last\n2. Display\n3. Insert at begin\n4. Insert at position\n5. dab\n6. dae\n7. dap\n8. exit\nEnter your choice: ");
        scanf("%d", &op);
        switch (op) {
            case 1: printf("Enter value to insert: "); scanf("%d", &val); insertatlast(val); display(); break;
            case 2: display(); break;
            case 3: insertatbegin(); display(); break;
            case 4: insertatposition(); display(); break;
            case 5: dab(); display(); break;
            case 6: dae(); display(); break;
            case 7: dap(); display(); break;
            case 8: printf("Exiting program.\n"); exit(1);
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (op != 8);
    return 0;
}

// create one node and insert at end
void create() {
    int val;
    printf("Enter a number: ");
    scanf("%d", &val);
    insertatlast(val);
}

// insert node at last
void insertatlast(int val) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = val; temp->link = NULL;
    if (head == NULL) {
        head = temp; last = temp; last->link = head;
    } else {
        last->link = temp; last = temp; last->link = head;
    }
}

// print the list
void display() {
    if (head == NULL) {
        printf("List is empty.\n"); return;
    }
    struct node *temp = head;
    printf("Circular Linked List: ");
    do {
        printf("%d\t", temp->data);
        temp = temp->link;
    } while (temp != head);
    printf("\n");
}

// insert at beginning
void insertatbegin() {
    int pos;
    printf("Enter value to insert\n");
    scanf("%d", &pos);
    struct node *sr = (struct node *)malloc(sizeof(struct node));
    sr->data = pos;
    if (head == NULL) {
        head = sr; sr->link = head; last = sr;
    } else {
        sr->link = head; last->link = sr; head = sr;
    }
}

// insert at given position
void insertatposition() {
    struct node *prev = NULL, *curr = NULL;
    int pos, v, count = 1;
    printf("Enter the pos u want to insert\n");
    scanf("%d", &pos);
    printf("Enter the val u want to insert\n");
    scanf("%d", &v);
    prev = head;
    curr = (struct node *)malloc(sizeof(struct node));
    curr->data = v; curr->link = NULL;

    if (pos == 1) {
        curr->link = head; last->link = curr; head = curr; return;
    }

    int p = pos; pos--;
    while (pos != 1 && prev->link != head) {
        prev = prev->link; count++; pos--;
    }

    if (p > count + 1) {
        printf("invalid\n"); return;
    } else if (prev->link == head) {
        insertatlast(v); return;
    } else {
        curr->link = prev->link; prev->link = curr;
    }
}

// delete at beginning
void dab() {
    if (head == NULL) {
        printf("list is empty\n"); return;
    }
    struct node *temp = head;
    if (head == last) {
        free(head); head = NULL; last = NULL;
    } else {
        head = head->link; last->link = head; free(temp);
    }
}

// delete at end
void dae() {
    if (head == NULL) {
        printf("list is empty\n"); return;
    }
    struct node *ptr = head, *ptr2 = head;
    if (head == last) {
        free(head); head = NULL; last = NULL; return;
    }
    while (ptr->link != head) {
        ptr2 = ptr; ptr = ptr->link;
    }
    ptr2->link = head; free(ptr); last = ptr2;
}

// delete at given position
void dap() {
    int pos;
    struct node *prev = head, *curr;
    printf("Enter position to delete\n");
    scanf("%d", &pos);
    if (head == NULL) {
        printf("List is empty.\n"); return;
    }
    int count = 1;
    struct node *temp = head;

    if (pos == 1) {
        dab(); return;
    }

    pos--;
    while (pos != 1 && prev->link != head) {
        prev = prev->link; pos--; count++;
    }

    if (prev->link == head || pos > 1) {
        printf("invalid\n"); return;
    }

    curr = prev->link;
    prev->link = curr->link;
    if (curr == last) last = prev;
    free(curr);
}
