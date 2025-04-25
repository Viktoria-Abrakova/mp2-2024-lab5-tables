#pragma once
#include "table.h"
#include <string>


struct TreeNode {
    std::string key;
    Polynomial value;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(const std::string& k, const Polynomial& v)
        : key(k), value(v), left(nullptr), right(nullptr), height(1) {
    }
};

class BinaryTreeTable : public Table {
private:

    TreeNode* root;
    mutable int opCount;

    int height(TreeNode* node, size_t& localOpCount) const;
    void updateHeight(TreeNode* node, size_t& localOpCount);
    int balanceFactor(TreeNode* node, size_t& localOpCount) const;
    TreeNode* rotateRight(TreeNode* y, size_t& localOpCount);
    TreeNode* rotateLeft(TreeNode* x, size_t& localOpCount);
    TreeNode* balance(TreeNode* node, size_t& localOpCount);
    TreeNode* insert(TreeNode* node, const std::string& key, const Polynomial& value, size_t& localOpCount);
    TreeNode* remove(TreeNode* node, const std::string& key, size_t& localOpCount);
    TreeNode* findNode(TreeNode* node, const std::string& key, size_t& localOpCount) const;
    TreeNode* minValueNode(TreeNode* node, size_t& localOpCount);
    void clear(TreeNode* node);

public:
    BinaryTreeTable();
    ~BinaryTreeTable();

    void insert(const std::string& key, const Polynomial& value) override;
    void remove(const std::string& key) override;
    Polynomial* find(const std::string& key) override;
    void printStats() const override;
};