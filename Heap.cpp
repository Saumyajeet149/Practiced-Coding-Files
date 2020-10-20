/*
Write a program to create a binary heap: (a) min-heap, or (b) max-heap depending upon the user choice. 
Perform insertion, and deletion to either of the heap. Your program should also able to print the heap after performing each operation.
*/
#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node * par;
    struct node * left;
    struct node * right;
};

struct link
{
    struct node * ele;
    struct link * next;
};

struct node * create_node (struct node * parent, int val)
{
    struct node * new_node = new node;
    new_node->data = val;
    new_node->par = parent;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct link * create_link (struct node * element)
{
    struct link * new_link = new link;
    new_link->ele = element;
    new_link->next = NULL;
    return new_link;
}
 
void free_link (struct link ** a)
{
    struct link * temp = *a;
    while(temp != NULL)
    {
        *a = temp->next;
        free(temp);
        temp = *a;
    }
}

void link_join (struct node * n1, struct link ** end)
{
    if(n1->left != NULL)
    {
        (*end)->next = create_link(n1->left);
        *end = (*end)->next;
    }
    if(n1->right != NULL)
    {
        (*end)->next = create_link(n1->right);
        *end = (*end)->next;
    }
}

void insertHeap (struct node ** root, int val, int ch = 1)
{
    // New node is heap if it is empty before hand
    if(*root == NULL)
        *root = create_node(NULL, val);
    // Searching for the location to insert
    else
    {
        struct link * l = create_link(*root);
        struct link * cur = l;
        struct link * end = l;
        struct node * cur_node;
        while (cur != NULL)
        {
            cur_node = cur->ele;       // obtaining a node from the link
            if(cur_node->left == NULL)
            {
                cur_node->left = create_node(cur_node, val);
                cur_node = cur_node->left;
            }
            else if(cur_node->right == NULL)
            {
                cur_node->right = create_node(cur_node, val);
                cur_node = cur_node->right;
            }
            else
            {
                link_join(cur_node, &end);
                cur = cur->next;                // incrementing the current link pointer
                continue;
            }
            if(ch == 1)     // Max Heap
            {
                while(cur_node->par != NULL && cur_node->par->data < cur_node->data)
                {
                    // Swap
                    int temp = cur_node->par->data;
                    cur_node->par->data = cur_node->data;
                    cur_node->data = temp;
                    cur_node = cur_node->par;
                }
            }
            else          // Min Heap
            {
                while(cur_node->par != NULL && cur_node->par->data > cur_node->data)
                {
                    // Swap
                    int temp = cur_node->par->data;
                    cur_node->par->data = cur_node->data;
                    cur_node->data = temp;
                    cur_node = cur_node->par;
                }
            }
            break;
        }
        free_link(&l);
    }
}

void deleteHeapElement (struct node ** root, int ch = 1)
{
    if (*root == NULL) 
        cout<<"Heap is already Empty.\n";
    else
    {
        struct link * l = create_link(*root);
        struct link * cur = l;
        struct link * end = l;
        struct link * prev = l;
        struct node * cur_node;
        
        // Finding the Last node
        while(cur != NULL)
        {
            cur_node = cur->ele;
            link_join(cur_node, &end);
            prev = cur;
            cur = cur->next;
        }
        cur_node = prev->ele;
        free_link(&l);

        // Removing the last node and storing it's value in root
        if(cur_node->par == NULL)
        {
            free(cur_node);
            *root = NULL;
        }
        else
        {
            (*root)->data = cur_node->data;
            cur_node = cur_node->par;
            if(cur_node->right != NULL)
            {
                free(cur_node->right);
                cur_node->right = NULL;
            }
            else
            {
                free(cur_node->left);
                cur_node->left = NULL;
            }
            
            // Moving the root node down to appropriate location
            int a,b,c;
            cur_node = *root;
            while(1)
            {
                if(cur_node->left == NULL)
                    break;                      // Implies right node is also NULL
                else if(cur_node->right == NULL)
                {
                    a = cur_node->data;
                    b = cur_node->left->data;
                    if (a < b && ch == 1)           // For max heap
                    {
                        cur_node->data = b;
                        cur_node->left->data = a;
                        cur_node = cur_node->left;
                    }
                    else if(a > b && ch != 1)           // for min heap
                    {
                        cur_node->data = b;
                        cur_node->left->data = a;
                        cur_node = cur_node->left;
                    }
                    else
                        break; 
                }
                else
                {
                    a = cur_node->data;
                    b = cur_node->left->data;
                    c = cur_node->right->data;
                    
                    
                    if(ch == 1)                         // For Max Heap                        
                    {
                        // if a is largest, do nothing
                        if(a >= b && a >= c)
                            break;
                        else if(b > a && b>=c)
                        {
                            cur_node->left->data = a;
                            cur_node->data = b;
                            cur_node = cur_node->left;
                        }
                        else
                        {
                            cur_node->right->data = a;
                            cur_node->data = c;
                            cur_node = cur_node->right;
                        }
                    }
                    else                                    // For Mean Heap
                    {
                        if(a <= b && a <= c)
                            break;
                        else if(b < a && b<=c)
                        {
                            cur_node->left->data = a;
                            cur_node->data = b;
                            cur_node = cur_node->left;
                        }
                        else
                        {
                            cur_node->right->data = a;
                            cur_node->data = c;
                            cur_node = cur_node->right;
                        }
                    }    
                } 
            } 
        } 
    } 
}
void print (struct node * root)
{
    if(root == NULL)
        cout<<"Heap is empty.\n";
    else
    {
        cout<<"Heap in Level Order : ";
        struct link * l = create_link(root);
        struct link * cur = l;
        struct link * end = l;
        struct node * temp;
        while (cur != NULL)
        {
            temp = cur->ele;
            link_join(temp, &end);
            cout<<temp->data<<"  ";
            cur = cur->next;
        }
        free_link(&l);
        cout<<"\n";
    } 
}
int main()
{
    struct node * root = NULL;
    int val,ch2;
    char ch,choice;
    cout<<"Enter a to perform operations in Max Heap.\n";
    cout<<"Enter any other to perform operations in Min Heap.\n";
    cin>>ch;

    // Menu Driven Cases
    cout<<"Enter 1 to perform insertion into Heap.\n";
    cout<<"Enter 2 to perform deletion from Heap.\n";
    do
    {
        cout<<"Enter your choice '1 or 2'.\n";
        cin>>ch2;
        if(ch == 'a')
        {
            switch(ch2)
            {
                case 1: cout<<"Enter element to be inserted.\n";
                        cin>>val;
                        insertHeap(&root, val);
                        cout<<"After inserting:\n";
                        print(root);
                        break;
                case 2: deleteHeapElement(&root);
                        cout<<"After Deletion:\n";
                        print(root);
                        break;
                default:cout<<"Wrong choice Entered.\n";
            }
        }
        else
        {
            switch(ch2)
            {
                case 1: cout<<"Enter element to be inserted.\n";
                        cin>>val;
                        insertHeap(&root, val, 2);
                        cout<<"After inserting:\n";
                        print(root);
                        break;
                case 2: deleteHeapElement(&root, 2);
                        cout<<"After Deletion:\n";
                        print(root);
                        break;
                default:cout<<"Wrong choice Entered.\n";
            }
        }
        cout<<"For continuing further operations again press y.\n";
        cin>>choice;
    } while (choice == 'Y' || choice == 'y');  
}