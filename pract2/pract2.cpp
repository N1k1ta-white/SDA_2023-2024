#include <iostream>
#include <vector>

typedef std::vector<int> vector;

int merge(vector& arr, vector& temp, int l, int mid, int r) {
    int p1 = l, p2 = mid, k = l, counter = 0;
    while(p1 < mid && p2 <= r) {
        if(arr[p1] > arr[p2]){
            temp[k++] = arr[p2++];
            counter += mid - p1;
        }
        else
            temp[k++] = arr[p1++];
    }
    while(p1 < mid) {
        temp[k++] = arr[p1++];
    }
    while(p2 <= r) {
        temp[k++] = arr[p1++];
    }
    for(int i = l ; i <= r;i++){
        arr[i] = temp[i];
    }
    return counter;
}

int mergeSortCountInversion(vector& arr, vector& temp, int l, int r) {
    int counter = 0;
    int mid = (l + r) / 2;
    counter += mergeSortCountInversion(arr, temp, l, mid);
    counter += mergeSortCountInversion(arr, temp, mid, r);
    counter += merge(arr, temp, l, mid, r);
    return counter;
}


int main() {

}
