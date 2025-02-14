#include "avl.hpp"


AVL::AVL() : root(nullptr) {}
AVL::~AVL() {
    clear();
}

Node* AVL::llRotation(Node* node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    tmp->height = std::max(getHeight(tmp->left), node->height) + 1;

    return tmp;
}

Node* AVL::rrRotation(Node* node) {
    Node* tmp = node->right;
    node->right = tmp->right;
    tmp->left = node;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    tmp->height = std::max(node->height, getHeight(tmp->right)) + 1;

    return tmp;
}

Node* AVL::lrRotation(Node* node) {
    node->left = rrRotation(node->left);
    return llRotation(node);
}

Node* AVL::rlRotation(Node* node) {
    node->right = llRotation(node->right);
    return rrRotation(node);
}

int AVL::getHeight(Node* node) {
    if (!node) return -1;

    return node->height;
}

int AVL::getBalance(Node* node) {
    if (!node) return -1;

    return getHeight(node->left) - getHeight(node->right);
}

Node* AVL::insertHelper(Node* node, const int& value) {
    if (!node) return new Node(value);

    if (node->val > value) {
        node->left = insertHelper(node->left, value);
    }
    else {
        node->right = insertHelper(node->right, value);
    }

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int b = getBalance(node);

    if (b > 1 && value < node->left->val) {
        llRotation(node);
    }

    if (b > 1 && value > node->left->val) {
        lrRotation(node);
    }

    if (b < -1 && value > node->right->val) {
        rrRotation(node);
    }

    if (b < -1 && value < node->right->val) {
        rlRotation(node);
    }

    return node;
}

void AVL::insert(const int& value) {
    root = insertHelper(root, value);
}

Node* AVL::getMin(Node* node) {
    if (!node) return node;

    if (node->left) {
        return getMin(node->left);
    }

    return node;
}

Node* AVL::deletionHelper(Node* node, const int& value) {
    if (!node) return node;

    if (node->val > value) {
        node->left = deletionHelper(node->left, value);
    }
    else if (node->val < value) {
        node->right = deletionHelper(node->right, value);
    }
    else {
        if (node->right && node->left) {
            Node* tmp = getMin(node->left);
            node->val = tmp->val;
            node->left = deletionHelper(node->left, tmp->val);
        }
        else {
            Node* tmp = node->left ? node->left : node->right;

            if (!tmp) {
                tmp = node;
                node = nullptr;
            }
            else {
                root->val = tmp->val;
            }
            delete(tmp);
        }
    }

    if (!node) return node;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

    int b = getBalance(node);

    if (b > 1 && value < node->left->val) {
        llRotation(node);
    }

    if (b > 1 && value > node->left->val) {
        lrRotation(node);
    }

    if (b < -1 && value > node->right->val) {
        rrRotation(node);
    }

    if (b < -1 && value < node->right->val) {
        rlRotation(node);
    }

    return node;
}

void AVL::deletion(const int& value) {
    root = deletionHelper(root, value);
}

void AVL::clearHelper(Node* node) {
    if (!node) return;

    clearHelper(node->left);
    clearHelper(node->right);

    delete node;
    node = nullptr;
}

void AVL::clear() {
    clearHelper(root);
}

int AVL::isAvl(Node* node) {
    if (!node) return 0;

    int left = isAvl(node->left);
    if (left == -1) {
        return -1;
    }

    int right = isAvl(node->right);
    if (right == -1) {
        return -1;
    }

    if (std::abs(right - left) > 1) {
        return -1;
    }

    return std::max(right, left) + 1;
}