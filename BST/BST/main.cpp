#include <bits/stdc++.h>

using namespace std;

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

class nodeT {
public:
    int age;
    char gender;
    string name;
    string dept;
    nodeT* left = NULL;
    nodeT* right = NULL;
    
    nodeT(int a, char g, string n, string d) {
        dept = d;
        name = n;
        age = a;
        gender = g;
    }
};

class tree {
private:
    nodeT* root = NULL;

    void insert(int a, char g, string n, string d, nodeT* p) {
        if (!root) {
            nodeT *pnew = new nodeT(a, g, n, d);
            root = pnew;
        } else if (p->right == NULL && p->name <= n) {
            nodeT *pnew = new nodeT(a, g, n, d);
            p->right = pnew;
        } else if (p->left == NULL && p->name > n) {
            nodeT *pnew = new nodeT(a, g, n, d);
            p->left = pnew;
        } else if (n >= p->name) {
            return insert(a, g, n, d, p->right);
        } else {
            return insert(a, g, n, d, p->left);
        }
    }
    
    nodeT* parent(nodeT* p) {
        nodeT* pt = root;
        
        if (p == root || !p) {
            return NULL;
        }
        
        while (pt && pt->left != p && pt->right != p) {
            if (p->name > pt->name)
                pt = pt->right;
            else
                pt = pt->left;
        }
        
        return pt;
    }
    
    nodeT* parent(nodeT* p, nodeT* head) {
        nodeT* pt = head;
        
        if (p == root || !p) {
            return NULL;
        }
        
        while (pt && pt->left != p && pt->right != p) {
            if (p->name > pt->name)
                pt = pt->right;
            else
                pt = pt->left;
        }
        
        return pt;
    }
    
    void remove(string n, nodeT* p, nodeT* head) {
        if (!p)
            return;
        if (p->name == n) {
            nodeT* par = parent(p, head); //->parent;

            if (p->left && p->right) {
                nodeT *suc = right_successor(p);
                p->name = suc->name;
                p->age = suc->age;
                p->dept = suc->dept;
                p->gender = suc->gender;
                return remove(suc->name, p->right, p->right);
            } else if (!p->left && !p->right) {
                if (!par) {
                    delete p;
                    root = NULL;
                    return;
                } else if (par->left == p)
                    par->left = NULL;
                else if (par->right == p)
                    par->right = NULL;
            } else if (!p->right) {
                if (!par) {
                    root = p->left;
                    delete p;
                    return;
                } else if (par->left == p)
                    par->left = p->left;
                else if (par->right == p)
                    par->right = p->left;
            } else if (!p->left) {
                if (!par) {
                    root = p->right;
                    delete p;
                    return;
                } else if (par->left == p)
                    par->left = p->right;
                else if (par->right == p)
                    par->right = p->right;
            }
            
            delete p;
        } else if (p->name > n) {
            remove(n, p->left, p);
        } else {
            remove(n, p->right, p);
        }
    }

    nodeT* right_successor(nodeT* p) {
        if (!p->right)
            return NULL;
        
        nodeT *pright = p->right;
        
        while (pright->left)
            pright = pright->left;
            
        return pright;
    }

    nodeT* search(string n, nodeT* p) {
        if (!p)
            return NULL;

        if (p->name == n)
            return p;

        if (p->left && n == p->left->name)
            return p->left;
        else if (p->right && p->right->name == n)
            return p->right;
        else if (n > p->name)
            return search(n, p->right);
        else if (n < p->name)
            return search(n, p->left);
        else
            return NULL;
    }

    void printin(nodeT* p) {
        if (!p)
            return;

        printin(p->left);
        cout<<p->name<<"\n";
        printin(p->right);
    }
    
    void destroy(nodeT* p) {
        if (!p)
            return;
        
        nodeT *left = p->left;
        nodeT *right = p->right;
        
        p->right = NULL;
        p->left = NULL;
        
        delete p;
        
        destroy(left);
        destroy(right);
    }

public:
    void insert(int a, char g, string n, string d) {
        insert(a, g, n, d, root);
    }

    void print() {
        printin(root);
    }

    bool search(string name) {
        return search(name, root);
    }

    void remove(string name) {
        return remove(name, root, root);
    }
    
    ~tree() {
        destroy(root);
    }
}; // Tree without parent pointer

int main() {
    tree t2;
    
    while (1) {
        cout<<"Enter 1 to insert element\nEnter 2 to delete element\nEnter 3 to print in order\nEnter 4 to search for an element\nEnter 5 to exit\n";

        string i;
        cin>>i;

        if (i == "1") {
            cout<<"Enter name to add\n";
            string name; cin>>name;
            cout<<"Enter department of faculty\n";
            string dept; cin>>dept;
            cout<<"Enter age\n";
            int age; cin>>age;
            cout<<"Enter M for male and F for female\n";
            char gender; cin>>gender;
            t2.insert(age, gender, name, dept);
            cout<<"Element added\n\n";
        } else if (i == "2") {
            cout<<"Enter name to delete\n";
            string name; cin>>name;
            t2.remove(name);
            cout<<"Element deleted\n\n";
        } else if (i == "3") {
            t2.print();
            cout<<endl;
        } else if (i == "4") {
            cout<<"Enter name to search\n";
            string name; cin>>name;
            if (t2.search(name)) {
                cout<<"Element exists\n\n";
            } else {
                cout<<"Element does not exist\n\n";
            }
        } else if (i == "5") {
            break;
        }
    }
    return 0;
}
