/*
Write a program to create a doubly linked list and perform insertion and deletion on the doubly linked list. 
Consider all possible cases of insertion and deletion. A few cases of insertion and deletion are mentioned below. 
This is not an exhaustive one.
1. insertBegin : Insert at the begin of the list
2. insertEnd: Insert at the end of the list
3. deleteBegin : Delete at the begin of the list
4. deleteEnd : Delete at the end of the list
5. insertAfter : Insert after a specific node
6. insertBefore : Insert before a specific node
7. deleteAfter : Delete a node after a specific node
8. deleteBefore : Delete a node before a specific node
Your program should have a function to display the linked list. 
Before deleting a node your program must check for empty condition. 
Write a menu driven program. User should able to enter his desired option. Based on the desired option, the required task is to be performed.
*/
# include <iostream>
using namespace std;

/* Node of a doubly linked list */
struct node 
{ 
    int data; 
    struct node * next; // Pointer to next node in DLL 
    struct node * prev; // Pointer to previous node in DLL 
};

// function to assign value in a node  
struct node * create (int val)
{
    struct node * new_node = new node;
    new_node->data = val;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// function to insert value at beginning of node
void insertBegin (struct node ** head, int val)
{
    struct node * temp = create(val);
    temp->next = *head;
    if (*head != NULL )                // is head is not null
        (*head)->prev = temp;
    *head = temp;
}

// function to insert value at end of linked list
void insertEnd ( struct node ** head, int val)
{
    struct node * temp = create (val);
    struct node * end = *head;
    
    // base case
    if(*head == NULL)
    {
        *head = temp;
        return;
    }

    while (end->next != NULL)
        end = end->next;
    end->next = temp;
    temp->prev = end;
}

// function to delete the beginning of linked list
void deleteBegin (struct node ** head)
{
    struct node * temp = *head;
    //base case
    if(*head == NULL)
    {
        cout<<"No node to be deleted. UnderFlow!!!.\n";
    }
    else if( (*head)->next == NULL)
    {
        *head = (*head)->next;
        free(temp);
    }   
    else
    {
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
}

// function to delete the end od linked list.
void deleteEnd (struct node ** head)
{
    struct node * temp;
    struct node * ptr = *head;
    if(*head == NULL)
    {
        cout<<"No node to be deleted. UnderFlow!!!.\n";
    }
    else if( (*head)->next == NULL)
    {
        *head = (*head)->next;
        free(ptr);
    }
    else
    {
        while (ptr->next != NULL)
            ptr = ptr->next;
        temp = ptr->prev;
        temp->next = NULL;
        ptr->prev = NULL;
        free(ptr);
    }    
}

// function to obtain the position of the value entered in linked list
struct node * find_loc (struct node * ptr, int value)
{
    while (ptr != NULL)
    {
        if (ptr->data == value )
            break;
        ptr = ptr->next;
    }
    return ptr;
}

// function to insert after a given node
void insertAfter (struct node ** head, int val1, int val)
{
    struct node * loc = find_loc (*head, val1);
    if (loc == NULL)
    {
        cout<<"No Such node found after which value is to be inserted.\n";
    }    
    else
    {
        struct node * temp = create (val);
        temp->next = loc->next;
        loc->next = temp;
        temp->prev = loc;
    }
}

// function to insert before a given node
void insertBefore (struct node ** head, int val1, int val)
{
    struct node * loc = find_loc (*head, val1);
    if (loc == NULL)
    {
        cout<<"No Such node found before which value is to be inserted.\n";
    }    
    else
    {
        struct node * temp = create (val);
        temp->prev = loc->prev;
        loc->prev = temp;
        temp->next = loc;
        if (temp->prev != NULL)
            temp->prev->next = temp;
        else
            *head = temp;   
    }
}

// function to delete after a given node
void deleteAfter (struct node ** head, int val1)
{
    struct node * loc = find_loc (*head, val1);
    if (loc == NULL)
    {
        cout<<"No Such node found , whose after node is to be deleted.\n";
    }
    else if (loc->next == NULL)
    {
        cout<<"This node does not have any after node to be deleted.\n";
    }
    else
    {
        struct node * temp = loc->next;
        loc->next =temp->next;
        if(temp->next != NULL)
        {
            temp->next->prev = temp->prev;
            temp->next = NULL;
            temp->prev = NULL;
        } 
        else
            temp->prev = NULL;
        free(temp);
    }
}

// function to delete before a given node
void deleteBefore (struct node ** head, int val1)
{
    struct node * loc = find_loc (*head, val1);
    if (loc == NULL)
    {
        cout<<"No Such node found , whose before node is to be deleted.\n";
    }
    else if (loc->prev == NULL)
    {
        cout<<"This node does not have any before node to be deleted. This is a head node.\n";
    }
    else
    {
        struct node * temp = loc->prev;
        loc->prev =temp->prev;
        if(temp->prev != NULL)
        {
            temp->prev->next = temp->next;
            temp->next = NULL;
            temp->prev = NULL;
        } 
        else
        {
            *head = loc;
            temp->next = NULL;
        }   
        free(temp);
    }
}

// function to delete a given node
void deleteNode (struct node ** head, int value)
{
    struct node * loc = find_loc (*head, value);
    if (loc == NULL)
    {
        cout<<"No Such node found , which is to be deleted.\n";
    }
    else if(loc->next == NULL && loc->prev == NULL)
    {
        *head = (*head)->next;
        free(loc);
    }
    else
    {
        if(loc->prev != NULL)
            loc->prev->next = loc->next;
        else
        {
            *head = (*head)->next;
            (*head)->prev = NULL;
            loc->next = NULL;
            free(loc);
            return;
        }
        if (loc->next != NULL)
            loc->next->prev = loc->prev;
        else
        {
            loc->prev->next = NULL;
            loc->prev = NULL;
            free(loc);
            return;
        }
        loc->next = NULL;
        loc->prev = NULL;
        free(loc);    
    }   
}

// function to display the elements of the linked list
void display (struct node * head)
{
    if(head == NULL)
        cout<<"No elements in the linked list.\n";
    else
    {
        while(head->next  != NULL)
        {
            cout<<head->data<<"->";
            head = head->next;
        }
        cout<<head->data<<"->NULL.\n";
    }
    
}

// main function
int main ()
{
    struct node * head = NULL;
    char ch;
    int ch1;
    int value, value1;
    cout<<"Menu Driven Program for doubly linked list.\n";
    cout<<"Press 1 to perform insertion at beginning.\n";
    cout<<"Press 2 to perforn insertion at end.\n";
    cout<<"Press 3 to perform deletion at beginning.\n";
    cout<<"Press 4 to perforn deletion at end.\n";
    cout<<"Press 5 to perform insertion after a specific node.\n";
    cout<<"Press 6 to perforn insertion before a specific node.\n";
    cout<<"Press 7 to perform deletion after a specific node.\n";
    cout<<"Press 8 to perform deletion before a specific node.\n";
    cout<<"Press 9 to perform deletion of a specific node.\n";
    cout<<"Press 10 to display the doubly linked list.\n";

    do
    {
        cout<<"Please Enter your choice among '1'   '2'   '3'   '4'   '5'   '6'   '7'   '8'   '9'   '10'.\n";
        cin>>ch1;
        switch(ch1)                             // menu driven cases
        {
            case 1: cout<<"Enter value to be inserted.\n";
                    cin>>value;
                    insertBegin(&head, value);
                    cout<<"Success.\n";
                    break;
            case 2: cout<<"Enter value to be inserted.\n";
                    cin>>value;
                    insertEnd(&head, value);
                    cout<<"Success.\n";
                    break;
            case 3: deleteBegin(&head);
                    cout<<"Success.\n";
                    break;
            case 4: deleteEnd(&head);
                    cout<<"Success.\n";
                    break;       
            case 5: cout<<"Enter a node value after which new value is to be inserted.\n";
                    cin>>value1;
                    cout<<"Enter new value to be inserted.\n";
                    cin>>value;
                    insertAfter(&head, value1, value);
                    cout<<"Success.\n";
                    break;
            case 6: cout<<"Enter a node value before which new value is to be inserted.\n";
                    cin>>value1;
                    cout<<"Enter new value to be inserted.\n";
                    cin>>value;
                    insertBefore(&head, value1, value);
                    cout<<"Success.\n";
                    break;
            case 7: cout<<"Enter a node value whose after node is to be deleted.\n";
                    cin>>value1;
                    deleteAfter(&head, value1);
                    cout<<"Success.\n";
                    break;
            case 8: cout<<"Enter a node value whose before node is to be deleted.\n";
                    cin>>value1;
                    deleteBefore(&head, value1);
                    cout<<"Success.\n";
                    break;
            case 9: cout<<"Enter a node value which is to be deleted.\n";
                    cin>>value;
                    deleteNode(&head, value);
                    cout<<"Success.\n";
                    break;
            case 10: cout<<"The given linked list elements are : \n";
                    display(head);
                    break;
            default:cout<<"Wrong Choice Entered.\n";
        }
        cout<<"Dou you want to continue performing operation?.\n";
        cout<<"Enter y for YES else n for NO.\n";
        cin>>ch;
    } while (ch == 'y' || ch == 'Y');
    return 0;
}