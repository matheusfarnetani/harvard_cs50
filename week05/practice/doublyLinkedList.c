// Doubly-Linked Lists

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* 
Singly-linked lists really extend our ability to collect and organize data, but
they suffer from a crucial limitation.
    
    We can only ever move in one direction through the list.

Consider the implication that would have for trying to delete a node.

A doubly-linked list, by contrast, allows us to move forward and backward through the list,
all by simply adding one extra pointer to our 'struct' definition
*/

typedef struct dllist
{
    int val;
    struct dllist *next;
    struct dllist *prev;
}
dllnode;

/*
In order to work with linked lists effectively, there are a number of operations
that we need to understand:

    1. Create a linked list when it doesn't already exist.
    2. Search through a linked list to find an element.
    3. Insert a new node into the linked list.
    4. Delete a single element from a linked list.
    5. Delete an entire linked list.
*/

// Prototypes 
dllnode *create(int value);
bool find(dllnode *head, int value);
dllnode *insert(dllnode *head, int value);
void destroy(dllnode *head);
int delete(dllnode *head, int value);

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./doublyLinkedList [number of values]\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./doublyLinkedList [number of values]\n");
            return 1;
        }
    }

    int numValues = atoi(argv[1]);
    
    // Create linked list
    dllnode *head = NULL;

    for (int i = 0; i < numValues; i++)
    {
        int number;
        printf("Enter an integer: ");
        scanf("%d", &number);

        dllnode *newNode = create(number);
        if (newNode == NULL)
        {
            printf("Memory allocation failed.\n");
            return 2;
        }

        if (head != NULL)
        {
            // Connect the new node to the previous node
            newNode->next = head;
            head->prev = newNode;
        }

        head = newNode;
    }

    // Search for a number
    int searchNumber;
    printf("Enter an integer to be searched: ");
    scanf("%d", &searchNumber);

    if (find(head, searchNumber) == true)
    {
        printf("The integer %i exist in the linked list\n", searchNumber);
    }
    else
    {
        printf("The integer %i doest not exist in the linked list\n", searchNumber);
    }

    // Insert a number
    int insertNumber;
    printf("Enter an integer to be inserted: ");
    scanf("%d", &insertNumber);

    dllnode *newHead = insert(head, insertNumber);
    if (newHead == NULL)
    {
        printf("Memory allocation failed.\n");
        destroy(head);
        return 3;    
    }

    head = newHead;

    // delete a number
    int deleteNumber;
    printf("Enter an integer to be deleted: ");
    scanf("%d", &deleteNumber);

    if (delete(head, deleteNumber)!= 0)
    {
        printf("Couldn't delete %i\n", deleteNumber);
        return 4;
    }

    // Free Memory
    destroy(head);
    return 0;
}

dllnode *create(int value)
{
    /*
    Steps Involved:
        a. Dynamically allocate space for a new dllnode.
        b. Check to make sure we didn't run out of memory.
        c. Initialize the node's value field.
        d. Initialize the node's next field.
        e. Initialize the node's prev field.
        f. Return a pointer to the newly created sllnode.
    */

    dllnode *n = malloc(sizeof(dllnode));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = value;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

bool find(dllnode *head, int value)
{
    /*
    Steps Involved:
        a. Create a traversal pointer pointing to the list's head.
        b. If the current node's value field is what we're looking for, report success.
        c. If not, set the traversal pointer to the next pointer in the list and go back to step b.
        d. If you've reached the end of the list, report failure.
    */

   dllnode *current = head;

   while (current != NULL)
   {
        if (current->val == value)
        {
            return true;
        }

        current = current->next;
   }

   return false;
}

dllnode *insert(dllnode *head, int value)
{
    /*
    Steps Involved:
        a. Dynamically allocate space for a new dllnode.
        b. Check to make sure we didn't run out of memory.
        c. Populate and insert the node at the beginning of the linked list.
        d. Fix the prev pointer of the old head of the linked list.
        e. Return a pointer to the new head of the linked list.
    */

    dllnode *n = malloc(sizeof(dllnode));
    if (n == NULL)
    {
        return NULL;
    }

    printf("Inserting %i\n", value);

    n->val = value;
    n->next = head;
    n->prev = NULL;

    if (head != NULL)
    {
        head->prev = n;
    }

    return n;
}

void destroy(dllnode *head)
{
    /*
    Steps Involved:
        a. If you've reached a null pointer, stop
        b. Delete the rest of the list.
        c. Free the current node.
    */

    if (head == NULL)
    {
        return;
    }

    if (head->next == NULL)
    {
        // If it's the last node
        printf("Deleting %i\n", head->val);
        free(head);
    }
    else
    {
        destroy(head->next);
        printf("Deleting %i\n", head->val);
        free(head);
    }
}

int delete(dllnode *head, int value)
{
    /*
    Steps Involved:
        a. Fix the pointers of the surrounding nodes to "skipe over" target.
        b. Free Target
    */

    dllnode *current = head;
    dllnode *previous = NULL;

    while (current != NULL)
    {
        if (current->val == value)
        {
            if (previous != NULL)
            {
                previous->next = current->next;
                if (current->next != NULL) // Update the prev pointer of the next node
                {
                    current->next->prev = previous;
                }
            }
            else
            {
                head = current->next;
                if (head != NULL) // Update the prev pointer of the new head
                {
                    head->prev = NULL;
                }
            }

            printf("Deleting %i\n", current->val);

            free(current);

            return 0;
        }

        previous = current;
        current = current->next;
    }

    return 1;
}