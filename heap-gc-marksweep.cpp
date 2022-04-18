// BT20CSE056 
// JC MANJUNATH

#include<iostream>
using namespace std;

struct Node
{
    int data;   // data of the node
    bool mark;  // mark bit
    struct Node* adjacent1; // point to the first adjacent node
    struct Node* adjacent2; // point to the second adjacent node
    struct Node* adjacent3; // point to the third adjacent node
    
    Node(int data)   // default + parametric constructor
    {
        this->data = data;
        adjacent1=NULL;
        adjacent2=NULL;
        adjacent3=NULL;
        mark=false;
    }
};
typedef struct root_tag
{
    Node* point;
}root;

Node* heap[8];

void initialize(root& root1,root& root2)    
{                                                   
    Node* temp = new Node(5);   // create a node with data 5 (root1)
    heap[0]=temp;               // store the node in heap[0]
    temp = new Node(1);         // create a node with data 1 (root2)
    heap[1]=temp;               // store the node in heap[1]
    temp = new Node(2);         // create a node with data 2
    heap[2]=temp;               // store the node in heap[2]
    temp = new Node(9);         // create a node with data 9
    heap[3]=temp;               // store the node in heap[3]
    temp = new Node(10);        // create a node with data 10
    heap[4]=temp;               // store the node in heap[4]
    temp = new Node(7);         // create a node with data 7
    heap[5]=temp;               // store the node in heap[5]
    temp = new Node(8);         // create a node with data 8
    heap[6]=temp;               // store the node in heap[6]
    temp = new Node(3);         // create a node with data 3
    heap[7]=temp;               // store the node in heap[7]
    temp = NULL;                // set temp to NULL

    // Creating connections between nodes
    root1.point=heap[0];      //root1->5
    heap[0]->adjacent1=heap[1]; //5->1
    root2.point=heap[1];      //root2->1
    heap[1]->adjacent1=heap[2]; //1->2
    heap[1]->adjacent2=heap[3]; //1->9
    heap[1]->adjacent3=heap[4]; //1->10
    heap[5]->adjacent1=heap[1]; //7->1
    heap[5]->adjacent2=heap[6]; //7->8
    heap[6]->adjacent1=heap[4]; //8->10
    heap[7]->adjacent1=heap[6]; //3->8
    heap[7]->adjacent2=heap[4]; //3->10
}

void mark_Node(Node* ptr)   
{
    Node* head=ptr;         // head of the list
    Node* tail=NULL;        // tail of the list
    Node* middle=NULL;      // middle of the list
    int flag=1;          
    while(head !=NULL)  
    {
        if(!head->mark) //if Node we are on is unmarked, mark it
        {
            head->mark=true;
        }
        if(head->adjacent1!=NULL && !head->adjacent1->mark) //if adjacent Node to this is unmarked, move to it
        {
            tail=middle;
            middle=head;
            head=head->adjacent1;
        }
        else if(head->adjacent2!=NULL && !head->adjacent2->mark)//only move along one adjacent path every iteration
        {
            tail=middle;
            middle=head;
            head=head->adjacent2;   
        }
        else if(head->adjacent3!=NULL && !head->adjacent3->mark)   
        {
            tail=middle;
            middle=head;
            head=head->adjacent3;   
        }
        else
        {
            head=middle;
            middle=tail;
            tail=NULL;
        }

    }
}

void mark(const root& value)
{
    mark_Node(value.point);       // mark the root
}

void sweep(Node** ptr)      // sweep the heap
{
    for(int i=0;i<8;i++)    // for each node in the heap
    {
        if(ptr[i]!=NULL) 
        {
            if(!ptr[i]->mark)   // if the node's mark bit is false
            {
                //disconnect the Node
                ptr[i]->adjacent1=NULL;
                ptr[i]->adjacent2=NULL;
                ptr[i]->adjacent3=NULL;
                delete ptr[i];
                ptr[i]=NULL;
            }
        }
    }
}

void gc_marksweep(const root& r1,const root& r2,Node** heap)
{
    cout<<"=> Mark phase started"<<endl;
    mark(r1);
    mark(r2);
    cout<<"=> Marking done"<<endl;
    cout<<"=> Sweep phase started"<<endl;
    sweep(heap);
}

void print_Node(const Node* Node)   
{
    if(Node==NULL)      
    {
        return;
    }
    cout<<" "<<Node->data;      // print the data of the node
    if (Node->adjacent1!=NULL || Node->adjacent2!=NULL || Node->adjacent3!=NULL)       
    {
        cout<<"->[";
        print_Node(Node->adjacent1);
        print_Node(Node->adjacent2);
        print_Node(Node->adjacent3);
        cout<<" ]";
    }
}
void print_heap(Node** ptr)
{
    for(int i=0;i<8;i++)
    {
        if(ptr[i]!=NULL)
        {
            print_Node(ptr[i]);
            cout<<endl;
        }
    }
}
void connected_with_roots(const root& value)
{
    cout<<"root->";
    print_Node(value.point);
    cout<<endl;
}

int main()
{
    root root1, root2;
    initialize(root1,root2);
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Simulation for Mark and Sweep Garbage Collector\n";
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Initial heap"<<endl;
    print_heap(heap);
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Heap connected to the roots is: "<<endl;
    connected_with_roots(root1);
    connected_with_roots(root2);
    cout<<"------------------------------------"<<endl;
    gc_marksweep(root1, root2, heap);
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Garbage collector was called. The heap is now: \n";
    print_heap(heap);
    cout<<"-----------------------------------------------------"<<endl;
    cout<<"Checking if this matches heap connected to roots: \n";
    connected_with_roots(root1);
    connected_with_roots(root2);
}