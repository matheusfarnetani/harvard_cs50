// Singly-Linked Lists

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* 
We call this combination of elements, when used in this way, a linked list.

A linked list node is a special kind of struct with two members:
    Data of some data type (int, char, float...)
    A pointer to another node of the same type

In this way, a set of nodes together can be thought of as forming a chaing of
elements that we can follow from beginning to end
*/

typedef struct sllist
{
    int val;
    struct sllist *next;
}
sllnode;

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
sllnode *create(int value);
bool find(sllnode *head, int value);
sllnode *insert(sllnode *head, int value);
void destroy(sllnode *head);

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        printf("Usage: ./singlyLinkedList [number of values]\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./singlyLinkedList [number of values]\n");
            return 1;
        }
    }

    int numValues = atoi(argv[1]);
    
    // Create linked list
    sllnode *head = NULL;
    for (int i = 0; i < numValues; i++)
    {
        int number;
        printf("Enter an integer: ");
        scanf("%d", &number);

        sllnode *newNode = create(number);
        if (newNode == NULL)
        {
            printf("Memory allocation failed.\n");
            return 2;
        }

        if (head != NULL)
        {
            // Connect the new node to the previous node
            newNode->next = head;
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

    head = insert(head, insertNumber);
    if (head == NULL)
    {
        printf("Memory allocation failed.\n");
        return 3;    
    }

    // Free Memory
    destroy(head);
    return 0;
}

sllnode *create(int value)
{
    /*
    Steps Involved:
        a. Dynamically allocate space for a new sllnode.
        b. Check to make sure we didn't run out of memory.
        c. Initialize the node's value field.
        d. Initialize the node's next field.
        e. Return a pointer to the newly created sllnode.
    */

    sllnode *n = malloc(sizeof(sllnode));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = value;
    n->next = NULL;

    return n;
}

bool find(sllnode *head, int value)
{
    /*
    Steps Involved:
        a. Create a traversal pointer pointing to the list's head.
        b. If the current node's value field is what we're looking for, report success.
        c. If not, set the traversal pointer to the next pointer in the list and go back to step b.
        d. If you've reached the end of the list, report failure.
    */

   sllnode *current = head;

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

sllnode *insert(sllnode *head, int value)
{
    /*
    Steps Involved:
        a. Dynamically allocate space for a new sllnode.
        b. Check to make sure we didn't run out of memory.
        c. Populate and insert the node at the beginning of the linked list.
        d. Return a pointer to the new head of the linked list.
    */

    sllnode *n = malloc(sizeof(sllnode));
    if (n == NULL)
    {
        return NULL;
    }

    n->val = value;
    n->next = head;

    return n;
}

void destroy(sllnode *head)
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