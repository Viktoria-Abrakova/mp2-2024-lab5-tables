#pragma once
#include "table.h"
#include "myvector.h"
#include <string>

struct HashNode {
    std::string key;
    Polynomial value;
    HashNode* next;

    HashNode(const std::string& k, const Polynomial& v)
        : key(k), value(v), next(nullptr) {}
};

class HashTable : public Table {
private:
    myVector<HashNode*> table;
    size_t capacity = 100;
    size_t size_ = 0;
    size_t opCount = 0;

    size_t hash(const std::string& key) const;
    void rehash();

public:
    HashTable();
    ~HashTable();
    void insert(const std::string& key, const Polynomial& value) override;
    Polynomial* find(const std::string& key) override;
    void remove(const std::string& key) override;
    size_t size() const;
    float getLoadFactor() const;
    size_t getMaxBucketSize() const;
    void clear();
    void printStats() const override;
};