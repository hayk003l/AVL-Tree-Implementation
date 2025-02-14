#include <iostream>


struct Node {
    Node* left;
    Node* right;
    int val;
    int height;
    Node(const int& value) : val(value), height(0), left(nullptr), right(nullptr) {}
};

class AVL {
public:
    AVL();
    ~AVL();

    void insert(const int& value);
    void deletion(const int& value);
    int isAvl(Node* node);
    void clear();

private:
    Node* llRotation(Node* node);
    Node* rrRotation(Node* node);
    Node* lrRotation(Node* node);
    Node* rlRotation(Node* node);

    Node* insertHelper(Node* node, const int& value);
    Node* deletionHelper(Node* node, const int& value);
    Node* getMin(Node* node);
    int getHeight(Node* node);
    int getBalance(Node* node);
    void clearHelper(Node* node);

private:
    Node* root;
};