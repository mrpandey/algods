#include<iostream>
#include<vector>

using namespace std;

//Avg. Time Complexity: O(n^2)
//Worst Time Complexity: O(n^2)
//Extra Space Complexity: O(1)

//although same complexity, but insertion sort
//performs better than selection and bubble sorts

int main(){

    vector<int> a = {34, 21, 45, 67, 23, 8, 12, 5, 40};
    int n = a.size();

    //insertion sort
    
    for(int i=1; i<n; i++){
        //subarray a[0,..,i-1] is already sorted
        //insert a[i] to its right place in this subarray

        int j=i-1, temp=a[i];

        //shift greater elements
        while(j>=0 && a[j]>temp){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = temp;
    }

    for(int num:a) cout << num << " ";
    cout << endl;
}