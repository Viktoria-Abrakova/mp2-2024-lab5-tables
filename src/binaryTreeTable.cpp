#include "binaryTreeTable.h"

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
    }
    return node;
}

void BinaryTreeTable::insert(const std::string& key, const Polynomial& value) {
    root = insert(root, key, value);
}

Polynomial* BinaryTreeTable::find(const std::string& key) {
    TreeNode* node = find(root, key);
    return node ? &node->value : nullptr;
}

TreeNode* BinaryTreeTable::find(TreeNode* node, const std::string& key) {
    if (!node || node->key == key) {
        opCount++;
        return node;
    }
    opCount++;
    if (key < node->key) {
        return find(node->left, key);
    }
    return find(node->right, key);
}

void BinaryTreeTable::remove(const std::string& key) {
    root = remove(root, key);
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
        if (!node->left) {
            TreeNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            TreeNode* temp = node->left;
            delete node;
            return temp;
        }
        TreeNode* temp = minValueNode(node->right);
        node->key = temp->key;
        node->value = temp->value;
        node->right = remove(node->right, temp->key);
    }
    return node;
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
}