    #include <bits/stdc++.h>

    using namespace std;

    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        
        int T; cin>>T;
        
        for (int t = 1; t<=T; t++) {
            int num_a; cin>>num_a;
            const int na = num_a;
            
            int num_flights; cin>>num_flights;
            int days; cin>>days;

            int *arr = (int*)calloc(na*na, sizeof(int));
            
            //cout<<"Hello 1\n";
            
    //        for (int i = 0; i < na; i++) {
    //            arr[i] = new int[na];
    //        }
            
            //cout<<"Hello 2\n";
            
            for (int i = 0; i<num_flights; i++) {
                int a1, a2, cap;
                cin>>a1>>a2>>cap;
                
                arr[na*(a1-1) + a2-1] = cap;
                arr[na*(a2-1) + a1-1] = cap;
            }
            
            //cout<<"Hello 2\n";
            
            cout<<"Case #"<<t<<": ";
            for (int i = 0; i<days; i++) {
                vector<int> conn;
                int a; cin>>a;
                int b; cin>>b;
                
                a-=1;
                b-=1;
                
                for (int i = 0; i<na; i++) {
                    if (arr[na*i + a] != 0 && arr[na*i + b] != 0) {
                        conn.push_back(i);
                    }
                }
                
                int num_pass = 2*arr[na*a + b];
                
                for (auto i : conn) {
                    int q1 = arr[na*i + a];
                    int q2 = arr[na*i + b];
                    
                    num_pass+=min(q1, q2);
                }
                
                cout<<num_pass<<" ";
            }
            
            cout<<endl;
            
            //free(arr);
        }
        
        return 0;
    }
