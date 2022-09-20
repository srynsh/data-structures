#include <bits/stdc++.h>

using namespace std;

class node {
public:
    int key = 0;
    node *next = NULL;

    node() {}
    
    node(int k) {
        key = k;
    }
    
    ~node() {}
};

class linked_list {
private:
    node *head = NULL;
    node *tail = NULL;
    
public:
    void push_back(int a) {
        node *p = tail;
        
        if (!p) {
            node *pnew = new node(a);
            head = pnew;
            tail = pnew;
            return;
        }

        p->next = new node(a);
        tail = p->next;
        return;
    }
    
    void insert_front(int a) { 
        node *pnew = new node(a);
        pnew->next = head;
        if (!tail)
            tail = pnew;
        head = pnew;
    }
    
    bool remove(int a) {
        node *p = head;
        
        if (p->key == a) {
            if (tail == head) {
                tail = NULL;
            }
            node* ptemp = head;
            head = head->next;
            delete ptemp;
            return 1;
        }
        
        while (p->next && p->next->key != a) {
            p = p->next;
        }
        
        if (!p->next) {
            cout<<"No such element exists\n";
            return 0;
        }
        
        if (p->next == tail) {
            tail = p;
        }
        node *ptemp = p->next;
        node *pnext = ptemp->next;
        delete ptemp;
        p->next = pnext;
        return 1;
    }
    
    void print() {
        node *p = head;
        while (p) {
            cout<<p->key<<" ";
            p = p->next;
        }
        cout<<endl;
    }
    
    bool is_present(int value) {
        node *p = head;
        while (p) {
            if (p->key == value)
                return 1;
            p = p->next;
        }
        
        return 0;
    }
    
    void remove_head() {
        if (!head)
            return;
        remove(head->key);
    }
    
    int head_val() {
        if (!head)
            return NAN;
        return head->key;
    } // Returns the key stored in head.
    
    bool empty() {
        if (head)
            return true;
        
        return false;
    }
    
    linked_list() {}
    
    ~linked_list() {
        node *p = head;
        tail = NULL;
        
        if (!p)
            return;
        
        while (p) {
            node* ptemp = p->next;
            delete p;
            p = ptemp;
        }
    }
};

class stack_with_ll {
private:
    linked_list l1;
    int length = 0;
    
public:
    bool pop() {
        if (length == 0)
            return 0;
        l1.remove_head();
        length--;
        return 1;
    }
    
    void push(int a) {
        l1.insert_front(a);
        length++;
    }
    
    int top() {
        if (length == 0)
            return NAN;
        return l1.head_val();
    }
    
    bool empty() {
        return length;
    }
};

class queue_with_ll {
private:
    linked_list l1;
    int length = 0;
    
public:
    void push(int a) {
        l1.push_back(a);
        
        length++;
    }
    
    bool pop() {
        if (length == 0)
            return 0;
        
        l1.remove_head();
        length--;
        
        return 1;
    }
    
    int top() {
       if (length == 0)
           return NAN;
        
        return l1.head_val();
    }
    
    bool empty() {
        return length;
    }
};
 
int main() {
    return 0;
}
