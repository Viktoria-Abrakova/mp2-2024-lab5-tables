#pragma once
#include "table.h"
#include "myvector.h"
#include <string>

class ArrayTable : public Table {
private:
    myVector<std::pair<std::string, Polynomial>> data;
    size_t opCount = 0;

public:
    void insert(const std::string& key, const Polynomial& value) override;
    Polynomial* find(const std::string& key) override;
    void remove(const std::string& key) override;
    void printStats() const override;
};