// BT20CSE056 
// JC MANJUNATH

#include<iostream>
using namespace std;

struct Node
{
    int data;       //data of node
    int count;      //count of node
    struct Node* adjacent1;     //point to first adjacent node
    struct Node* adjacent2;     //point to second adjacent node
    struct Node* adjacent3;     //point to third adjacent node
    Node(int data)       // default + parametric constructor
    {
        this->data = data;
        adjacent1=NULL;
        adjacent2=NULL;
        adjacent3=NULL;
        count=0;
    }
}; //we know at most 3 connections are present
typedef struct root_tag
{
    Node* point;
}root;

Node* heap[8];

void initialize_nodes(root& root1,root& root2)
{                                                   
    Node* temp = new Node(5);   
    heap[0]=temp;
    temp = new Node(1);
    heap[1]=temp;
    temp = new Node(2);
    heap[2]=temp;
    temp = new Node(9);
    heap[3]=temp;
    temp = new Node(10);
    heap[4]=temp;
    temp = new Node(7);
    heap[5]=temp;
    temp = new Node(8);
    heap[6]=temp;
    temp = new Node(3);
    heap[7]=temp;
    temp = NULL;

    // Creating connections and updating reference counts
    root1.point=heap[0];//root1->5        
    heap[0]->count+=1;      
    heap[0]->adjacent1=heap[1];//5->1
    heap[1]->count+=1;
    root2.point=heap[1];//root2->1
    heap[1]->count+=1;
    heap[1]->adjacent1=heap[2];//1->2
    heap[2]->count+=1;
    heap[1]->adjacent2=heap[3];//1->9
    heap[3]->count+=1;
    heap[1]->adjacent3=heap[4];//1->10
    heap[4]->count+=1;
    heap[5]->adjacent1=heap[1];//7->1
    heap[1]->count+=1;
    heap[5]->adjacent2=heap[6];//7->8
    heap[6]->count+=1;
    heap[6]->adjacent1=heap[4];//8->10
    heap[4]->count+=1;
    heap[7]->adjacent1=heap[6];//3->8
    heap[6]->count+=1;
    heap[7]->adjacent2=heap[4];//3->10
    heap[4]->count+=1;
    //connections done
}
void gc_referenceCounting(Node** ptr)   
{
    int flag=0;     //flag to check if any node is deleted
    for(int i=0;i<8;i++)        
    {
        if(ptr[i]!=NULL)        //if node is not deleted
        {
            if(ptr[i]->count==0)        //if node is not referenced
            {   
                //update reference counts of adjacent nodes as we disconnect them
                if(ptr[i]->adjacent1!=NULL)         //if first adjacent node is not null
                {
                    ptr[i]->adjacent1->count-=1;
                    ptr[i]->adjacent1=NULL;
                }
                if(ptr[i]->adjacent2!=NULL)         //if second adjacent node is not null
                {
                    ptr[i]->adjacent2->count-=1;
                    ptr[i]->adjacent2=NULL;
                }
                if(ptr[i]->adjacent3!=NULL)         //if third adjacent node is not null
                {
                    ptr[i]->adjacent3->count-=1;
                    ptr[i]->adjacent3=NULL;
                }
                delete ptr[i];      //delete the node
                ptr[i]=NULL;        //set the point to null
                flag=1;         //set flag to 1
            }
        }
    }
    if(flag)      //if reference counts were updated, call garbage collector again
    {
        gc_referenceCounting(ptr);
    }
}

void print_node(const Node* node)
{
    if(node==NULL)
    {
        return;
    }
    cout<<" "<<node->data<<"(count="<<node->count<<")";
    if (node->adjacent1!=NULL || node->adjacent2!=NULL || node->adjacent3!=NULL)
    {
        cout<<"->[";
        print_node(node->adjacent1);
        print_node(node->adjacent2);
        print_node(node->adjacent3);
        cout<<" ]";
    }
}

void print_heap(Node** ptr)
{
    for(int i=0;i<8;i++)
    {
        if(ptr[i]!=NULL)
        {
            print_node(ptr[i]);
            cout<<endl;
        }
    }
}

void connected_with_roots(const root& value)
{
    cout<<"root->";
    print_node(value.point);
    cout<<endl;
}

int main()
{
    root A,B;
    initialize_nodes(A,B);
    cout<<"---------------------------------------------------------\n";
    cout<<"Simulation of Reference Counting Garbage Collector\n";
    cout<<"---------------------------------------------------------\n";
    cout<<"Initial heap\n";
    print_heap(heap);
    cout<<"---------------------------------------------------------\n";
    cout<<"Heap connected to the roots is: "<<endl;
    connected_with_roots(A);
    connected_with_roots(B);
    cout<<"---------------------------------------------------------\n";
    gc_referenceCounting(heap);
    cout<<"Garbage collector called!!\n";
    cout<<"Heap after garbage collection\n";
    cout<<"---------------------------------------------------------\n";
    print_heap(heap);
    cout<<"Checking if this matches heap connected to roots printed below\n";
    connected_with_roots(A);
    connected_with_roots(B);
}