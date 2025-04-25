#include "arrayTable.h"

void ArrayTable::insert(const std::string& key, const Polynomial& value) {
    size_t localOpCount = 0;  
    localOpCount++;          

    for (size_t i = 0; i < data.size(); ++i) {
        localOpCount++;  
        if (data[i].first == key) {
            localOpCount++; 
            data[i].second = value;
            opCount += localOpCount;  
            std::cout << "ArrayTable: updated polynomial '" << key << "' operations: " << localOpCount << std::endl;
            return;
        }
    }

    localOpCount++;  
    data.push_back({ key, value.createDeepCopy() });
    opCount += localOpCount;  
    std::cout << "ArrayTable: inserted new polynomial '" << key << "', operations: " << localOpCount << std::endl;
}

Polynomial* ArrayTable::find(const std::string& key) {
    size_t localOpCount = 0;
    localOpCount++;          

    for (size_t i = 0; i < data.size(); ++i) {
        localOpCount++;  
        if (data[i].first == key) {
            opCount += localOpCount;  
            std::cout << "ArrayTable: found polynomial '" << key << "', operations: " << localOpCount << std::endl;
            return &data[i].second;
        }
    }

    opCount += localOpCount;  
    std::cout << "ArrayTable: polynomial not found, '" << key << "' operations: " << localOpCount << std::endl;
    return nullptr;
}

void ArrayTable::remove(const std::string& key) {
    size_t localOpCount = 0;  
    localOpCount++;          

    for (size_t i = 0; i < data.size(); ++i) {
        localOpCount++;  
        if (data[i].first == key) {
            localOpCount++;  
            data.erase(i);
            opCount += localOpCount;  
            std::cout << "ArrayTable: removed polynomial '" << key << "', operations: " << localOpCount << std::endl;
            return;
        }
    }

    opCount += localOpCount;  
    std::cout << "ArrayTable: polynomial '" << key << "' not found for removal, operations: " << localOpCount << std::endl;
}

void ArrayTable::printStats() const {
    std::cout << "  ArrayTable total operations: " << opCount << std::endl;
    std::cout << "  Current size: " << data.size() << std::endl;
    std::cout << "  Memory used: ~" << sizeof(data[0]) * data.size() + sizeof(data) << " bytes" << std::endl;
}