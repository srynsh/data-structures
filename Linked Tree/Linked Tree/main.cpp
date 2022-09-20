#include <bits/stdc++.h>

using namespace std;

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

class node {
public:
    int key;
    node* left = NULL;
    node* right = NULL;
    bool has_left = 0;
    bool has_right = 0;
    
    node(int k) {
        key = k;
    }
};

class tree {
private:
    node* root = NULL;
    
    void insert(int val, node* p) {
        if (!root) {
            node *pnew = new node(val);
            pnew->has_right = 0;
            pnew->has_left = 0;
            root = pnew;
        } else if (!p->has_right && p->key <= val) {
            node *pnew = new node(val);
            pnew->right = p->right;
            pnew->left = p;
            p->right = pnew;
            p->has_right = 1;
        } else if (!p->has_left && p->key > val) {
            node *pnew = new node(val);
            pnew->left = p->left;
            pnew->right = p;
            p->left = pnew;
            p->has_left = 1;
        } else if (val >= p->key) {
            return insert(val, p->right);
        } else if (val < p->key) {
            return insert(val, p->left);
        }
    }
    
    node* parent(node* p) {
        node* pt = root;
        
        if (p == root || !p) {
            return NULL;
        }
        
        while (pt && pt->left != p && pt->right != p) {
            if (p->key > pt->key)
                pt = pt->right;
            else
                pt = pt->left;
        }
        
        return pt;
    }
    
    node* parent(node* p, node* head) {
        node* pt = head;
        
        if (p == root || !p) {
            return NULL;
        }
        
        while (pt && pt->left != p && pt->right != p) {
            if (p->key > pt->key)
                pt = pt->right;
            else
                pt = pt->left;
        }
        
        return pt;
    }
    
    void remove(int val, node* p, node* head) {
        if (!p)
            return;
        if (p->key == val) {
            node* par = parent(p, head); //->parent;
            
            if (p->left && p->right) {
                node *suc = right_successor(p);
                p->key = suc->key;
                return remove(suc->key, p->right, p->right);
            } else if (!p->left && !p->right) {
                if (par->left == p)
                    par->left = NULL;
                else if (par->right == p)
                    par->right = NULL;
            } else if (!p->right) {
                if (par->left == p)
                    par->left = p->left;
                else if (par->right == p)
                    par->right = p->left;
            } else if (!p->left) {
                if (par->left == p)
                    par->left = p->right;
                else if (par->right == p)
                    par->right = p->right;
            }
            
            delete p;
        } else if (p->key > val) {
            remove(val, p->left, p);
        } else {
            remove(val, p->right, p);
        }
    }
    
    node* right_successor(node* p) {
        if (!p->right)
            return NULL;
        
        node *pright = p->right;
        
        while (pright->left)
            pright = pright->left;
        
        return pright;
    }
    
    void destroy(node* p) {
        if (!p)
            return;
        
        node *left = p->left;
        node *right = p->right;
        
        p->right = NULL;
        p->left = NULL;
        
        bool has_l = p->has_left;
        bool has_r = p->has_right;
        
        delete p;
        
        if (has_l)
            destroy(left);
        if (has_r)
            destroy(right);
    }
    
public:
    void insert(int key) {
        insert(key, root);
    }
    
    bool search(int a) {
        node* p = root;
        
        while (p->left) {
            p = p->left;
        }
        
        if (p->key == a)
            return true;
        
        while (p->right) {
            if (p->has_right == 0) {
                p = p->right;
                if (p->key == a)
                    return true;
            } else {
                p = p->right;
                
                if (p->has_left) {
                    while (p->has_left) {
                        p = p->left;
                    }
                }
                
                if (p->key == a)
                    return true;
            }
        }
        
        return false;
    }
    
    void remove(int val) {
        return remove(val, root, root);
    }
    
    void inorder() {
        node* p = root;
        
        while (p->left) {
            p = p->left;
        }
        
        cout<<p->key<<" ";
        
        while (p->right) {
            if (p->has_right == 0) {
                p = p->right;
                cout<<p->key<<" ";
            } else {
                p = p->right;
                
                if (p->has_left) {
                    while (p->has_left) {
                        p = p->left;
                    }
                }
                
                cout<<p->key<<" ";
            }
        }
    }
    
    ~tree() {
        destroy(root);
    }
}; // Tree without parent pointer

int main() {
//    tree t;
//    t.insert(10);
//
//    t.insert(13);
//    t.insert(5);
//
//    t.insert(7);
//    t.insert(3);
//    t.insert(11);
//    t.insert(20);
//
//
//    t.insert(1);
//    t.insert(6);
//    t.insert(8);
//    t.insert(12);
//    t.insert(15);
//    t.insert(22);
//
//    t.insert(2);
//    t.insert(9);
//    t.insert(14);
//    t.insert(17);
//
//    t.insert(16);
//    t.insert(19);
//
//    cout<<endl;
//    //t.remove(15);
//    cout<<endl;
//    cout<<endl;
//    t.inorder();
//    cout<<endl;
    
    string a = "a";
    string b = "ab";
    
    cout<< (a<b) <<endl;
    
    return 0;
}
