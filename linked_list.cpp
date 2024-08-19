#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;
public:
    Node(int data,Node* next){
        this->data=data;
        this->next=next;
    }
public:
    Node(int data){
        this->data=data;
        this->next=nullptr;
    }
};


int find_length_LL(Node* head_node){
    int length=1;
    Node* temp=head_node;
    while(temp->next!=nullptr){
        temp=temp->next;
        length+=1;
    }
    return length;
}

void add_element_LL(Node** head_node,int data){
    Node* actual_head_node=*head_node;
    Node* new_node=new Node(data);
    Node* mover=actual_head_node;
    while(mover->next!=nullptr){
        mover=mover->next;
    }
    mover->next=new_node;
}

Node* Split_LL(Node** head_node){
    int length=find_length_LL(*head_node);
    Node* temp=*head_node;
    for(int i=1;i<length/2;i++){
        temp=temp->next;
    }
    Node* new_start=temp->next;
    temp->next=nullptr;
    return new_start;
}

Node* Merge_LL(Node** a,Node** b){
    Node* a_mover=*a;
    Node* b_mover=*b;
    Node* result=new Node(0); //initialize
    int count=0;
    Node* head=nullptr;
    while(a_mover!=nullptr || b_mover!=nullptr){
        if(a_mover!=nullptr && b_mover!=nullptr){
            if(a_mover->data<=b_mover->data){
                Node* temp=new Node(a_mover->data,a_mover->next);
                result->next=temp;
                result=temp;
                a_mover=a_mover->next;
            }
            else{
                Node* temp=new Node(b_mover->data,b_mover->next);
                result->next=temp;
                result=temp;
                b_mover=b_mover->next;
            }
        }
        else if(a_mover==nullptr && b_mover!=nullptr){
            Node* temp=new Node(b_mover->data,b_mover->next);
            result->next=temp;
            result=temp;
            b_mover=b_mover->next;
        }
        else if(b_mover==nullptr && a_mover!=nullptr){
            Node* temp=new Node(a_mover->data,a_mover->next);
            result->next=temp;
            result=temp;
            a_mover=a_mover->next;
        }
        if(count==0){
            head=result;
        }
        count++;
    }
    return head;
}
Node* MergeSort(Node* head_node){
    int length=find_length_LL(head_node);
    if(length<=1){
        return head_node;
    }
    Node** head_node_address=&head_node;
    Node* right=Split_LL(head_node_address);
    Node* left=head_node;
    left=MergeSort(left);
    right=MergeSort(right);
    Node** left_address=&left;
    Node** right_address=&right;
    return Merge_LL(left_address,right_address);
}

Node* array_to_linked_list(int* arr,int arr_length){
    Node* head_node=new Node(arr[0]);
    Node* mover=head_node;
    for(int i=1;i<arr_length;i++){
        Node* temp=new Node(arr[i]);
        mover->next=temp;
        mover=temp;
    }
    return head_node;
}
void print_LL(Node* head_node){
    Node* mover=head_node;
    while(mover->next!=nullptr){
        cout<<mover->data<<" ";
        mover=mover->next;
    }
    cout<<mover->data<<" ";
}
int main(){
    int num_test_cases;
    int arr_length;
    int value;
    cin>>num_test_cases;
    // int* arr_lengths=new int[num_test_cases];
    for(int i=0;i<num_test_cases;i++){
        cin>>arr_length;
        cin>>value;
        Node* head_node=new Node(value);
        Node* mover=head_node;
        for(int j=1;j<arr_length;j++){
            cin>>value;
            Node* temp=new Node(value);
            mover->next=temp;
            mover=temp;
        }
        Node* result=MergeSort(head_node);
        print_LL(result);
        cout<<endl;
    }
    return 0;
}