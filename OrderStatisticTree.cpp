#include <algorithm>
#include <climits>
using namespace std;

class OrderStatisticTree {
 
    struct Node {
        int val, count, height, size, node_count;
        Node *left, *right;
        Node(int v) {
            val = v;
            count = 1;
            size = 1;
            height = 1;
            node_count = 1;
            left = nullptr;
            right = nullptr;
        }
    };
 
    Node* root = nullptr;
 
    int count_util(Node* root, int val) {
        if (!root) {
            return 0;
        }
        if (root->val == val) {
            return root->count;
        }
        else if (root->val > val) {
            return count_util(root->left, val);
        }
        else {
            return count_util(root->right, val);
        }
    }
 
    int order_util(Node* root, int val) {
        if (!root) {
            return 0;
        }
        if (root->val == val) {
            if (root->left) {
                return root->left->size;
            }
            return 0;
        }
        else if (root->val > val) {
            return order_util(root->left, val);
        }
        else {
            int left_size = 0;
            if (root->left) {
                left_size = root->left->size;
            }
            return left_size + root->count + order_util(root->right, val);
        }
    }
 
    int select_distinct_util(Node* root, int k) {
        if (!root) {
            return INT_MIN;
        }
        if (node_count(root->left) == k - 1) {
            return root->val;
        }
        if (node_count(root->left) >= k) {
            return select_distinct_util(root->left, k);
        }
        else {
            return select_distinct_util(root->right, k - node_count(root->left) - 1);
        }
    }
 
    int select_util(Node* root, int k) {
        if (!root) {
            return INT_MIN;
        }
        if (size(root->left) + root->count < k) {
            return select_util(root->right, k - size(root->left) - root->count);
        }
        else if (size(root->left) < k && size(root->left) + root->count >= k) {
            return root->val;
        }
        else {
            return select_util(root->left, k);
        }
    }
 
    Node* right_rotate(Node* A) {
        /*    A              B 
             / \           /   \
            B  Ar   ->    C     A
           / \           / \   / \
          C   Br        Cl Cr Br Ar 
         / \
        Cl Cr 
        
        */
 
        Node* B = A->left;
        Node* Br = B->right;
        B->right = A;
        A->left = Br;
        A->height = 1 + max(height(A->left), height(A->right));
        B->height = 1 + max(height(B->left), height(B->right));
        A->size = A->count + size(A->left) + size(A->right);
        B->size = B->count + size(B->left) + size(B->right);
        A->node_count = 1 + node_count(A->left) + node_count(A->right);
        B->node_count = 1 + node_count(B->left) + node_count(B->right);
        return B;
    }
 
    Node* left_rotate(Node* A) {
        /*  A                 B 
          /  \              /   \ 
         Al   B     ->     A     C
             / \          / \   / \
            Bl  C        Al Bl Cl Cr 
               / \
              Cl  Cr
        */
 
        Node* B = A->right;
        Node* Bl = B->left;
        B->left = A;
        A->right = Bl;
        A->height = 1 + max(height(A->left), height(A->right));
        B->height = 1 + max(height(B->left), height(B->right));
        A->size = A->count + size(A->left) + size(A->right);
        B->size = B->count + size(B->left) + size(B->right);
        A->node_count = 1 + node_count(A->left) + node_count(A->right);
        B->node_count = 1 + node_count(B->left) + node_count(B->right);
        return B;
    }
 
    int size(Node* root) {
        if (!root) {
            return 0;
        }
        return root->size;
    }
 
    int height(Node* root) {
        if (!root) {
            return 0;
        }
        return root->height;
    }
 
    int node_count(Node* root) {
        if (!root) {
            return 0;
        }
        return root->node_count;
    }
 
    int balance(Node* root) {
        if (!root) {
            return 0;
        }
        return height(root->left) - height(root->right);
    }
 
    Node* balance_it_out(Node* root) {
        int bf = balance(root);
        if (bf < -1) {
            if (height(root->right->left) > height(root->right->right)) { //RL
                root->right = right_rotate(root->right);
                root = left_rotate(root);
            }
            else { //RR 
                root = left_rotate(root);
            } 
        }
        else if (bf > 1) {
            if (height(root->left->right) > height(root->left->left)) { //LR
                root->left = left_rotate(root->left);
                root = right_rotate(root);
            }
            else { //LL 
                root = right_rotate(root);
            } 
        }
        return root;
    }
 
    Node* insert_util(Node* root, int val) {
        if (!root) {
            Node* node = new Node(val);
            return node;
        }
        if (root->val == val) {
            root->count++;
            root->size++;
            return root;
        }
        if (root->val > val) {
            root->left = insert_util(root->left, val);
        }
        else {
            root->right = insert_util(root->right, val);
        }
        root->height = 1 + max(height(root->left), height(root->right));
        root->node_count = 1 + node_count(root->left) + node_count(root->right);
        root->size = root->count + size(root->left) + size(root->right);
        root = balance_it_out(root);
        return root;
    }
 
    Node* remove_util(Node* root, int val) {
        if (!root) {
            return nullptr;
        }
        if (root->val == val) {
            if (root->count > 1) {
                root->count--;
                root->size--;
                return root;
            }
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            }
            if (!root->left) {
                Node* right = root->right;
                delete root;
                return right;
            }
            if (!root->right) {
                Node* left = root->left;
                delete root;
                return left;
            }
            int inorder_succ = min_element(root->right);
            root->val = inorder_succ;
            root->right = remove_util(root->right, inorder_succ);
        }
        else if (root->val > val) {
            root->left = remove_util(root->left, val);
        }
        else {
            root->right = remove_util(root->right, val);
        }
        root->height = 1 + max(height(root->left), height(root->right));
        root->node_count = 1 + node_count(root->left) + node_count(root->right);
        root->size = root->count + size(root->left) + size(root->right);
        root = balance_it_out(root);
        return root;
    }
 
    int min_element(Node* root) {
        if (!root) {
            return INT_MIN;
        }
        while (root->left) {
            root = root->left;
        }
        return root->val;
    }
 
    int max_element(Node* root) {
        if (!root) {
            return INT_MAX;
        }
        while (root->right) {
            root = root->right;
        }
        return root->val;
    }
 
    public:
 
    void insert(int val) {
        root = insert_util(root, val);
    }
 
    void remove(int val) {
        if (count(val) == 0) {
            return;
        }
        root = remove_util(root, val);
    }
 
    int order(int val) {
        return order_util(root, val);
    }
 
    int count(int val) {
        return count_util(root, val);
    }
 
    int size() {
        if (!root) {
            return 0;
        }
        return root->size;
    }
 
    int size_distinct() {
        return root->node_count;
    }
 
    int min_value() {
        return min_element(root);
    }
 
    int max_value() {
        return max_element(root);
    }
 
    int select(int k) {
        if (k > root->size) {
            return INT_MIN;
        }
        return select_util(root, k);
    }
 
    int select_distinct(int k) {
        if (k > root->node_count) {
            return INT_MIN;
        }
        return select_distinct_util(root, k);
    }
};