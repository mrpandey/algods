#include<iostream>
#include<vector>

using namespace std;

//T(n) = time complexity of mergeSort of vector of length a
//T(n) = 2T(n/2) + cn
//Avg Time complexity: O(nlogn)
//Worst Time complexity: O(nlogn)
//Extra Space Complexity: O(n)

vector<int> mergeSort(vector<int> a){
    int n = a.size();
    if(n<2) return a;

    //sort the left half recursively
    vector<int> left = mergeSort( vector<int>( a.begin(), a.begin()+n/2 ) );
    //sort the right half recursively
    vector<int> right = mergeSort( vector<int>( a.begin()+n/2, a.end() ) );

    //merge the sorted halves
    int i=0, j=0, k=0;
    for(; i<n && j<left.size() && k<right.size(); i++){
        if(left[j]<right[k]) a[i] = left[j++];
        else a[i] = right[k++];
    }

    while(j<left.size()) a[i++] = left[j++];
    while(k<right.size()) a[i++] = right[k++];

    //merge complete

    return a;
}

int main(){
    
    vector<int> a = {23, 43, 18, 8, 4, 12, 34, 20, 15, 33};
    int n = a.size();

    vector<int> b = mergeSort(a);

    for(int num:b) cout << num << " ";
    cout << endl;
}