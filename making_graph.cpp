#include <iostream>
#include <vector>
#include <cstdio>
#include <random>
#include <ctime>

using namespace std;

// int* unsorted_array_generator(int num_integers,int random_seed){
//     mt19937 gen(random_seed);
//     int lower_bound = 0;
//     int upper_bound = 15000;
//     uniform_int_distribution<> dis(lower_bound, upper_bound); 
//     int* arr_pointer=new int[num_integers];
//     for(int i=0;i<num_integers;i++){
//         arr_pointer[i]=dis(gen);
//     }
//     return arr_pointer;
// }

int* unsorted_array_generator(int num_integers,int random_seed){
    int* arr_pointer=new int[num_integers];
    for(int i=0;i<num_integers;i++){
        arr_pointer[i]=i;
    }
    return arr_pointer;
}

int ceiling_division(int a, int b) { //converts 2.34 to 3
    return (a + b - 1) / b;
}

int Partition(int* arr,int start,int end,int pivot_index){
    int x;
    int pivot=arr[pivot_index];
    int pIndex=start;
    //swapping
    x = arr[pivot_index];
    arr[pivot_index] = arr[end];
    arr[end] = x;
    for(int i=start;i<end;i++){
        if(arr[i]<pivot){
            //swaping
            x=arr[i];
            arr[i]=arr[pIndex];
            arr[pIndex]=x;
            pIndex++;
        }
    }
    //swaping
    x=arr[pIndex];
    arr[pIndex]=arr[end];
    arr[end]=x;
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

// //subarray of 3
// int median_of_medians_3(int* arr,int start,int end){
//     int length=end-start+1;
//     if(length<=3){
//         Simple_QuickSort(arr,0,length-1);
//         return arr[start+(length-1)/2];
//     }
//     int num_subarrays=ceiling_division(length,3);
//     int* medians_array=new int[num_subarrays];
//     for(int i=0;i<num_subarrays-1;i++){
//         int* temp=new int[3];
//         for(int j=0;j<3;j++){
//             temp[j]=arr[start+i*3+j];
//         }
//         Simple_QuickSort(temp,0,2);
//         medians_array[i]=temp[1];
//     }
//     int last_length=end-start-(num_subarrays-1)*3+1;
//     int* temp=new int[last_length];
//     for(int j=0;j<last_length;j++){
//         temp[j]=arr[start+(num_subarrays-1)*3+j];
//     }
//     if(last_length!=0){
//         Simple_QuickSort(temp,0,end-start-(num_subarrays-1)*3);
//         medians_array[num_subarrays-1]=temp[(last_length-1)/2];
//     }
//     int median_of_medians=median_of_medians_3(medians_array,0,num_subarrays-1);
//     return median_of_medians;
// }

int median_of_medians_3(int* arr, int start, int end) {
    int length = end - start + 1;
    if (length <= 3) {
        Simple_QuickSort(arr, start, end); // Use Simple_QuickSort to sort the small array
        return arr[start + (length - 1) / 2]; // Return the median
    }

    int num_subarrays = ceiling_division(length, 3);
    int* medians_array = new int[num_subarrays];

    // Compute medians of each subarray
    for (int i = 0; i < num_subarrays - 1; ++i) {
        int* temp = new int[3];
        for (int j = 0; j < 3; ++j) {
            temp[j] = arr[start + i * 3 + j];
        }
        Simple_QuickSort(temp, 0, 2);
        medians_array[i] = temp[1]; // Median of 7 elements is the 4th element (index 3)
        delete[] temp; // Free memory
    }

    // Handle the last subarray
    int last_length = end - start - (num_subarrays - 1) * 3 + 1;
    int* temp = new int[last_length];
    for (int j = 0; j < last_length; ++j) {
        temp[j] = arr[start + (num_subarrays - 1) * 3 + j];
    }

    if (last_length != 0) {
        Simple_QuickSort(temp, 0, last_length - 1);
        medians_array[num_subarrays - 1] = temp[(last_length - 1) / 2];
    }
    delete[] temp; // Free memory

    // Recursively find the median of medians
    int median_of_medians = median_of_medians_3(medians_array, 0, num_subarrays - 1);
    delete[] medians_array; // Free memory

    return median_of_medians;
}

// //subarray of 3
// int median_of_medians_3(int* arr,int start,int end){
//     int length=end-start+1;
//     if(length<=3){
//         Simple_QuickSort(arr,0,length-1);
//         return arr[start+(length-1)/2];
//     }
//     int num_subarrays=ceiling_division(length,3);
//     int* medians_array=new int[num_subarrays];
//     for(int i=0;i<num_subarrays-1;i++){
//         // int* temp=new int[5];
//         // for(int j=0;j<5;j++){
//         //     temp[j]=arr[start+i*5+j];
//         // }
//         Simple_QuickSort(arr,3*i+start,3*i+start+2);
//         medians_array[i]=arr[3*i+start+1];
//     }
//     int last_length=end-start-(num_subarrays-1)*3+1;
//     // int* temp=new int[last_length];
//     // for(int j=0;j<last_length;j++){
//     //     temp[j]=arr[start+(num_subarrays-1)*5+j];
//     // }
//     if(last_length!=0){
//         Simple_QuickSort(arr,start+(num_subarrays-1)*3,start+(num_subarrays-1)*3+last_length-1);
//         medians_array[num_subarrays-1]=arr[start+(num_subarrays-1)*3+(last_length-1)/2];
//     }
//     int median_of_medians=median_of_medians_3(medians_array,0,num_subarrays-1);
//     // cout<<median_of_medians<<endl;
//     return median_of_medians;
// }

// //subarray of 5
// int median_of_medians_5(int* arr,int start,int end){
//     int length=end-start+1;
//     if(length<=5){
//         Simple_QuickSort(arr,0,length-1);
//         return arr[start+(length-1)/2];
//     }
//     int num_subarrays=ceiling_division(length,5);
//     int* medians_array=new int[num_subarrays];
//     for(int i=0;i<num_subarrays-1;i++){
//         // int* temp=new int[5];
//         // for(int j=0;j<5;j++){
//         //     temp[j]=arr[start+i*5+j];
//         // }
//         Simple_QuickSort(arr,5*i+start,5*i+start+4);
//         medians_array[i]=arr[5*i+start+2];
//     }
//     int last_length=end-start-(num_subarrays-1)*5+1;
//     // int* temp=new int[last_length];
//     // for(int j=0;j<last_length;j++){
//     //     temp[j]=arr[start+(num_subarrays-1)*5+j];
//     // }
//     if(last_length!=0){
//         Simple_QuickSort(arr,start+(num_subarrays-1)*5,start+(num_subarrays-1)*5+last_length-1);
//         medians_array[num_subarrays-1]=arr[start+(num_subarrays-1)*5+(last_length-1)/2];
//     }
//     int median_of_medians=median_of_medians_5(medians_array,0,num_subarrays-1);
//     // cout<<median_of_medians<<endl;
//     return median_of_medians;
// }
// //subaray of 5
// int median_of_medians_5(int* arr,int start,int end){
//     int length=end-start+1;
//     if(length<=5){
//         Simple_QuickSort(arr,0,length-1);
//         return arr[start+(length-1)/2];
//     }
//     int num_subarrays=ceiling_division(length,5);
//     int* medians_array=new int[num_subarrays];
//     for(int i=0;i<num_subarrays-1;i++){
//         int* temp=new int[5];
//         for(int j=0;j<5;j++){
//             temp[j]=arr[start+i*5+j];
//         }
//         Simple_QuickSort(temp,0,4);
//         medians_array[i]=temp[2];
//     }
//     int last_length=end-start-(num_subarrays-1)*5+1;
//     int* temp=new int[last_length];
//     for(int j=0;j<last_length;j++){
//         temp[j]=arr[start+(num_subarrays-1)*5+j];
//     }
//     if(last_length!=0){
//         Simple_QuickSort(temp,0,end-start-(num_subarrays-1)*5);
//         medians_array[num_subarrays-1]=temp[(last_length-1)/2];
//     }
//     int median_of_medians=median_of_medians_5(medians_array,0,num_subarrays-1);
//     return median_of_medians;
// }
int median_of_medians_5(int* arr, int start, int end) {
    int length = end - start + 1;
    if (length <= 5) {
        Simple_QuickSort(arr, start, end);
        return arr[start + (length - 1) / 2];
    }

    int num_subarrays = ceiling_division(length, 5);
    int* medians_array = new int[num_subarrays];

    // Compute medians of each subarray
    for (int i = 0; i < num_subarrays - 1; ++i) {
        int* temp = new int[5];
        for (int j = 0; j < 5; ++j) {
            temp[j] = arr[start + i * 5 + j];
        }
        Simple_QuickSort(temp, 0, 4);
        medians_array[i] = temp[2];
        delete[] temp; // Free memory
    }

    // Handle the last subarray
    int last_length = end - start - (num_subarrays - 1) * 5 + 1;
    int* temp = new int[last_length];
    for (int j = 0; j < last_length; ++j) {
        temp[j] = arr[start + (num_subarrays - 1) * 5 + j];
    }

    if (last_length != 0) {
        Simple_QuickSort(temp, 0, last_length - 1);
        medians_array[num_subarrays - 1] = temp[(last_length - 1) / 2];
    }
    delete[] temp; // Free memory

    // Recursively find the median of medians
    int median_of_medians = median_of_medians_5(medians_array, 0, num_subarrays - 1);
    delete[] medians_array; // Free memory

    return median_of_medians;
}
// subarray of 7
// int median_of_medians_7(int* arr,int start,int end){
//     int length=end-start+1;
//     if(length<=7){
//         Simple_QuickSort(arr,0,length-1);
//         return arr[start+(length-1)/2];
//     }
//     int num_subarrays=ceiling_division(length,7);
//     int* medians_array=new int[num_subarrays];
//     for(int i=0;i<num_subarrays-1;i++){
//         // int* temp=new int[5];
//         // for(int j=0;j<5;j++){
//         //     temp[j]=arr[start+i*5+j];
//         // }
//         Simple_QuickSort(arr,7*i+start,7*i+start+6);
//         medians_array[i]=arr[7*i+start+3];
//     }
//     int last_length=end-start-(num_subarrays-1)*7+1;
//     // int* temp=new int[last_length];
//     // for(int j=0;j<last_length;j++){
//     //     temp[j]=arr[start+(num_subarrays-1)*5+j];
//     // }
//     if(last_length!=0){
//         Simple_QuickSort(arr,start+(num_subarrays-1)*7,start+(num_subarrays-1)*7+last_length-1);
//         medians_array[num_subarrays-1]=arr[start+(num_subarrays-1)*7+(last_length-1)/2];
//     }
//     int median_of_medians=median_of_medians_7(medians_array,0,num_subarrays-1);
//     // cout<<median_of_medians<<endl;
//     return median_of_medians;
// }
// //subarray of 7 
// int median_of_medians_7(int* arr,int start,int end){
//     int length=end-start+1;
//     if(length<=7){
//         Simple_QuickSort(arr,0,length-1);
//         return arr[start+(length-1)/2];
//     }
//     int num_subarrays=ceiling_division(length,7);
//     int* medians_array=new int[num_subarrays];
//     for(int i=0;i<num_subarrays-1;i++){
//         int* temp=new int[7];
//         for(int j=0;j<7;j++){
//             temp[j]=arr[start+i*7+j];
//         }
//         Simple_QuickSort(temp,0,6);
//         medians_array[i]=temp[3];
//     }
//     int last_length=end-start-(num_subarrays-1)*7+1;
//     int* temp=new int[last_length];
//     for(int j=0;j<last_length;j++){
//         temp[j]=arr[start+(num_subarrays-1)*7+j];
//     }
//     if(last_length!=0){
//         Simple_QuickSort(temp,0,end-start-(num_subarrays-1)*7);
//         medians_array[num_subarrays-1]=temp[(last_length-1)/2];
//     }
//     int median_of_medians=median_of_medians_7(medians_array,0,num_subarrays-1);
//     return median_of_medians;
// }
int median_of_medians_7(int* arr, int start, int end) {
    int length = end - start + 1;
    if (length <= 7) {
        Simple_QuickSort(arr, start, end); // Use Simple_QuickSort to sort the small array
        return arr[start + (length - 1) / 2]; // Return the median
    }

    int num_subarrays = ceiling_division(length, 7);
    int* medians_array = new int[num_subarrays];

    // Compute medians of each subarray
    for (int i = 0; i < num_subarrays - 1; ++i) {
        int* temp = new int[7];
        for (int j = 0; j < 7; ++j) {
            temp[j] = arr[start + i * 7 + j];
        }
        Simple_QuickSort(temp, 0, 6);
        medians_array[i] = temp[3]; // Median of 7 elements is the 4th element (index 3)
        delete[] temp; // Free memory
    }

    // Handle the last subarray
    int last_length = end - start - (num_subarrays - 1) * 7 + 1;
    int* temp = new int[last_length];
    for (int j = 0; j < last_length; ++j) {
        temp[j] = arr[start + (num_subarrays - 1) * 7 + j];
    }

    if (last_length != 0) {
        Simple_QuickSort(temp, 0, last_length - 1);
        medians_array[num_subarrays - 1] = temp[(last_length - 1) / 2];
    }
    delete[] temp; // Free memory

    // Recursively find the median of medians
    int median_of_medians = median_of_medians_7(medians_array, 0, num_subarrays - 1);
    delete[] medians_array; // Free memory

    return median_of_medians;
}
int find_pivot_index(int* arr,int start,int end,int mom){
    //linear search
    for(int i=start;i<=end;i++){
        if(arr[i]==mom){
            return i;
        }
    }
    cout<<"wtf??"<<endl;
    return -1; //failed
}


void QuickSort_3(int* arr,int start,int end){
    if(start>=end){
        return;
    }
    int mom=median_of_medians_3(arr,start,end);
    // cout<<mom<<endl;
    int pivot_index=find_pivot_index(arr,start,end,mom);
    int Pindex=Partition(arr,start,end,pivot_index);
    QuickSort_3(arr,start,Pindex-1);
    QuickSort_3(arr,Pindex+1,end);
}


void QuickSort_5(int* arr,int start,int end){
    if(start>=end){
        return;
    }
    int mom=median_of_medians_5(arr,start,end);
    int pivot_index=find_pivot_index(arr,start,end,mom);
    int Pindex=Partition(arr,start,end,pivot_index);
    QuickSort_5(arr,start,Pindex-1);
    QuickSort_5(arr,Pindex+1,end);
}

void QuickSort_7(int* arr,int start,int end){
    if(start>=end){
        return;
    }
    int mom=median_of_medians_7(arr,start,end);
    int pivot_index=find_pivot_index(arr,start,end,mom);
    int Pindex=Partition(arr,start,end,pivot_index);
    QuickSort_7(arr,start,Pindex-1);
    QuickSort_7(arr,Pindex+1,end);
}

void Print_arr(int* arr,int start,int end){
    for(int i=start;i<=end;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}
void plotSingleVector_quicksort_simple(const std::vector<double>& vector_1) {
    // Open a pipe to GNUplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error: Could not open pipe to GNUplot." << std::endl;
        return;
    }

    // Write GNUplot commands to the pipe
    fprintf(gnuplotPipe, "set terminal pngcairo\n");
    fprintf(gnuplotPipe, "set output 'quicksort_endpivot.png'\n");
    fprintf(gnuplotPipe, "set title 'quicksort with end pivot'\n");
    fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time'\n");
    fprintf(gnuplotPipe, "plot '-' with lines title 'Vector 1'\n");

    // Write vector_1 data to GNUplot
    for (size_t i = 0; i < vector_1.size(); ++i) {
        fprintf(gnuplotPipe, "%zu %f\n", i + 2, vector_1[i]); // x = i + 2
    }
    fprintf(gnuplotPipe, "e\n"); // End of data

    // Close the pipe
    pclose(gnuplotPipe);
}

void plotSingleVector_quicksort_3(const std::vector<double>& vector_1) {
    // Open a pipe to GNUplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error: Could not open pipe to GNUplot." << std::endl;
        return;
    }

    // Write GNUplot commands to the pipe
    fprintf(gnuplotPipe, "set terminal pngcairo\n");
    fprintf(gnuplotPipe, "set output 'quicksort_3.png'\n");
    fprintf(gnuplotPipe, "set title 'quick sort with median of medians sub array size 3'\n");
    fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time'\n");
    fprintf(gnuplotPipe, "plot '-' with lines title 'Vector 1'\n");

    // Write vector_1 data to GNUplot
    for (size_t i = 0; i < vector_1.size(); ++i) {
        fprintf(gnuplotPipe, "%zu %f\n", i + 2, vector_1[i]); // x = i + 2
    }
    fprintf(gnuplotPipe, "e\n"); // End of data

    // Close the pipe
    pclose(gnuplotPipe);
}

void plotSingleVector_quicksort_5(const std::vector<double>& vector_1) {
    // Open a pipe to GNUplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error: Could not open pipe to GNUplot." << std::endl;
        return;
    }

    // Write GNUplot commands to the pipe
    fprintf(gnuplotPipe, "set terminal pngcairo\n");
    fprintf(gnuplotPipe, "set output 'quicksort_5.png'\n");
    fprintf(gnuplotPipe, "set title 'quick sort with median of medians sub array size 5'\n");
    fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time'\n");
    fprintf(gnuplotPipe, "plot '-' with lines title 'Vector 1'\n");

    // Write vector_1 data to GNUplot
    for (size_t i = 0; i < vector_1.size(); ++i) {
        fprintf(gnuplotPipe, "%zu %f\n", i + 2, vector_1[i]); // x = i + 2
    }
    fprintf(gnuplotPipe, "e\n"); // End of data

    // Close the pipe
    pclose(gnuplotPipe);
}

void plotSingleVector_quicksort_7(const std::vector<double>& vector_1) {
    // Open a pipe to GNUplot
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (!gnuplotPipe) {
        std::cerr << "Error: Could not open pipe to GNUplot." << std::endl;
        return;
    }

    // Write GNUplot commands to the pipe
    fprintf(gnuplotPipe, "set terminal pngcairo\n");
    fprintf(gnuplotPipe, "set output 'quicksort_7.png'\n");
    fprintf(gnuplotPipe, "set title 'quick sort with median of medians sub array size 7'\n");
    fprintf(gnuplotPipe, "set xlabel 'Array Size'\n");
    fprintf(gnuplotPipe, "set ylabel 'Time'\n");
    fprintf(gnuplotPipe, "plot '-' with lines title 'Vector 1'\n");

    // Write vector_1 data to GNUplot
    for (size_t i = 0; i < vector_1.size(); ++i) {
        fprintf(gnuplotPipe, "%zu %f\n", i + 2, vector_1[i]); // x = i + 2
    }
    fprintf(gnuplotPipe, "e\n"); // End of data

    // Close the pipe
    pclose(gnuplotPipe);
}

int main() {
    int* unsorted_arr;
    clock_t start;
    clock_t end;
    vector<double> simple_quick_sort_time={};
    vector<double> quick_sort_time_3={};
    vector<double> quick_sort_time_5={};
    vector<double> quick_sort_time_7={};
    double duration;
    int x=6455;
    int u=6455;
    for(int i=2;i<=x+5;i++){
        cout<<i<<endl;
        unsorted_arr=unsorted_array_generator(i,42);
        //unsorted
        start=clock();
        Simple_QuickSort(unsorted_arr,0,i-1);
        end=clock();
        duration = double(end - start) / CLOCKS_PER_SEC;
        simple_quick_sort_time.push_back(duration);
        for(int j=0;j<i-1;j++){
            if(unsorted_arr[j]>unsorted_arr[j+1]){
                cout<<"wtf"<<endl;
                return 0;
            }
        }
        // start=clock();
        // answer_arr=InsertionSort(unsorted_arr,i);
        // end=clock();
        // duration = double(end - start) / CLOCKS_PER_SEC;
        // insertion_sort_time.push_back(duration);
        // start=clock();
        // answer_arr=SelectionSort(unsorted_arr,i);
        // end=clock();
        // duration = double(end - start) / CLOCKS_PER_SEC;
        // selection_sort_time.push_back(duration);
        // start=clock();
        // answer_arr=MergeSort(unsorted_arr,i);
        // end=clock();
        // duration = double(end - start) / CLOCKS_PER_SEC;
        // merge_sort_time.push_back(duration);
        // start=clock();
        // QuickSort(unsorted_arr,0,i-1);
        // end=clock();
        // duration = double(end - start) / CLOCKS_PER_SEC;
        // quick_sort_time.push_back(duration);
        // delete[] answer_arr;
    }
    cout<<"Bubble sort time:"<<simple_quick_sort_time[x]<<endl;
    // Plot the vector
    plotSingleVector_quicksort_simple(simple_quick_sort_time);

    for(int i=2;i<=x+5;i++){
        cout<<i<<endl;
        unsorted_arr=unsorted_array_generator(i,42);
        // for(int j=0;j<i;j++){
        //     cout<<unsorted_arr[j]<<" ";
        // }
        // cout<<endl;
        //unsorted
        start=clock();
        QuickSort_3(unsorted_arr,0,i-1);
        end=clock();
        duration = double(end - start) / CLOCKS_PER_SEC;
        quick_sort_time_3.push_back(duration);
        // for(int j=0;j<i;j++){
        //     cout<<unsorted_arr[j]<<" ";
        // }
        // cout<<endl;
        for(int j=0;j<i-1;j++){
            if(unsorted_arr[j]>unsorted_arr[j+1]){
                cout<<"wtf"<<endl;
                return 0;
            }
        }
    }
    cout<<"insertion sort time:"<<quick_sort_time_3[x]<<endl;
    plotSingleVector_quicksort_3(quick_sort_time_3);

    // for(int i=2;i<=x+5;i++){
    //     cout<<i<<endl;
    //     int* answer_arr=new int[i];
    //     sorted_arr=sorted_array_generator(i);
    //     unsorted_arr=unsorted_array_generator(i,42);
    //     //unsorted
    //     start=clock();
    //     answer_arr=SelectionSort(unsorted_arr,i);
    //     end=clock();
    //     duration = double(end - start) / CLOCKS_PER_SEC;
    //     selection_sort_time.push_back(duration);
    // }
    // cout<<"selection sort time:"<<selection_sort_time[x]<<endl;
    // plotSingleVector_selection_unsorted(insertion_sort_time);

    for(int i=2;i<=u+5;i++){
        cout<<i<<endl;
        unsorted_arr=unsorted_array_generator(i,42);
        //unsorted
        start=clock();
        QuickSort_5(unsorted_arr,0,i-1);
        end=clock();
        duration = double(end - start) / CLOCKS_PER_SEC;
        quick_sort_time_5.push_back(duration);
        for(int j=0;j<i-1;j++){
            if(unsorted_arr[j]>unsorted_arr[j+1]){
                cout<<"wtf"<<endl;
                return 0;
            }
        }
    }
    cout<<"merge sort time:"<<quick_sort_time_5[u]<<endl;
    plotSingleVector_quicksort_5(quick_sort_time_5);

    for(int i=2;i<=u+5;i++){
        cout<<i<<endl;
        unsorted_arr=unsorted_array_generator(i,42);
        // if(i==7){
        //     cout<<unsorted_arr[0]<<" "<<unsorted_arr[1]<<endl;
        // }
        //unsorted
        start=clock();
        QuickSort_7(unsorted_arr,0,i-1);
        end=clock();
        duration = double(end - start) / CLOCKS_PER_SEC;
        quick_sort_time_7.push_back(duration);
        for(int j=0;j<i-1;j++){
            if(unsorted_arr[j]>unsorted_arr[j+1]){
                cout<<"wtf"<<endl;
                return 0;
            }
        }
    }
    cout<<"quick sort time:"<<quick_sort_time_7[u]<<endl;
    plotSingleVector_quicksort_7(quick_sort_time_7);

    // bubble_sort_time={};
    // insertion_sort_time={};
    // selection_sort_time={};
    // merge_sort_time={};
    // quick_sort_time={};

    // for(int i=2;i<=x+5;i++){
    //     cout<<i<<endl;
    //     int* answer_arr=new int[i];
    //     sorted_arr=sorted_array_generator(i);
    //     //unsorted
    //     start=clock();
    //     answer_arr=BubbleSort(sorted_arr,i);
    //     end=clock();
    //     duration = double(end - start) / CLOCKS_PER_SEC;
    //     bubble_sort_time.push_back(duration);
    //     // start=clock();
    //     // answer_arr=InsertionSort(unsorted_arr,i);
    //     // end=clock();
    //     // duration = double(end - start) / CLOCKS_PER_SEC;
    //     // insertion_sort_time.push_back(duration);
    //     // start=clock();
    //     // answer_arr=SelectionSort(unsorted_arr,i);
    //     // end=clock();
    //     // duration = double(end - start) / CLOCKS_PER_SEC;
    //     // selection_sort_time.push_back(duration);
    //     // start=clock();
    //     // answer_arr=MergeSort(unsorted_arr,i);
    //     // end=clock();
    //     // duration = double(end - start) / CLOCKS_PER_SEC;
    //     // merge_sort_time.push_back(duration);
    //     // start=clock();
    //     // QuickSort(unsorted_arr,0,i-1);
    //     // end=clock();
    //     // duration = double(end - start) / CLOCKS_PER_SEC;
    //     // quick_sort_time.push_back(duration);
    //     // delete[] answer_arr;
    // }
    // cout<<"Bubble sort time:"<<bubble_sort_time[x]<<endl;
    // // Plot the vector
    // plotSingleVector_bubble_sorted(bubble_sort_time);

    // for(int i=2;i<=x+5;i++){
    //     cout<<i<<endl;
    //     int* answer_arr=new int[i];
    //     sorted_arr=sorted_array_generator(i);
    //     //unsorted
    //     start=clock();
    //     answer_arr=InsertionSort(sorted_arr,i);
    //     end=clock();
    //     duration = double(end - start) / CLOCKS_PER_SEC;
    //     insertion_sort_time.push_back(duration);
    // }
    // cout<<"insertion sort time:"<<insertion_sort_time[x]<<endl;
    // plotSingleVector_insertion_sorted(insertion_sort_time);

    // for(int i=2;i<=x+5;i++){
    //     cout<<i<<endl;
    //     int* answer_arr=new int[i];
    //     sorted_arr=sorted_array_generator(i);
    //     //unsorted
    //     start=clock();
    //     answer_arr=SelectionSort(sorted_arr,i);
    //     end=clock();
    //     duration = double(end - start) / CLOCKS_PER_SEC;
    //     selection_sort_time.push_back(duration);
    // }
    // cout<<"selection sort time:"<<selection_sort_time[x]<<endl;
    // plotSingleVector_selection_sorted(insertion_sort_time);

    // for(int i=2;i<=u+5;i++){
    //     cout<<i<<endl;
    //     int* answer_arr=new int[i];
    //     sorted_arr=sorted_array_generator(i);
    //     //unsorted
    //     start=clock();
    //     answer_arr=MergeSort(sorted_arr,i);
    //     end=clock();
    //     duration = double(end - start) / CLOCKS_PER_SEC;
    //     merge_sort_time.push_back(duration);
    // }
    // cout<<"merge sort time:"<<merge_sort_time[u]<<endl;
    // plotSingleVector_merge_sorted(merge_sort_time);
    // for(int i=2;i<=u+5;i++){
    //     cout<<i<<endl;
    //     int* new_Arr=new int[i];
    //     for(int j=0;j<i;j++){
    //         new_Arr[j]=j;
    //     }
    //     // cout<<"element:"<<new_Arr[i-1]<<endl;
    //     //unsorted
    //     start=clock();
    //     QuickSort(new_Arr,0,i-1);
    //     end=clock();
    //     duration = double(end - start) / CLOCKS_PER_SEC;
    //     quick_sort_time.push_back(duration);
    //     delete[] new_Arr;
    // }
    // cout<<"quick sort time:"<<quick_sort_time[u]<<endl;
    // plotSingleVector_quick_sorted(quick_sort_time);
    return 0;
}
