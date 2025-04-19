#include "binaryTreeTable.h"

int BinaryTreeTable::height(TreeNode* node) const {
    return node ? node->height : 0;
}

int BinaryTreeTable::balanceFactor(TreeNode* node) const{
    return height(node->right) - height(node->left);
}

void BinaryTreeTable::updateHeight(TreeNode* node) {
        if (node) {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

TreeNode* BinaryTreeTable::rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    y->left = x->right;
    x->right = y;

    updateHeight(y);
    updateHeight(x);

    return x;
}

TreeNode* BinaryTreeTable::rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    x->right = y->left;
    y->left = x;

    updateHeight(x);
    updateHeight(y);

    return y;
}

TreeNode* BinaryTreeTable::balance(TreeNode* node) {
    updateHeight(node);

    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

TreeNode* BinaryTreeTable::insert(TreeNode* node, const std::string& key, const Polynomial& value) {
    if (!node) {
        return new TreeNode(key, value);
    }
    opCount++;

    if (key < node->key) {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, value);
    }
    else {
        node->value = value;
        return node; 
    }

    return balance(node);
}

TreeNode* BinaryTreeTable::remove(TreeNode* node, const std::string& key) {
    if (!node) return nullptr;
    opCount++;

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (!node->left || !node->right) {
            TreeNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp; 
            }
            delete temp;
        }
        else {
            TreeNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
    }

    if (!node) return nullptr;

    return balance(node);
}

BinaryTreeTable::BinaryTreeTable() : root(nullptr), opCount(0) {}

BinaryTreeTable::~BinaryTreeTable() {
    clear(root);
}

void BinaryTreeTable::clear(TreeNode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BinaryTreeTable::insert(const std::string& key, const Polynomial& value) {
    root = insert(root, key, value.createDeepCopy());
}

void BinaryTreeTable::remove(const std::string& key) {
    root = remove(root, key);
}

Polynomial* BinaryTreeTable::find(const std::string& key) {
    TreeNode* node = findNode(root, key);
    if (node) {
        return node ? &node->value : nullptr;
    }
    return nullptr;
}

TreeNode* BinaryTreeTable::findNode(TreeNode* node, const std::string& key) const {
    if (!node || node->key == key) {
        opCount++;
        return node;
    }
    opCount++;
    return key < node->key ? findNode(node->left, key) : findNode(node->right, key);
}

TreeNode* BinaryTreeTable::minValueNode(TreeNode* node) {
    while (node && node->left) {
        opCount++;
        node = node->left;
    }
    return node;
}

void BinaryTreeTable::printStats() const {
    std::cout << "BinaryTreeTable operations: " << opCount << std::endl;
    std::cout << "Tree height: " << height(root) << std::endl;
}