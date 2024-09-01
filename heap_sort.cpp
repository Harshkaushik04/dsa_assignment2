#include<iostream>
using namespace std;

class heap{
public:
    int* arr;
    int arr_length;
public:
    heap(int* arr,int arr_length){
        this->arr=arr;
        this->arr_length=arr_length;
    }
public:
    void swap(int index1,int index2){
        int x=this->arr[index1];
        this->arr[index1]=this->arr[index2];
        this->arr[index2]=x;
    }

    void delete_last_element(){
        this->arr_length--;
    }

    void heapify(int index){
        int largest=index;
        int left=2*index+1;
        int right=2*index+2;
        bool flag=false;
        if(left<this->arr_length && this->arr[left]>this->arr[largest]){
            largest=left;
            flag=true;
        }
        if(right<this->arr_length && this->arr[right]>this->arr[largest]){
            largest=right;
            flag=true;
        }
        if(flag==true){
            this->swap(index,largest);
            heapify(largest);
        }
    }
    int* sort_heap(){
        int actual_arr_length=this->arr_length;
        int* arr=new int[this->arr_length];
        for(int i=this->arr_length/2-1;i>=0;i--){
            this->heapify(i);
        }
        int count=0;
        for(int i=actual_arr_length-1;i>=0;i--){
            arr[actual_arr_length-count-1]=this->arr[0];
            this->swap(0,this->arr_length-1);
            this->delete_last_element();
            this->heapify(0);
            count++;
        }
        return arr;
    }
};
void print_arr(int* arr,int arr_length){
    for(int i=0;i<arr_length;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


int main(){
    int num_test_cases;
    int arr_length;
    int value;
    cin>>num_test_cases;
    for(int i=0;i<num_test_cases;i++){
        cin>>arr_length;
        int* arr=new int[arr_length];
        for(int j=0;j<arr_length;j++){
            cin>>value;
            arr[j]=value;
        }
        heap heap_arr=heap(arr,arr_length);
        int* sorted_arr=heap_arr.sort_heap();
        print_arr(sorted_arr,arr_length);
    }
    return 0;
}