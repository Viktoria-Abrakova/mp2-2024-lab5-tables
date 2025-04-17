#pragma once
#include "table.h"
#include <string>

struct TreeNode {
    std::string key;
    Polynomial value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(std::string k, Polynomial v) : key(std::move(k)), value(std::move(v)) {}
};

class BinaryTreeTable : public Table {
private:
    TreeNode* root = nullptr;
    size_t opCount = 0;

    TreeNode* insert(TreeNode* node, const std::string& key, const Polynomial& value);
    TreeNode* find(TreeNode* node, const std::string& key);
    TreeNode* remove(TreeNode* node, const std::string& key);
    TreeNode* minValueNode(TreeNode* node);
    void clear(TreeNode* node);

public:
    ~BinaryTreeTable() override;
    void insert(const std::string& key, const Polynomial& value) override;
    Polynomial* find(const std::string& key) override;
    void remove(const std::string& key) override;
    void printStats() const override;
};