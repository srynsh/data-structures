//
// Suryaansh Jain
// CS21BTECH11057
// Double Linked List
//

#include <bits/stdc++.h>

using namespace std;

class node {
public:
    node* next = NULL;
    node* prev = NULL;
    
    string name;
    string dept;
    char gender;
    int age;
    
    node(string n, string d, char g, int a) {
        name = n;
        dept = d;
        gender = g;
        age = a;
    }
    
    node(string n, string d, char g, int a, node* back) {
        name = n;
        dept = d;
        gender = g;
        age = a;
        prev = back;
    }
};

class d_list{
private:
    int length = 0;
    node* head = NULL;
    node* tail = NULL;
    
public:
    void push_back(string n, string d, char g, int a) {
        if (!length) {
            node* pnew = new node(n, d, g, a);
            tail = pnew;
            head = pnew;
            length++;
            return;
        }
        
        node *p = tail;
        
        node* pnew = new node(n, d, g, a, p);
        
        p->next = pnew;
        tail = pnew;
        length++;
    }
    
    void insert_front(string n, string d, char g, int a) {
        if (!length) {
            node* pnew = new node(n, d, g, a);
            tail = pnew;
            head = pnew;
            length++;
            return;
        }
        
        node *p = head;
        node* pnew = new node(n, d, g, a);
        p->prev = pnew;
        pnew->next = p;
        head = pnew;
        length++;
    }
    
    bool find(string name_of_person) {
        node* p = head;
        
        while (p) {
            if (p->name == name_of_person)
                return 1;
            
            p = p->next;
        }
        
        return 0;
    }
    
    void print() {
        node* p = head;
        
        while (p) {
            cout<<p->name<<" "<<p->age<<" "<<p->dept<<" ";
            if (p->gender == 'M')
                cout<<"male\n";
            else
                cout<<"female\n";
            
            cout<<'\n';
            
            p = p->next;
        }
        
        cout<<'\n';
    }
    
    bool remove(string name_of_person) {
        node* p = head;
        
    
        while (p) {
            if (p->name == name_of_person) {
                node* pnext = p->next;
                node* pback = p->prev;
                
                if (length == 1) {
                    head = NULL;
                    tail = NULL;
                    delete p;
                } else if (pnext && pback) {
                    delete p;
                    pnext->prev = pback;
                    pback->next = pnext;
                } else if (pnext) {
                    head = pnext;
                    pnext->prev = NULL;
                    p->next = NULL;
                    delete p;
                } else if (pback) {
                    tail = pback;
                    pback->next = NULL;
                    p->prev = NULL;
                    delete p;
                }
                
                length--;
                return 1;
            }
            
            p = p->next;
        }
        
        return 0;
    }
    
    ~d_list() {
        node *p = head;
        
        while(p) {
            node *pnext = p->next;
            pnext->prev = NULL;
            delete p;
            p = pnext;
        }
    }
};

int main() {
    d_list l1;
    
    while (1) {
        cout<<"Enter 1 to insert a factulty member in the front\n";
        cout<<"Enter 2 to insert a factulty member in the back\n";
        cout<<"Enter 3 to search for a factulty member\n";
        cout<<"Enter 4 to delete a factulty member\n";
        cout<<"Enter 5 to print the list of factulty members\n";
        cout<<"Enter 6 to exit\n";
        
        string ip;
        cin>>ip;
        
        if (ip=="1") {
            string name, dept;
            char gender;
            
            int age;
            
            cout<<"Enter name\n";
            cin>>name;
            
            cout<<"Enter department\n";
            cin>>dept;
            
            cout<<"Enter age\n";
            cin>>age;
            
            cout<<"Enter age(M for Male and F for Female)\n";
            cin>>gender;
            
            
            l1.insert_front(name, dept, gender, age);
            cout<<"Faculty added\n\n";
        } else if (ip=="2") {
            string name, dept;
            char gender;
            
            int age;
            
            cout<<"Enter name\n";
            cin>>name;
            
            cout<<"Enter department\n";
            cin>>dept;
            
            cout<<"Enter age\n";
            cin>>age;
            
            cout<<"Enter age(M for Male and F for Female)\n";
            cin>>gender;
            
            
            l1.push_back(name, dept, gender, age);
            cout<<"Faculty added\n\n";
        } else if (ip=="3") {
            cout<<"Enter name of faculty to be searched\n";
            string name;
            cin>>name;
            
            if (l1.find(name))
                cout<<"This faculty member exists\n\n";
            else
                cout<<"This faculty member does not exist\n\n";
        } else if (ip=="4") {
            cout<<"Enter name of faculty to be deleted\n";
            string name;
            cin>>name;
            
            if (l1.remove(name))
                cout<<"Faculty removed\n\n";
            else
                cout<<"Faculty does not exist\n\n";
        } else if (ip=="5") {
            l1.print();
        } else if (ip=="6") {
            break;
        }
    }
    
    return 0;
}
