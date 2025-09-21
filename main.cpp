#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <random>
using namespace std;
using namespace std::chrono;

int container=0;

//---------------------------------------------------------------------------

//SELECTION SORT
void selectionSort(vector<int> arr, int n){
    int minValIndex=0;

    for(int i=0; i<n-1; i++){
        minValIndex=i;

        for(int j=i+1; j<n; j++) if(arr[minValIndex]>arr[j]) minValIndex=j;

        if(minValIndex!=i){
            container=arr[i];
            arr[i]=arr[minValIndex];
            arr[minValIndex]=container;
        }
    }
}


//---------------------------------------------------------------------------


//INSERTION SORT
void insertionSort(vector<int> &arr, int n){
    int currentIndex=0;

    for(int i=1; i<n; i++){
        currentIndex=i;
        container=arr[currentIndex];

        for(int j=currentIndex-1; j>=0; j--){
            if(arr[j]>arr[currentIndex]){
               arr[currentIndex]=arr[j];
               arr[j]=container;
               currentIndex=j;
            }
        }
    }
}


//---------------------------------------------------------------------------


//MERGE SORT
void mergeArrays(vector<int> &arr, int l, int m, int r){
    int lSize=m-l+1, rSize=r-m;
    vector<int> left(lSize), right(rSize);

    for(int i=0; i<lSize; i++) left[i]=arr[l+i];
    for(int j=0; j<rSize; j++) right[j]=arr[(m+1)+j];

    int lCurrent=0, rCurrent=0, arrCurrent=l;

    while(lCurrent<lSize && rCurrent<rSize){
        if(left[lCurrent]<=right[rCurrent]){
            arr[arrCurrent]=left[lCurrent];
            lCurrent++;
        }else{
            arr[arrCurrent]=right[rCurrent];
            rCurrent++;
        }
        arrCurrent++;
    }

    while(lCurrent<lSize){
        arr[arrCurrent]=left[lCurrent];
        arrCurrent++;
        lCurrent++;
    }

    while(rCurrent<rSize){
        arr[arrCurrent]=right[rCurrent];
        arrCurrent++;
        rCurrent++;
    }
}
void mergeSort(vector<int> &arr, int l, int r){
   if(l<r){
     mergeSort(arr, l, (l+r)/2);
     mergeSort(arr, (l+r)/2 + 1, r);
     mergeArrays(arr, l, (l+r)/2, r);
   }else return;
}


//---------------------------------------------------------------------------


//QUICK SORT
int findPartitionIndex(vector<int> &arr, int s, int l){
    int pivot=arr[l];
    int i=s;

    for(int j=s; j<=l-1; j++){
        if(arr[j]<=pivot){
            container=arr[j];
            arr[j]=arr[i];
            arr[i]=container;
            i++;
        }
    }

    container=arr[i];
    arr[i]=arr[l];
    arr[l]=container;

    return i;
}
void quickSort(vector<int> &arr, int s, int l){
    if(s<l){
        int p=findPartitionIndex(arr, s, l);
        quickSort(arr, s, p-1);
        quickSort(arr, p+1, l);
    }
}

//---------------------------------------------------------------------------

int main()
{
    vector<int> a, b;
    for(int i=0; i<100000; i++) a.push_back(rand()%100001);
    int n=a.size();

    b=a;
    auto s1=high_resolution_clock::now();
    selectionSort(b, n);
    auto f1=high_resolution_clock::now();

    b=a;
    auto s2=high_resolution_clock::now();
    insertionSort(b, n);
    auto f2=high_resolution_clock::now();

    b=a;
    auto s3=high_resolution_clock::now();
    mergeSort(b, 0, n-1);
    auto f3=high_resolution_clock::now();

    b=a;
    auto s4=high_resolution_clock::now();
    quickSort(b, 0, n-1);
    auto f4=high_resolution_clock::now();

    duration<double> time1=f1-s1, time2=f2-s2, time3=f3-s3, time4=f4-s4;

    cout << setprecision(5) << "selection sort runtime: " << time1.count() << '\n' << "insertion sort runtime: " << time2.count() << '\n' << "merge sort runtime: " << time3.count() << '\n' << "quick sort runtime: " << time4.count();

    return 0;
}
