#include <string>
using namespace std;

class Trie {
    static const int SIZE = 26;

     struct Node {
        int count;
        bool end;
        Node* child[SIZE];
        Node(int cnt, bool e) {
            count = cnt;
            end = e;
            for (int i = 0; i < SIZE; ++i) {
                child[i] = nullptr;
            }
        }
    };

    Node* root = nullptr;

    public:

    Trie() {
        root = new Node(0, false);
    }

    void insert(string str) {
        Node* node = root;
        for (char c : str) {
            int i = c - 'a';
            if (node->child[i]) {
                node = node->child[i];
                node->count++;
            }
            else {
                node->child[i] = new Node(1, false);
                node = node->child[i];
            }
        }
        node->end = true;
    }

    int word_count(string word) {
        Node* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->child[i]) {
                return 0;
            }
            node = node->child[i];
        }
        return node->end ? node->count : 0;
    }

    int prefix_count(string prefix) {
        Node* node = root;
        for (char c : prefix) {
            int i = c - 'a';
            if (!node->child[i]) {
                return 0;
            }
            node = node->child[i];
        }
        return node->count;
    }
};