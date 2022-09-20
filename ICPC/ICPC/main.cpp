#include <bits/stdc++.h>

using namespace std;

int min_cost(vector<int*>& v1, int n, int k[]) {
    int cost = 0;
    vector<int> len_arr;
    
    for (int i = 0; i<n; i++) {
        int l = k[i];
        int len_cur = l;
        int len_sub = 1;
        
        for (int j = 1; j<l; j++, len_cur--) {
            if (v1[i][j] > v1[i][j-1]) {
                len_sub++;
            } else {
                cost+=(min(len_cur, len_sub));
                len_arr.push_back(len_sub);
                len_sub = 1;
            }
        }
        
        len_arr.push_back(len_sub);
    }
    
    for (int i = 1; i<(int)len_arr.size(); i++) {
        len_arr[i] = len_arr[i] + len_arr[i-1];
        cost+=(len_arr[i]);
    }
    
    return cost;
}

int main() {
    int T; cin>>T;

    while (T) {
        int n; cin>>n;
        
        vector<int*> v1;
        int k[n];

        for (int i = 0; i<n; i++) {
            int len; cin>>len;
    
            k[i] = len;

            int *arr = (int*)malloc(sizeof(int) * len);

            for (int j = 0; j<len; j++) {
                cin>>arr[j];
            }
            
            v1.push_back(arr);
        }
        
        cout<<min_cost(v1, n, k)<<endl;
        T--;
    }
    
    return 0;
}
