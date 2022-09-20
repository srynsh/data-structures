#include <bits/stdc++.h>
using namespace std;

class b_tree_node {
public:
    int *key_array;
    int branching_factor;
    b_tree_node **child_aray;
    int len;
    bool is_leaf;
    
    void print() { 
        int i = 0;
        for (; i < len; i++) {
            if (is_leaf == false)
                child_aray[i]->print();
            
            cout << key_array[i] << ' ';
        }
        
        if (is_leaf == false)
            child_aray[i]->print();
    }
    
    b_tree_node *search(int k) {
        int i = 0;
        while (i < len && k > key_array[i]) {
            i++;
        }
        
        if (key_array[i] == k)
            return this;
        
        if (is_leaf == true)
            return NULL;
        
        return child_aray[i]->search(k);
    }
    
    int find_key(int k) {
        int index=0;
        
        while (index<len && key_array[index] < k) {
            index++;
        }
        
        return index;
    }
    
    int successor(int idx) {
        b_tree_node *cur = child_aray[idx+1];
        while (!cur->is_leaf) {
            cur = cur->child_aray[0];
        }
        
        return cur->key_array[0];
    }
    
    int predessor(int idx) {
        b_tree_node *cur=child_aray[idx];
        
        while (!cur->is_leaf) {
            cur = cur->child_aray[cur->len];
        }
        
        return cur->key_array[cur->len-1];
    }
    
    void remove(int k) {
        int idx = find_key(k);
        
        if (idx < len && key_array[idx] == k) {
            if (is_leaf)
                remove_from_leaf(idx);
            else
                remove_from_non_leaf(idx);
        } else {
            if (is_leaf) {
                return;
            }
            
            bool flag;
            
            if (idx == len)
                flag = 1;
            else
                flag = 0;
            
            if (child_aray[idx]->len < branching_factor)
                fill(idx);
            
            if (flag && idx > len)
                child_aray[idx-1]->remove(k);
            else
                child_aray[idx]->remove(k);
        }
    }
    
    void insert_not_full(int k) {
        int i = len-1;
        
        if (is_leaf == true) {
            while (i >= 0 && key_array[i] > k) {
                key_array[i+1] = key_array[i];
                i--;
            }
            
            key_array[i+1] = k;
            len = len+1;
        }
        else {
            while (i >= 0 && key_array[i] > k) {
                i--;
            }
            
            if (child_aray[i+1]->len == 2*branching_factor-1) {
                split_child(i+1, child_aray[i+1]);
                
                if (key_array[i+1] < k) {
                    i++;
                }
            }
            
            child_aray[i+1]->insert_not_full(k);
        }
    }
    
    void split_child(int i, b_tree_node *y) {
        b_tree_node *z = new b_tree_node(y->branching_factor, y->is_leaf);
        z->len = branching_factor - 1;
        
        for (int j = 0; j < branching_factor-1; j++) {
            z->key_array[j] = y->key_array[j+branching_factor];
        }
        
        if (y->is_leaf == false) {
            for (int j = 0; j < branching_factor; j++)
                z->child_aray[j] = y->child_aray[j+branching_factor];
        }
        
        y->len = branching_factor - 1;
        
        for (int j = len; j >= i+1; j--)
            child_aray[j+1] = child_aray[j];
        
        child_aray[i+1] = z;
        
        for (int j = len-1; j >= i; j--)
            key_array[j+1] = key_array[j];
        
        key_array[i] = y->key_array[branching_factor-1];
        
        len = len + 1;
    }
    
    void remove_from_leaf(int idx) {
        for (int i=idx+1; i<len; i++) {
            key_array[i-1] = key_array[i];
        }
        
        len--;
        
        return;
    }
    
    void remove_from_non_leaf(int idx) {
        
        int k = key_array[idx];
        
        if (child_aray[idx]->len >= branching_factor) {
            int pred = predessor(idx);
            key_array[idx] = pred;
            child_aray[idx]->remove(pred);
        } else if (child_aray[idx+1]->len >= branching_factor) {
            int succ = successor(idx);
            key_array[idx] = succ;
            child_aray[idx+1]->remove(succ);
        } else {
            merge(idx);
            child_aray[idx]->remove(k);
        }
    }
    
    void fill(int idx) {
        if (idx!=0 && child_aray[idx-1]->len>=branching_factor) {
            take_prev(idx);
        } else if (idx!=len && child_aray[idx+1]->len>=branching_factor) {
            take_next(idx);
        }else {
            if (idx != len)
                merge(idx);
            else
                merge(idx-1);
        }
    }
    
    void take_prev(int idx) {
        b_tree_node *child=child_aray[idx];
        b_tree_node *sister=child_aray[idx-1];
        
        for (int i=child->len-1; i>=0; --i)
            child->key_array[i+1] = child->key_array[i];
        
        if (!child->is_leaf) {
            for(int i=child->len; i>=0; --i)
                child->child_aray[i+1] = child->child_aray[i];
        }
        
        child->key_array[0] = key_array[idx-1];
        
        if(!child->is_leaf)
            child->child_aray[0] = sister->child_aray[sister->len];
        
        key_array[idx-1] = sister->key_array[sister->len-1];
        
        child->len += 1;
        sister->len -= 1;
    }
    
    void take_next(int idx) {
        b_tree_node *child=child_aray[idx];
        b_tree_node *sibling=child_aray[idx+1];
        
        child->key_array[(child->len)] = key_array[idx];
        
        if (!(child->is_leaf))
            child->child_aray[(child->len)+1] = sibling->child_aray[0];
        
        key_array[idx] = sibling->key_array[0];
        
        for (int i=1; i<sibling->len; ++i)
            sibling->key_array[i-1] = sibling->key_array[i];
        
        if (!sibling->is_leaf) {
            for(int i=1; i<=sibling->len; ++i)
                sibling->child_aray[i-1] = sibling->child_aray[i];
        }
        
        child->len += 1;
        sibling->len -= 1;
    }
    
    void merge(int idx) {
        b_tree_node *child = child_aray[idx];
        b_tree_node *sibling = child_aray[idx+1];
        
        child->key_array[branching_factor-1] = key_array[idx];
        
        for (int i=0; i<sibling->len; ++i)
            child->key_array[i+branching_factor] = sibling->key_array[i];
        
        if (!child->is_leaf) {
            for(int i=0; i<=sibling->len; ++i)
                child->child_aray[i+branching_factor] = sibling->child_aray[i];
        }
        
        for (int i=idx+1; i<len; ++i)
            key_array[i-1] = key_array[i];
        
        for (int i=idx+2; i<=len; ++i)
            child_aray[i-1] = child_aray[i];
        
        child->len += sibling->len+1;
        len--;
        
        delete(sibling);
    }
    
    b_tree_node(int t1, bool leaf1) {
        branching_factor = t1;
        is_leaf = leaf1;
        
        key_array = new int[2*branching_factor-1];
        child_aray = new b_tree_node *[2*branching_factor];
        
        len = 0;
    }
    
    ~b_tree_node() {
        delete key_array;
        delete child_aray;
    }
};

class b_tree {
private:
    b_tree_node *root;
    int branching_factor;
    
    void destory(b_tree_node *p) {
        if (!p)
            return;
        
        for (int i = 0; i<=p->len; i++) {
            destory(p->child_aray[i]);
        }
        
        delete p;
    }
    
public:
    
    b_tree(int bf) {
        root = NULL;
        branching_factor = bf;
    }
    
    void print_inorder() {
        if (root != NULL)
            root->print();
    }
    
    bool search(int k) {
        if(root)
            return root->search(k);
        
        return NULL;
    }
    
    void insert(int k) {
        if (root == NULL) {
            root = new b_tree_node(branching_factor, true);
            root->key_array[0] = k;
            root->len = 1;
        } else {
            if (root->len == 2*branching_factor-1) {
                b_tree_node *s = new b_tree_node(branching_factor, false);
                
                s->child_aray[0] = root;
                s->split_child(0, root);
                
                int i = 0;
                
                if (s->key_array[0] < k)
                    i++;
                
                s->child_aray[i]->insert_not_full(k);
                
                root = s;
            } else {
                root->insert_not_full(k);
            }
        }
    }
    
    void remove(int k) {
        if (!root) {
            return;
        }
        
        root->remove(k);
        
        if (root->len==0) {
            b_tree_node *tmp = root;
            if (root->is_leaf)
                root = NULL;
            else
                root = root->child_aray[0];
            
            delete tmp;
        }
    }
    
    ~b_tree() {
        destory(root);
    }
};

int main() {
    b_tree t1(5);
    
    while (1) {
        cout<<"Enter 1 to insert age\n";
        cout<<"Enter 2 to delete age\n";
        cout<<"Enter 3 to search for age\n";
        cout<<"Enter 4 to print\n";
        cout<<"Enter 5 to exit\n";
        
        string n;
        cin>>n;
        
        if (n == "1") {
            int a;
            cout<<"Enter age\n";
            cin>>a;
            
            t1.insert(a);
            cout<<"Age added\n\n";
        } else if (n == "2") {
            int a;
            cout<<"Enter age\n";
            cin>>a;
            
            t1.remove(a);
            cout<<"Age removed\n\n";
        } else if (n == "3") {
            int a;
            cout<<"Enter age\n";
            cin>>a;
            
            if (t1.search(a)) {
                cout<<"Age exists\n\n";
            } else {
                cout<<"Age does not exist\n\n";
            }
        } else if (n == "4") {
            t1.print_inorder();
            cout<<endl<<endl;
        } else if (n == "5") {
            break;
        } else {
            cout<<"Enter a valid input\n\n";
        }
    }
    
    return 0;
}
