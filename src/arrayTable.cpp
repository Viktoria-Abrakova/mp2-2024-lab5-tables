#include "arrayTable.h"

void ArrayTable::insert(const std::string& key, const Polynomial& value) {
    opCount++;
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].first == key) {
            data[i].second = value;  
            return;
        }
    }
    data.push_back({ key, value.createDeepCopy() });
}

Polynomial* ArrayTable::find(const std::string& key) {
   for (size_t i = 0; i < data.size(); ++i) {
        opCount++;
        if (data[i].first == key) {
            return &data[i].second;
        }
    }
    return nullptr;
}

void ArrayTable::remove(const std::string& key) {
    for (size_t i = 0; i < data.size(); ++i) {
        opCount++;
        if (data[i].first == key) {
            data.erase(i);
            return;
        }
    }
}

void ArrayTable::printStats() const {
    std::cout << "ArrayTable operations: " << opCount << std::endl;
}