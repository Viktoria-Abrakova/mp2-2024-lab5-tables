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

    int height(TreeNode* node) const;
    void updateHeight(TreeNode* node);
    int balanceFactor(TreeNode* node) const;
    TreeNode* rotateRight(TreeNode* y);
    TreeNode* rotateLeft(TreeNode* x);
    TreeNode* balance(TreeNode* node);
    TreeNode* insert(TreeNode* node, const std::string& key, const Polynomial& value);
    TreeNode* remove(TreeNode* node, const std::string& key);
    TreeNode* findNode(TreeNode* node, const std::string& key) const;
    TreeNode* minValueNode(TreeNode* node);
    void clear(TreeNode* node);

public:
    BinaryTreeTable();
    ~BinaryTreeTable();

    void insert(const std::string& key, const Polynomial& value) override;
    void remove(const std::string& key) override;
    Polynomial* find(const std::string& key) override;
    void printStats() const override;
};