#pragma once
#include "table.h"
#include "myvector.h"
#include <string>

struct HashNode {
    std::string key;
    Polynomial value;
    HashNode* next = nullptr;
    HashNode(std::string k, Polynomial v) : key(std::move(k)), value(std::move(v)) {}
};

class HashTable : public Table {
private:
    myVector<HashNode*> table;
    size_t capacity = 100;
    size_t size_ = 0;
    size_t opCount = 0;

    size_t hash(const std::string& key) const;

public:
    HashTable();
    ~HashTable();
    void insert(const std::string& key, const Polynomial& value) override;
    Polynomial* find(const std::string& key) override;
    void remove(const std::string& key) override;
    size_t size() const;
    float getLoadFactor() const;
    void rehash();
    size_t getMaxBucketSize() const;
    void clear();
    void printStats() const override;
};