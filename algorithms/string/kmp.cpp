#include<iostream>
using namespace std;

//Time Complexity: O(n+l), n=length of string, l=length of pattern
//Extra Space Complexity: O(l)

int main(){

	//t is string
	//s is pattern to search for in t
	string s, t;
	cin >> s >> t;

	int l=s.size(), n=t.size();
	if(l>n) return 0;

	//lps[i] gives length of longest proper prefix
	//of s[0..i] which is also suffix of s[0..i]
	int lps[l] = {0};

	// lps construction
	/* complexity is O(l) because:
		1. i is incremented at most l times
		2. j is incremented only when i is incremented, hence at most l increments of j
		3. since j-increments is at most l, j isn't decreaesed more than l times in total
	*/
	
	for(int j=0, i=1; i<l;){
		// lps[0..i-1] has been calculated
		// s[0...j-1] is a suffix of s[0...i-1]
		// we need to calculate lps[i]

		if(s[j]==s[i]) {
			lps[i++] = ++j;
		}
		else if(j==0){
			lps[i++] = 0;
		}
		else {
			// find next highest j such that s[0...j-1] is suffix of s[0...i-1]
			j = lps[j-1];
		}
	}

	// Searching begins
	// an alternative to following is simply find lps of s+"$"+t
	// and look for indices with lps[i]==l

	int i=0, j=0, ctr=0;
	while(i<n){
		if(s[j]==t[i]){
			i++;
			j++;
		}
		if(j==l){
			//match at i-l
			cout << i-l << " ";
			ctr++;
			j = lps[j-1];
		}
		else if(i<n && s[j]!=t[i]){
			if(j>0) j = lps[j-1];
			else i++;
		}
	}

	cout << "\n";

	//sample output:
	//s="na"
	//t="bananahibananaam"
	//2 4 10 12

	return 0;
}