#include "binaryTreeTable.h"

int BinaryTreeTable::height(TreeNode* node, size_t& localOpCount) const {
    localOpCount++;
    return node ? node->height : 0;
}

int BinaryTreeTable::balanceFactor(TreeNode* node, size_t& localOpCount) const {
    int rightHeight = height(node->right, localOpCount);
    int leftHeight = height(node->left, localOpCount);
    localOpCount += 2;
    return rightHeight - leftHeight;
}

void BinaryTreeTable::updateHeight(TreeNode* node, size_t& localOpCount) {
    if (node) {
        int leftHeight = height(node->left, localOpCount);
        int rightHeight = height(node->right, localOpCount);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        localOpCount += 3; 
    }
}

TreeNode* BinaryTreeTable::rotateRight(TreeNode* y, size_t& localOpCount) {
    TreeNode* x = y->left;
    y->left = x->right;
    x->right = y;
    localOpCount += 6; 

    updateHeight(y, localOpCount);
    updateHeight(x, localOpCount);

    return x;
}

TreeNode* BinaryTreeTable::rotateLeft(TreeNode* x, size_t& localOpCount) {
    TreeNode* y = x->right;
    x->right = y->left;
    y->left = x;
    localOpCount += 6; 

    updateHeight(x, localOpCount);
    updateHeight(y, localOpCount);

    return y;
}

TreeNode* BinaryTreeTable::balance(TreeNode* node, size_t& localOpCount) {
    localOpCount++; 
    updateHeight(node, localOpCount);

    int bf = balanceFactor(node, localOpCount);
    if (bf == 2) {
        localOpCount++; 
        if (balanceFactor(node->right, localOpCount) < 0) {
            localOpCount++; 
            node->right = rotateRight(node->right, localOpCount);
        }
        return rotateLeft(node, localOpCount);
    }
    if (bf == -2) {
        localOpCount++; 
        if (balanceFactor(node->left, localOpCount) > 0) {
            localOpCount++; 
            node->left = rotateLeft(node->left, localOpCount);
        }
        return rotateRight(node, localOpCount);
    }
    return node;
}

TreeNode* BinaryTreeTable::insert(TreeNode* node, const std::string& key,
    const Polynomial& value, size_t& localOpCount) {
    if (!node) {
        localOpCount++; 
        return new TreeNode(key, value);
    }
    localOpCount++; 

    if (key < node->key) {
        node->left = insert(node->left, key, value, localOpCount);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, value, localOpCount);
    }
    else {
        localOpCount++; 
        node->value = value;
        return node;
    }

    return balance(node, localOpCount);
}

TreeNode* BinaryTreeTable::remove(TreeNode* node, const std::string& key, size_t& localOpCount) {
    if (!node) return nullptr;
    localOpCount++;

    if (key < node->key) {
        node->left = remove(node->left, key, localOpCount);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key, localOpCount);
    }
    else {
        localOpCount += 2;
        if (!node->left || !node->right) {
            TreeNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }
            localOpCount++;
            delete temp;
        }
        else {
            TreeNode* temp = minValueNode(node->right, localOpCount);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key, localOpCount);
        }
    }

    if (!node) return nullptr;
    return balance(node, localOpCount);
}

void BinaryTreeTable::insert(const std::string& key, const Polynomial& value) {
    size_t localOpCount = 0;
    root = insert(root, key, value.createDeepCopy(), localOpCount);
    opCount += localOpCount;
    std::cout << "BinaryTreeTable: " << (localOpCount > 0 ? "inserted" : "updated") << " polynomial '" << key << "', operations: " << localOpCount << std::endl;
}

void BinaryTreeTable::remove(const std::string& key) {
    size_t localOpCount = 0;
    bool wasFound = (findNode(root, key, localOpCount) != nullptr);
    root = remove(root, key, localOpCount);
    opCount += localOpCount;
    std::cout << "BinaryTreeTable: polynomial '" << key << "' " << (wasFound ? "removed" : "not found for removal") << ", operations: " << localOpCount << std::endl;
}

Polynomial* BinaryTreeTable::find(const std::string& key) {
    size_t localOpCount = 0;
    TreeNode* node = findNode(root, key, localOpCount);
    opCount += localOpCount;
    std::cout << "BinaryTreeTable: " << (node ? "found" : "not found") << " polynomial '" << key << "', operations: " << localOpCount << std::endl;
    return node ? &node->value : nullptr;
}

TreeNode* BinaryTreeTable::findNode(TreeNode* node, const std::string& key, size_t& localOpCount) const {
    if (!node || node->key == key) {
        localOpCount++;
        return node;
    }
    localOpCount++;
    return key < node->key ? findNode(node->left, key, localOpCount)
        : findNode(node->right, key, localOpCount);
}

TreeNode* BinaryTreeTable::minValueNode(TreeNode* node, size_t& localOpCount) {
    while (node && node->left) {
        localOpCount++;
        node = node->left;
    }
    return node;
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

void BinaryTreeTable::printStats() const {
    std::cout << "  BinaryTreeTable total operations: " << opCount << std::endl;
    size_t dummy = 0;
    std::cout << "  Tree height: " << height(root, dummy) << std::endl;
    std::cout << "  Balance factor: " << balanceFactor(root, dummy) << std::endl;
}