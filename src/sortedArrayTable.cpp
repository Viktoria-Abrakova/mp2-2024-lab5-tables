#include "sortedArrayTable.h"

size_t SortedArrayTable::findInsertPos(const std::string& key) const {
    size_t left = 0;
    size_t right = data.size();
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (data[mid].first < key) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    return left;
}

void SortedArrayTable::insert(const std::string& key, const Polynomial& value) {
    size_t pos = findInsertPos(key);
    data.push_back({ "", Polynomial() }); 
    for (size_t i = data.size() - 1; i > pos; --i) {
        data[i] = data[i - 1];
    }
    data[pos] = { key, value.createDeepCopy() };
    opCount += pos;
}

Polynomial* SortedArrayTable::find(const std::string& key) {
    size_t pos = findInsertPos(key);
    if (pos < data.size() && data[pos].first == key) {
        return &data[pos].second;
    }
    return nullptr;
}

void SortedArrayTable::remove(const std::string& key) {
    size_t pos = findInsertPos(key);
    if (pos < data.size() && data[pos].first == key) {
        for (size_t i = pos; i < data.size() - 1; ++i) {
            data[i] = data[i + 1];
        }
        data.erase(data.size() - 1);
    }
    opCount += pos;
}

void SortedArrayTable::printStats() const {
    std::cout << "SortedArrayTable operations: " << opCount << std::endl;
}