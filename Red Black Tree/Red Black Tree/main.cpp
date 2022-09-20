#include <bits/stdc++.h>

using namespace std;

enum Color {
    red,
    black,
    end_black
};

class rb_node {
public:
    int key;
    int age;
    string name;
    string dept;
    char gender;
    int color = red;
    rb_node *left = NULL;
    rb_node *right = NULL;
    rb_node *parent = NULL;
    
    rb_node(int k) {
        key = k;
    }
    
    rb_node(string n, string d, int a, char g) {
        name = n;
        dept = d;
        age = a;
        gender = g;
    }
};

class red_black_tree {
private:
    rb_node *root = NULL;
    
    void left_rotate(rb_node *ptr) {
        rb_node *right_child = ptr->right;
        ptr->right = right_child->left;
        
        if (ptr->right != NULL) {
            ptr->right->parent = ptr;
        }
        
        right_child->parent = ptr->parent;
        
        if (ptr->parent == NULL) {
            root = right_child;
        } else if (ptr == ptr->parent->left) {
            ptr->parent->left = right_child;
        } else {
            ptr->parent->right = right_child;
        }
        
        right_child->left = ptr;
        ptr->parent = right_child;
    }
    
    void right_rotate(rb_node *ptr) {
        rb_node *left_child = ptr->left;
        ptr->left = left_child->right;
        
        if (ptr->left != NULL) {
            ptr->left->parent = ptr;
        }
        
        left_child->parent = ptr->parent;
        
        if (ptr->parent == NULL) {
            root = left_child;
        } else if (ptr == ptr->parent->left) {
            ptr->parent->left = left_child;
        } else {
            ptr->parent->right = left_child;
        }
        
        left_child->right = ptr;
        ptr->parent = left_child;
    }
    
    void balance_insert(rb_node *ptr) {
        rb_node *parent = NULL;
        rb_node *grandparent = NULL;
        
        while (ptr != root && get_colour(ptr) == red && get_colour(ptr->parent) == red) {
            parent = ptr->parent;
            grandparent = parent->parent;
            
            if (parent == grandparent->left) {
                rb_node *uncle = grandparent->right;
                
                if (get_colour(uncle) == red) {
                    set_colour(uncle, black);
                    set_colour(parent, black);
                    set_colour(grandparent, red);
                    ptr = grandparent;
                } else {
                    if (ptr == parent->right) {
                        left_rotate(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    
                    right_rotate(grandparent);
                    swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            } else {
                rb_node *uncle = grandparent->left;
                
                if (get_colour(uncle) == red) {
                    set_colour(uncle, black);
                    set_colour(parent, black);
                    set_colour(grandparent, red);
                    ptr = grandparent;
                } else {
                    if (ptr == parent->left) {
                        right_rotate(parent);
                        ptr = parent;
                        parent = ptr->parent;
                    }
                    
                    left_rotate(grandparent);
                    swap(parent->color, grandparent->color);
                    ptr = parent;
                }
            }
        }
        
        set_colour(root, black);
    }
    
    void balance_delete(rb_node *node) {
        if (node == NULL)
            return;
        
        if (node == root) {
            delete node;
            root = NULL;
            return;
        }
        
        if (get_colour(node) == red || get_colour(node->left) == red || get_colour(node->right) == red) {
            rb_node *child;
            
            if (node->left) {
                child = node->left;
            } else {
                child = node->right;
            }
            
            if (node == node->parent->left) {
                node->parent->left = child;
                if (child != NULL)
                    child->parent = node->parent;
                set_colour(child, black);
                delete (node);
            } else {
                node->parent->right = child;
                if (child != NULL)
                    child->parent = node->parent;
                set_colour(child, black);
                delete (node);
            }
        } else {
            rb_node *sibling = NULL;
            rb_node *parent = NULL;
            rb_node *ptr = node;
            set_colour(ptr, end_black);
            
            while (ptr != root && get_colour(ptr) == end_black) {
                parent = ptr->parent;
                
                if (ptr == parent->left) {
                    sibling = parent->right;
                    
                    if (get_colour(sibling) == red)
                    {
                        set_colour(sibling, black);
                        set_colour(parent, red);
                        left_rotate(parent);
                    } else {
                        if (get_colour(sibling->left) == black && get_colour(sibling->right) == black)
                        {
                            set_colour(sibling, red);
                            if (get_colour(parent) == red)
                                set_colour(parent, black);
                            else
                                set_colour(parent, end_black);
                            ptr = parent;
                        } else {
                            if (get_colour(sibling->right) == black)
                            {
                                set_colour(sibling->left, black);
                                set_colour(sibling, red);
                                right_rotate(sibling);
                                sibling = parent->right;
                            }
                            
                            set_colour(sibling, parent->color);
                            set_colour(parent, black);
                            set_colour(sibling->right, black);
                            left_rotate(parent);
                            break;
                        }
                    }
                } else {
                    sibling = parent->left;
                    
                    if (get_colour(sibling) == red) {
                        set_colour(sibling, black);
                        set_colour(parent, red);
                        right_rotate(parent);
                    } else {
                        if (get_colour(sibling->left) == black && get_colour(sibling->right) == black) {
                            set_colour(sibling, red);
                            
                            if (get_colour(parent) == red) {
                                set_colour(parent, black);
                            } else {
                                set_colour(parent, end_black);
                            }
                            
                            ptr = parent;
                        } else {
                            if (get_colour(sibling->left) == black) {
                                set_colour(sibling->right, black);
                                set_colour(sibling, red);
                                left_rotate(sibling);
                                sibling = parent->left;
                            }
                            
                            set_colour(sibling, parent->color);
                            set_colour(parent, black);
                            set_colour(sibling->left, black);
                            right_rotate(parent);
                            break;
                        }
                    }
                }
            }
            
            if (node == node->parent->left) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
            
            delete (node);
            set_colour(root, black);
        }
    }
    
    void inorder(rb_node *ptr) {
        if (ptr == NULL)
            return;
        
        inorder(ptr->left);
        cout << ptr->name << " " << ptr->dept << " " << ptr->age << " " << ptr->gender << endl;
        inorder(ptr->right);
    }
    
    int get_colour(rb_node *node) {
        if (node == NULL)
            return black;
        
        return node->color;
    }
    
    void set_colour(rb_node *node, int color) {
        if (node == NULL)
            return;
        
        node->color = color;
    }
    
    rb_node *min_element(rb_node *node) {
        
        rb_node *ptr = node;
        
        while (ptr->left != NULL) {
            ptr = ptr->left;
        }
        
        return ptr;
    }
    
    rb_node *max_element(rb_node *node) {
        rb_node *ptr = node;
        
        while (ptr->right != NULL) {
            ptr = ptr->right;
        }
        
        return ptr;
    }
    
    rb_node *insert(rb_node *root, rb_node *ptr) {
        if (root == NULL)
            return ptr;
        
        if (ptr->name < root->name) {
            root->left = insert(root->left, ptr);
            root->left->parent = root;
        } else if (ptr->name > root->name) {
            root->right = insert(root->right, ptr);
            root->right->parent = root;
        }
        
        return root;
    }
    
    rb_node *remove(rb_node *root, string name) {
        if (root == NULL)
            return root;
        
        if (name < root->name)
            return remove(root->left, name);
        
        if (name > root->name)
            return remove(root->right, name);
        
        if (root->left == NULL || root->right == NULL)
            return root;
        
        rb_node *temp = min_element(root->right);
        root->name = temp->name;
        return remove(root->right, temp->name);
    }
    
    int black_height(rb_node *node) {
        int blackheight = 0;
        while (node != NULL) {
            if (get_colour(node) == black)
                blackheight++;
            node = node->left;
        }
        
        return blackheight;
    }
    
    bool search(string name, rb_node *head) {
        if (head == NULL)
            return 0;
        
        if (head->name == name)
            return 1;
        
        return (search(name, head->left) || search(name, head->right));
    }
    
    void destroy(rb_node* p) {
        if (!p)
            return;
        
        rb_node *left = p->left;
        rb_node *right = p->right;
        
        p->right = NULL;
        p->left = NULL;
        
        if (left)
            left->parent = NULL;
        if (right)
            right->parent = NULL;
        
        delete p;
        
        destroy(left);
        destroy(right);
    }
    
public:
    void insert(string name, string dept, int age, char gender) {
        rb_node *node = new rb_node(name, dept, age, gender);
        root = insert(root, node);
        balance_insert(node);
    }
    
    void remove(string name) {
        rb_node *node = remove(root, name);
        balance_delete(node);
    }
    
    bool search(string name) {
        return search(name, root);
    }
    
    void inorder() {
        inorder(root);
    }
    
    ~red_black_tree() {
        destroy(root);
    }
};

int main() {
    red_black_tree t1;

    
    while(1) {
        cout<<"Enter 1 to add faculty\n";
        cout<<"Enter 2 to delete faculty\n";
        cout<<"Enter 3 to search for a faculty\n";
        cout<<"Enter 4 to print in order\n";
        cout<<"Enter 5 to exit\n";
        
        string n;
        cin>>n;
        
        if (n == "1") {
            cout<<"Enter name to add\n";
            string name; cin>>name;
            cout<<"Enter department\n";
            string dept; cin>>dept;
            cout<<"Enter age to add\n";
            int age; cin>>age;
            cout<<"Enter gender (M for male and F for female)\n";
            char gen; cin>>gen;
            
            t1.insert(name, dept, age, gen);
            cout<<"Faculty added\n\n";
        } else if (n == "2") {
            cout<<"Enter name to delete\n";
            string name; cin>>name;
            
            t1.remove(name);
            cout<<"Faculty removed\n\n";
        } else if (n == "3") {
            cout<<"Enter name to search\n";
            string name; cin>>name;
            
            if (t1.search(name)) {
                cout<<"This faculty exists\n\n";
            } else {
                cout<<"This faculty does not exist\n\n";
            }
        } else if (n == "4") {
            t1.inorder();
            cout<<endl<<endl;
        } else if (n == "5") {
            break;
        } else {
            cout<<"Enter a valid input or 5 to exit\n\n";
        }
    }
    
    return 0;
}
