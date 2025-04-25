#include "sortedArrayTable.h"

size_t SortedArrayTable::findInsertPos(const std::string& key, size_t& localOpCount) const {
    size_t left = 0;
    size_t right = data.size();
    localOpCount += 2;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        localOpCount += 4; 

        if (data[mid].first < key) {
            left = mid + 1;
            localOpCount += 2; 
        }
        else {
            right = mid;
            localOpCount += 1; 
        }
        localOpCount += 1; 
    }
    return left;
}

void SortedArrayTable::insert(const std::string& key, const Polynomial& value) {
    size_t localOpCount = 0;
    size_t pos = findInsertPos(key, localOpCount);

    if (pos < data.size() && data[pos].first == key) {
        data[pos].second = value;
        localOpCount += 3; 
        opCount += localOpCount;
        std::cout << "SortedArrayTable: updated polynomial '" << key << "', operations: " << localOpCount << std::endl;
        return;
    }
    data.push_back({ "", Polynomial() }); 
    localOpCount += 2; 

    for (size_t i = data.size() - 1; i > pos; --i) {
        data[i] = std::move(data[i - 1]);
        localOpCount += 3;
    }

    data[pos] = { key, value.createDeepCopy() };
    localOpCount += 2;

    opCount += localOpCount;
    std::cout << "SortedArrayTable: inserted polynomial '" << key << "' at position " << pos << ", operations: " << localOpCount << std::endl;
}

Polynomial* SortedArrayTable::find(const std::string& key) {
    size_t localOpCount = 0;
    size_t pos = findInsertPos(key, localOpCount);

    if (pos < data.size() && data[pos].first == key) {
        localOpCount += 2;
        opCount += localOpCount;
        std::cout << "SortedArrayTable: found polynomial '" << key << "' at position " << pos << ", operations: " << localOpCount << std::endl;
        return &data[pos].second;
    }

    opCount += localOpCount;
    std::cout << "SortedArrayTable: polynomial not found, '" << key << "' operations: " << localOpCount << std::endl;
    return nullptr;
}

void SortedArrayTable::remove(const std::string& key) {
    size_t localOpCount = 0;
    size_t pos = findInsertPos(key, localOpCount);

    if (pos < data.size() && data[pos].first == key) {
        localOpCount += 2; 

        for (size_t i = pos; i < data.size() - 1; ++i) {
            data[i] = std::move(data[i + 1]);
            localOpCount += 3;
        }
        data.erase(data.size() - 1);
        localOpCount += 1;

        opCount += localOpCount;
        std::cout << "SortedArrayTable: removed polynomial '" << key << "' from position " << pos << ", operations: " << localOpCount << std::endl;
        return;
    }

    opCount += localOpCount;
    std::cout << "SortedArrayTable: polynomial '" << key << "' not found for removal, operations: " << localOpCount << std::endl;
}

void SortedArrayTable::printStats() const {
    std::cout << "  SortedArrayTable total operations: " << opCount << std::endl;
    std::cout << "  Current size: " << data.size() << std::endl;
    std::cout << "  Memory used: ~" << sizeof(data[0]) * data.size() + sizeof(data) << " bytes" << std::endl;
}