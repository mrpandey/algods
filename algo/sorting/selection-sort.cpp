#include<iostream>
#include<vector>

using namespace std;

//Avg. Time Complexity: O(n^2)
//Worst Time Complexity: O(n^2)
//Extra Space Complexity: O(1)

int main(){

    vector<int> a = {46, 78, 23, 56, 12, 23, 9, 18, 4, 11};
    int n = a.size();

    //selection sort
    
    for(int i=0; i<n-1; i++){
        //a[0,..,i-1] are the first minimum i elements
        
        //select next minimum element and swap with a[i]

        //minIdx = index of min element
        int minIdx = i;

        for(int j=i+1; j<n; j++){
            if( a[j] < a[minIdx] ) minIdx=j;
        }

        int temp = a[i];
        a[i] = a[minIdx];
        a[minIdx] = temp;
    }

    for(int num:a) cout << num << " ";
    cout << endl;
}