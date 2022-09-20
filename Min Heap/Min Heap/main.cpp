#include <bits/stdc++.h>

using namespace std;

void swap (int* a, int* b) {
    int c = *a;
    *a = *b;
    *b = c;
}

class min_heap {
private:
    int* arr;
    int N = 2;
    int len = 0;
    
    int left(int parent) {
        return 2*parent + 1;
    }
    
    int right(int parent) {
        return 2*parent + 2;
    }
    
    int parent(int child) {
        return (child - 1)/2;
    }
    
public:
    min_heap() {
        arr = new int[N];
        
        for (int i = 0; i<N; i++)
            arr[i] = -1;
    }
    
    int get_min() {
        return arr[0];
    }
    
    void print_BFS() {
        int l = 0;
        for (int i = 0; i<len;) {
            int j = i;
            for (; i<j + (int)pow(2, l) && i<len; i++) {
                cout<<arr[i]<<" ";
            }
            l++;
            cout<<endl;
        }
    }
    
    void make_heap(int root) {
        int l = left(root);
        int r = right(root);
        int min = root;
        
        if (l < len && arr[l] < arr[root])
            min = l;
        if (r < len && arr[r] < arr[min])
            min = r;
        if (min != root) {
            swap(&arr[root], &arr[min]);
            make_heap(min);
        }
    }
    
    void add(int a) {
        if (len == N) {
            int* p = new int[2*N];
            
            for (int i = 0; i<N; i++)
                p[i] = arr[i];
            
            for (int i = N; i<2*N; i++)
                p[i] = -1;
            
            delete arr;
            arr = p;
        }
        
        arr[len] = a;
        len++;
        
        int i = len - 1;
        
        while (arr[i] < arr[parent(i)]) {
            swap(&arr[i], &arr[parent(i)]);
            i = parent(i);
        }
    }
    
    int pop_min() {
        if (len == 0)
            return -1;
        
        int min = arr[0];
        
        if (len == 1) {
            len = 0;
            return min;
        }
        
        arr[0] = arr[len - 1];
        len--;
        make_heap(0);
        
        return min;
    }
    
    ~min_heap() {
        delete arr;
    }
};

int main() {
    min_heap h1;
    
    h1.add(6);
    h1.add(9);
    h1.add(8);
    h1.add(7);
    h1.add(2);
    h1.add(3);
    h1.add(5);
    h1.add(1);
    h1.add(4);
    h1.add(0);
    
    h1.print_BFS();
    
    return 0;
}
