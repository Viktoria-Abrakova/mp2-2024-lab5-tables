#pragma once
#include "polynomial.h"
#include <string>

class Table {
public:
    virtual ~Table() = default;

    virtual void insert(const std::string& key, const Polynomial& value) = 0;
    virtual void remove(const std::string& key) = 0;
    virtual Polynomial* find(const std::string& key) = 0;
    virtual void printStats() const = 0;
};