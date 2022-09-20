#include <bits/stdc++.h>

using namespace std;

class queue_with_array {
private:
    int length = 0;
    int size = 4;
    int *arr;
    int start = 0;
    int end = 0;

public:
    queue_with_array() {
        arr = (int *)malloc(sizeof(int) * size); // Default length is 4.
    }

    bool pop() {
        if (length == 0)
            return false;

        if (length <= size / 4) {
            int *ptemp = (int *)malloc(sizeof(int) * size / 2);

            if (start < end) {
                for (int i = start; i < end; i++) {
                    ptemp[i - start] = arr[i];
                }
            } else {
                int index = 0;
                for (int i = start; i < size; i++) {
                    ptemp[index] = arr[i];
                    index++;
                }

                for (int i = 0; i < end; i++) {
                    ptemp[index] = arr[i];
                    index++;
                }
            }

            start = 0;
            end = length - 1;
            free(arr);
            arr = ptemp;
            size /= 2;
            length--;
            return 1;
        }

        if (start == size - 1)
            start = 0;
        else
            start++;

        length--;

        return true;
    }

    void push(int a) {
        if (length == size) {
            int *ptemp = (int *)malloc(sizeof(int) * size * 2);

            if (start < end) {
                for (int i = start; i < end; i++) {
                    ptemp[i - start] = arr[i];
                }
            } else {
                int index = 0;
                for (int i = start; i < size; i++, index++) {
                    ptemp[index] = arr[i];
                }

                for (int i = 0; i < end; i++, index++) {
                    ptemp[index] = arr[i];
                }
            }

            start = 0;
            end = length;
            free(arr);
            arr = ptemp;
            size *= 2;
        }

        arr[end] = a;
        length++;

        if (end == size - 1) {
            end = 0;
        } else {
            end++;
        }
    }

    int top() {
        if (length == 0)
            return -1;
        return arr[start];
    }

    bool empty() {
        return length;
    }

    ~queue_with_array() {
        free(arr);
    }
};

int main() {
    queue_with_array q1;
    
    while (1) {
        cout<<"Enter 1 to insert age\n";
        cout<<"Enter 2 to view the top element\n";
        cout<<"Enter 3 to pop age\n";
        cout<<"Enter 4 to exit\n";
        
        cout<<"WARNING: If you want to see the top of the queue and pop the element then you have to use command 2 and then command 3\n";
        
        char ip; cin>>ip;
        
        if (ip == '1') {
            cout<<"Enter age\n";
            int a; cin>>a;
            
            q1.push(a);
            cout<<"Element added\n\n";
        } else if (ip == '2') {
            if (q1.top() == -1) {
                cout<<"The queue is empty\n";
            } else {
                cout<<"Element at the top is: "<<q1.top()<<endl;
            }
            cout<<endl;
        } else if (ip == '3') {
            if (!q1.pop()) {
                cout<<"The queue is empty\n\n";
            } else {
                cout<<"Element popped\n\n";
            }
        } else if (ip == '4') {
            break;
        }
    }
    
    return 0;
}
