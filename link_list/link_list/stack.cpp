#include "mylib.h"

using namespace std;

class stack_with_array {
private:
    int size = 4;
    int length = 0;
    int *arr;
    
public:
    stack_with_array() {
        arr = (int*) malloc(sizeof(int) * 4);
    }
    
    void push(int a) {
        if (length == size) {
            int *p = (int*)malloc(sizeof(int) * size * 2);
            for (int i = 0; i<length; i++) {
                p[i] = arr[i];
            }
            
            size*=2;
            free(arr);
            arr = p;
        }
        
        arr[length] = a;
        length++;
    }
    
    bool pop() {
        if (length == 0)
            return false;
        
        if (length <= size/4) {
            int *p = (int*)malloc(sizeof(int) * size/2);
            for (int i = 0; i<length; i++) {
                p[i] = arr[i];
            }
            
            size/=2;
            free(arr);
            arr = p;
        }
        
        length--;
        return 1;
    }
    
    int top() {
        if (!length)
            return NAN;
        
        return arr[length-1];
    }
    
    bool empty() {
        return length;
    }
    
    ~stack_with_array() {
        free(arr);
    }
};
 
int main() {
    cout<<"\nCode for stack implemented with array test.\n";
    stack_with_array s;
    cout<<"Pushing 1 in the stack\n";
    s.push(1);
    cout<<"Pushing 2 in the stack\n";
    s.push(2);
    cout<<"Pushing 3 in the stack\n";
    s.push(3);
    cout<<"Viewing the top of the stack\n";
    cout<<s.top()<<endl;
    cout<<"Popping from the stack\n";
    s.pop();
    cout<<"Viewing the top of the stack\n";
    cout<<s.top()<<endl;

}
