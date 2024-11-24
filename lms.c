#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to store book information
struct Node {
    int id;
    char name[50];
    char author[50];
    char publisher[50];
    struct Node* next_add;
};

// Stack node structure for undo functionality
struct StackNode {
    struct Node* book;
    struct StackNode* next;
};

// Queue node structure for FIFO operation
struct QueueNode {
    struct Node* book;
    struct QueueNode* next;
};

// Library structure to hold linked list, stack, and queue
struct Library {
    struct Node* head;            // Head of the linked list of books
    struct StackNode* stack_top;  // Stack top for undo
    struct QueueNode* front;      // Front of the queue for books
    struct QueueNode* rear;       // Rear of the queue for books
};

// Function prototypes
void menu(struct Library* lib);
void insert(struct Library* lib);
void search(struct Library* lib);
void update(struct Library* lib);
void del(struct Library* lib);
void undo(struct Library* lib);
void sort(struct Library* lib);
void show(struct Library* lib);
void enqueue(struct Library* lib, struct Node* newBook);
void dequeue(struct Library* lib);
void displayQueue(struct Library* lib);
void pushToStack(struct Library* lib, struct Node* deletedBook);
struct Node* popFromStack(struct Library* lib);

// Main function
int main() {
    struct Library lib = {NULL, NULL, NULL, NULL};  // Initialize library
    menu(&lib);  // Show the menu to the user
    return 0;
}

// Push a deleted book onto the undo stack
void pushToStack(struct Library* lib, struct Node* deletedBook) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->book = deletedBook;
    newNode->next = lib->stack_top;
    lib->stack_top = newNode;
}

// Pop a book from the undo stack
struct Node* popFromStack(struct Library* lib) {
    if (lib->stack_top == NULL) {
        printf("No operation to undo.\n");
        return NULL;
    }
    struct Node* topBook = lib->stack_top->book;
    struct StackNode* temp = lib->stack_top;
    lib->stack_top = lib->stack_top->next;
    free(temp);
    return topBook;
}

// Undo the last operation (restores a deleted book)
void undo(struct Library* lib) {
    struct Node* book = popFromStack(lib);
    if (book) {
        printf("Undoing last operation... Restoring Book: %s\n", book->name);
        insert(lib);  // Insert the book back to the list
    }
}

// Enqueue a new book to the queue
void enqueue(struct Library* lib, struct Node* newBook) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->book = newBook;
    newNode->next = NULL;
    if (lib->rear == NULL) {
        lib->front = lib->rear = newNode;
    } else {
        lib->rear->next = newNode;
        lib->rear = newNode;
    }
}

// Dequeue a book from the queue
void dequeue(struct Library* lib) {
    if (lib->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    struct QueueNode* temp = lib->front;
    lib->front = lib->front->next;
    if (lib->front == NULL) {
        lib->rear = NULL;
    }
    free(temp);
}

// Display the books in the queue
void displayQueue(struct Library* lib) {
    struct QueueNode* ptr = lib->front;
    while (ptr != NULL) {
        printf("Book ID: %d Name: %s\n", ptr->book->id, ptr->book->name);
        ptr = ptr->next;
    }
}

// Show the menu and execute user's choice
void menu(struct Library* lib) {
    int choice;
    do {
        system("cls");
        printf("\n\n\t\t\t***********************************");
        printf("\n\n\t\t\t*****LIBRARY MANAGEMENT SYSTEM*****");
        printf("\n\n\t\t\t***********************************");
        printf("\n\n 1. INSERT NEW RECORD");
        printf("\n\n 2. SEARCH RECORD");
        printf("\n\n 3. UPDATE RECORD");
        printf("\n\n 4. DELETE RECORD");
        printf("\n\n 5. SHOW ALL RECORD");
        printf("\n\n 6. UNDO LAST OPERATION");
        printf("\n\n 7. EXIT");
        printf("\n\n ENTER YOUR CHOICE: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                insert(lib);
                break;
            case 2:
                search(lib);
                break;
            case 3:
                update(lib);
                break;
            case 4:
                del(lib);
                break;
            case 5:
                sort(lib);
                show(lib);
                break;
            case 6:
                undo(lib);
                break;
            case 7:
                exit(0);
            default:
                printf("\n\n Invalid choice.. Please try again...\n");
        }
        system("pause");
    } while (choice != 7);
}

// Insert a new book into the library
void insert(struct Library* lib) {
    system("cls");
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    printf("\n\n Book ID: ");
    scanf("%d", &new_node->id);
    printf("\n\n Name: ");
    scanf(" %[^\n]s", new_node->name);  // Reading string with spaces
    printf("\n\n Author Name: ");
    scanf(" %[^\n]s", new_node->author);
    printf("\n\n Publisher Name: ");
    scanf(" %[^\n]s", new_node->publisher);
    new_node->next_add = NULL;

    // Add to Queue before inserting
    enqueue(lib, new_node);

    // Insert the book into the linked list
    if (lib->head == NULL) {
        lib->head = new_node;
    } else {
        struct Node* ptr = lib->head;
        while (ptr->next_add != NULL) {
            ptr = ptr->next_add;
        }
        ptr->next_add = new_node;
    }
    printf("\n\n\t\t\t NEW BOOK INSERTED SUCCESSFULLY....\n");
}

// Search for a book by its ID and display details
void search(struct Library* lib) {
    system("cls");
    int t_id, found = 0;
    printf("\n\n\t\t\t***********************************");
    printf("\n\n\t\t\t*****LIBRARY MANAGEMENT SYSTEM*****");
    printf("\n\n\t\t\t***********************************");
    if (lib->head == NULL) {
        printf("\n\n LINKED LIST IS EMPTY...\n");
    } else {
        printf("\n\n BOOK ID: ");
        scanf("%d", &t_id);
        struct Node* ptr = lib->head;
        while (ptr != NULL) {
            if (t_id == ptr->id) {
                system("cls");
                printf("\n\n\t\t\t***********************************");
                printf("\n\n\t\t\t*****LIBRARY MANAGEMENT SYSTEM*****");
                printf("\n\n\t\t\t***********************************");
                printf("\n\n Book ID: %d", ptr->id);
                printf("\n\n Book Name: %s", ptr->name);
                printf("\n\n Author Name: %s", ptr->author);
                printf("\n\n Publisher Name: %s", ptr->publisher);
                found++;
            }
            ptr = ptr->next_add;
        }
        if (found == 0) {
            printf("\n\n BOOK ID IS INVALID...\n");
        }
    }
}

// Update a book's details by its ID
void update(struct Library* lib) {
    system("cls");
    int t_id, found = 0;
    printf("\n\n\t\t\t***********************************");
    printf("\n\n\t\t\t*****LIBRARY MANAGEMENT SYSTEM*****");
    printf("\n\n\t\t\t***********************************");
    if (lib->head == NULL) {
        printf("\n\n LINKED LIST IS EMPTY...\n");
    } else {
        printf("\n\n BOOK ID: ");
        scanf("%d", &t_id);
        struct Node* ptr = lib->head;
        while (ptr != NULL) {
            if (t_id == ptr->id) {
                system("cls");
                printf("\n\n\t\t\t***********************************");
                printf("\n\n\t\t\t*****LIBRARY MANAGEMENT SYSTEM*****");
                printf("\n\n\t\t\t***********************************");
                printf("\n\n New Book Name: ");
                scanf(" %[^\n]s", ptr->name);
                printf("\n\n New Author Name: ");
                scanf(" %[^\n]s", ptr->author);
                printf("\n\n New Publisher Name: ");
                scanf(" %[^\n]s", ptr->publisher);
                found++;
            }
            ptr = ptr->next_add;
        }
        if (found == 0) {
            printf("\n\n BOOK ID IS INVALID...\n");
        }
    }
}

// Delete a book and push it onto the stack for undo
void del(struct Library* lib) {
    system("cls");
    int t_id, found = 0;
    printf("\n\n\t\t\t***********************************");
    printf("\n\n\t\t\t*****LIBRARY MANAGEMENT SYSTEM*****");
    printf("\n\n\t\t\t***********************************");
    if (lib->head == NULL) {
        printf("\n\n LINKED LIST IS EMPTY...\n");
    } else {
        printf("\n\n Book ID: ");
        scanf("%d", &t_id);
        struct Node* ptr = lib->head;
        struct Node* prev = NULL;
        while (ptr != NULL) {
            if (t_id == ptr->id) {
                system("cls");
                if (prev == NULL) {
                    lib->head = ptr->next_add;  // Deleting the first book
                } else {
                    prev->next_add = ptr->next_add;  // Deleting a book in the middle or end
                }
                pushToStack(lib, ptr);  // Push deleted book to the stack
                free(ptr);
                printf("\n\n\t\t\t Book Deleted Successfully...\n");
                found++;
                break;
            }
            prev = ptr;
            ptr = ptr->next_add;
        }
        if (found == 0) {
            printf("\n\n BOOK ID IS INVALID...\n");
        }
    }
}

// Show all books in the library
void show(struct Library* lib) {
    system("cls");
    if (lib->head == NULL) {
        printf("\n\n LINKED LIST IS EMPTY...\n");
    } else {
        struct Node* ptr = lib->head;
        printf("\n\n\t\t\t*****LIBRARY MANAGEMENT SYSTEM*****");
        printf("\n\n\t\t\t***********************************");
        while (ptr != NULL) {
            printf("\n\n Book ID: %d", ptr->id);
            printf("\n Book Name: %s", ptr->name);
            printf("\n Author Name: %s", ptr->author);
            printf("\n Publisher Name: %s", ptr->publisher);
            ptr = ptr->next_add;
        }
    }
}

// Sort books based on ID in ascending order using bubble sort
void sort(struct Library* lib) {
    if (lib->head == NULL) return;
    struct Node *ptr, *temp;
    int swapped;
    do {
        swapped = 0;
        ptr = lib->head;
        while (ptr->next_add != NULL) {
            if (ptr->id > ptr->next_add->id) {
                // Swap books
                temp = ptr;
                ptr = ptr->next_add;
                temp->next_add = ptr->next_add;
                ptr->next_add = temp;
                swapped = 1;
            }
            ptr = ptr->next_add;
        }
    } while (swapped);
}

