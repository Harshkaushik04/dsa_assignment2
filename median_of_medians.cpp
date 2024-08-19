#include <iostream>
using namespace std;

int ceiling_division(int a, int b) { //converts 2.34 to 3
    return (a + b - 1) / b;
}

int Partition(int* arr,int start,int end,int pivot_index){
    int x;
    int pivot=arr[pivot_index];
    int pIndex=start;
    for(int i=start;i<end;i++){
        if(arr[i]<=pivot){
            //swaping
            x=arr[i];
            arr[i]=arr[pIndex];
            arr[pIndex]=x;
            pIndex++;
        }
    }
    //swaping
    x=arr[pIndex];
    arr[pIndex]=arr[pivot_index];
    arr[pivot_index]=x;
    return pIndex;
}

void Simple_QuickSort(int* arr,int start,int end){
    if(start>=end){
        return;
    }
    int pivot_index=end;
    int Pindex=Partition(arr,start,end,pivot_index);
    Simple_QuickSort(arr,start,Pindex-1);
    Simple_QuickSort(arr,Pindex+1,end);
}
//subarray of 3
int median_of_medians_3(int* arr,int start,int end){
    int length=end-start+1;
    if(length<=3){
        Simple_QuickSort(arr,0,length-1);
        return arr[start+(length-1)/2];
    }
    int num_subarrays=ceiling_division(length,3);
    int* medians_array=new int[num_subarrays];
    for(int i=0;i<num_subarrays-1;i++){
        int* temp=new int[3];
        for(int j=0;j<3;j++){
            temp[j]=arr[start+i*3+j];
        }
        Simple_QuickSort(temp,0,2);
        medians_array[i]=temp[1];
    }
    int last_length=end-start-(num_subarrays-1)*3+1;
    int* temp=new int[last_length];
    for(int j=0;j<last_length;j++){
        temp[j]=arr[start+(num_subarrays-1)*3+j];
    }
    if(last_length!=0){
        Simple_QuickSort(temp,0,end-start-(num_subarrays-1)*3);
        medians_array[num_subarrays-1]=temp[(last_length-1)/2];
    }
    int median_of_medians=median_of_medians_3(medians_array,0,num_subarrays-1);
    return median_of_medians;
}

//subarray of 5
int median_of_medians_5(int* arr,int start,int end){
    int length=end-start+1;
    if(length<=5){
        Simple_QuickSort(arr,0,length-1);
        return arr[start+(length-1)/2];
    }
    int num_subarrays=ceiling_division(length,5);
    int* medians_array=new int[num_subarrays];
    for(int i=0;i<num_subarrays-1;i++){
        int* temp=new int[5];
        for(int j=0;j<5;j++){
            temp[j]=arr[start+i*5+j];
        }
        Simple_QuickSort(temp,0,4);
        medians_array[i]=temp[2];
    }
    int last_length=end-start-(num_subarrays-1)*5+1;
    int* temp=new int[last_length];
    for(int j=0;j<last_length;j++){
        temp[j]=arr[start+(num_subarrays-1)*5+j];
    }
    if(last_length!=0){
        Simple_QuickSort(temp,0,end-start-(num_subarrays-1)*5);
        medians_array[num_subarrays-1]=temp[(last_length-1)/2];
    }
    int median_of_medians=median_of_medians_5(medians_array,0,num_subarrays-1);
    cout<<median_of_medians<<endl;
    return median_of_medians;
}

// subarray of 7
int median_of_medians_7(int* arr,int start,int end){
    int length=end-start+1;
    if(length<=7){
        Simple_QuickSort(arr,0,length-1);
        return arr[start+(length-1)/2];
    }
    int num_subarrays=ceiling_division(length,7);
    int* medians_array=new int[num_subarrays];
    for(int i=0;i<num_subarrays-1;i++){
        int* temp=new int[7];
        for(int j=0;j<7;j++){
            temp[j]=arr[start+i*7+j];
        }
        Simple_QuickSort(temp,0,6);
        medians_array[i]=temp[3];
    }
    int last_length=end-start-(num_subarrays-1)*7+1;
    int* temp=new int[last_length];
    for(int j=0;j<last_length;j++){
        temp[j]=arr[start+(num_subarrays-1)*7+j];
    }
    if(last_length!=0){
        Simple_QuickSort(temp,0,end-start-(num_subarrays-1)*7);
        medians_array[num_subarrays-1]=temp[(last_length-1)/2];
    }
    int median_of_medians=median_of_medians_7(medians_array,0,num_subarrays-1);
    return median_of_medians;
}

int find_pivot_index(int* arr,int start,int end,int mom){
    //linear search
    for(int i=start;i<=end;i++){
        if(arr[i]==mom){
            return i;
        }
    }
    return -1; //failed
}

void QuickSort_5(int* arr,int start,int end){
    if(start>=end){
        return;
    }
    int mom=median_of_medians_5(arr,start,end);
    int pivot_index=find_pivot_index(arr,start,end,mom);
    int Pindex=Partition(arr,start,end,pivot_index);
    Simple_QuickSort(arr,start,Pindex-1);
    Simple_QuickSort(arr,Pindex+1,end);
}
void Print_arr(int* arr,int start,int end){
    for(int i=start;i<=end;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int num_test_cases;
    int arr_length;
    int value;
    cin>>num_test_cases;
    // int* arr_lengths=new int[num_test_cases];
    for(int i=0;i<num_test_cases;i++){
        cin>>arr_length;
        int* arr=new int[arr_length];
        for(int j=0;j<arr_length;j++){
            cin>>value;
            arr[j]=value;
        }
        QuickSort_5(arr,0,arr_length-1);
        Print_arr(arr,0,arr_length-1);
    }
    return 0;
}