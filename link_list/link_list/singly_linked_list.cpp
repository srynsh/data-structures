//
// Suryaansh Jain
// CS21BTECH11057
// Singly Linked List
//

#include <bits/stdc++.h>

using namespace std;

class node {
public:
    node* next = NULL;  
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
};

class linked_list {
private:
    node *head = NULL;
    node *tail = NULL;
    
public:
    void push_back(string n, string d, char g, int a) {
        node *p = tail;
        
        if (!p) {
            node *pnew = new node(n, d, g, a);
            head = pnew;
            tail = pnew;
            return;
        }

        p->next = new node(n, d, g, a);
        tail = p->next;
        return;
    }
    
    void insert_front(string n, string d, char g, int a) {
        node *pnew = new node(n, d, g, a);
        pnew->next = head;
        if (!tail)
            tail = pnew;
        head = pnew;
    }
    
    bool remove(string name_of_person) {
        node *p = head;

        if (!p)
            return 0;

        if (p->name == name_of_person) {
            if (tail == head) {
                tail = NULL;
            }
            node* ptemp = head;
            head = head->next;
            delete ptemp;
            return 1;
        }
        
        while (p->next && p->next->name != name_of_person) {
            p = p->next;
        }
        
        if (!p->next) {
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
            cout<<p->name<<" "<<p->age<<" "<<p->dept<<" ";
            if (p->gender == 'M')
                cout<<"male\n";
            else
                cout<<"female\n";
            
            cout<<'\n';
            
            p = p->next;
        }
    }
    
    bool find(string name_of_person) {
        node *p = head;
        while (p) {
            if (p->name == name_of_person)
                return 1;
            p = p->next;
        }
        
        return 0;
    }
    
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

int main() {
    linked_list l1;
    
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
                cout<<"This faculty member exists\n";
            else
                cout<<"This faculty member does not exist\n";
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
