// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<random>
#define ll long long 
// Constructor
SortTool::SortTool() {}
using namespace std;

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int key = 0;
    int i=0;
    for(int j=1; j<data.size(); j++) {
        key = data[j];
        i = j-1;
        while(i>=0 && data[i]>key) {
            data[i+1] = data[i];
            i--;
        }
        data[i+1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
        QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(flag == 0) {
        if(low < high) {
            int part;
            part = Partition(data, low, high);
            QuickSortSubVector(data, low, part-1, flag);
            QuickSortSubVector(data, part+1, high, flag);
        }
    }
    else {
        if(low < high) {
            int part;
            part = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, part-1, flag);
            QuickSortSubVector(data, part+1, high, flag);
        }
    }
}

int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // TODO : Please complete the function
    int i = rand()%(high-low+1) + low;
    int tmp = data[high];
    data[high] = data[i];
    data[i] = tmp;
    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int pivot = data[high];
    int i = low - 1;
    int tmp;
    for(int j = low; j<high; j++) {
        if(data[j] < pivot) {
            i++;
            tmp = data[j];
            data[j] = data[i];
            data[i] = tmp;
        }
    }
    tmp = data[high];
    data[high] = data[i+1];
    data[i+1] = tmp;
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if((high-low)>=1) {
        int mid = (low+high)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, mid+1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1 = middle1 - low + 1;
    int n2 = high - middle2 + 1;
    vector<int> left;
    vector<int> right;
    int leftIndex = 0;
    int rightIndex = 0;

    for(int i=0; i<n1; i++) {
        left.push_back(data[low+i]);
    }
    for(int j=0; j<n2; j++) {
        right.push_back(data[middle2+j]);
    }

    for(int k=low; k<=high; k++) {
        if(leftIndex<n1 && rightIndex<n2) {
            if(left[leftIndex]<=right[rightIndex]) {
                data[k] = left[leftIndex];
                leftIndex++;
            }
            else {
                data[k] = right[rightIndex];
                rightIndex++;
            }
        }
        else {
            if(leftIndex<n1) {
                data[k] = left[leftIndex];
                leftIndex++;
            }
            else {
                data[k] = right[rightIndex];
                rightIndex++;
            }
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = root * 2 + 1;
    int right = root * 2 + 2;
    int largest = root;
    if(left < heapSize && data[left] > data[largest]) {
        largest = left;
    }
    if(right < heapSize && data[right] > data[largest]) {
        largest = right;
    }
    if(largest != root) {
        int tmp = data[root];
        data[root] = data[largest];
        data[largest] = tmp;
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i=heapSize/2 - 1; i>=0; i--) {
        MaxHeapify(data, i);
    }
}
