#include "HashTable.h"

HashTable::HashTable() {
    for (size_t i = 0; i < capacity; ++i) {
        table.push_back(nullptr);
    }
}

HashTable::~HashTable() {
    for (size_t i = 0; i < capacity; ++i) {
        HashNode* node = table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            delete temp;
        }
    }
}

size_t HashTable::hash(const std::string& key, size_t& localOpCount) const {
    size_t hash = 0;
    const size_t prime = 31;
    for (char c : key) {
        hash = hash * prime + static_cast<size_t>(c);
        localOpCount += 2; 
    }
    localOpCount++; 
    return hash % capacity;
}

void HashTable::insert(const std::string& key, const Polynomial& value) {
    size_t localOpCount = 0;

    if (static_cast<float>(size_ + 1) / capacity > 0.75f) {
        rehash(localOpCount);
    }

    size_t index = hash(key, localOpCount) % capacity;
    localOpCount++;

    HashNode* node = table[index];
    while (node != nullptr) {
        localOpCount++; 
        if (node->key == key) {
            node->value = value;
            localOpCount++; 
            opCount += localOpCount;
            std::cout << "HashTable: updated polynomial '" << key << "', operations: " << localOpCount << std::endl;
            return;
        }
        localOpCount++;
        node = node->next;
    }

    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    size_++;
    localOpCount += 4;

    opCount += localOpCount;
    std::cout << "HashTable: inserted polynomial '" << key << "', operations: " << localOpCount << std::endl;
}

Polynomial* HashTable::find(const std::string& key) {
    size_t localOpCount = 0;
    size_t index = hash(key, localOpCount);
    HashNode* node = table[index];

    while (node) {
        localOpCount++; 
        if (node->key == key) {
            opCount += localOpCount;
            std::cout << "HashTable: found polynomial '" << key << "', operations: " << localOpCount << std::endl;
            return &node->value;
        }
        localOpCount++; 
        node = node->next;
    }

    opCount += localOpCount;
    std::cout << "HashTable: polynomial not found, '" << key << "' operations: " << localOpCount << std::endl;
    return nullptr;
}


void HashTable::remove(const std::string& key) {
    size_t localOpCount = 0;
    size_t index = hash(key, localOpCount) % capacity;
    localOpCount++; 

    HashNode* prev = nullptr;
    HashNode* current = table[index];

    while (current != nullptr) {
        localOpCount++;
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            size_--;
            localOpCount += 4; 

            opCount += localOpCount;
            std::cout << "HashTable: removed polynomial '" << key << "', operations: " << localOpCount << std::endl;
            return;
        }
        prev = current;
        current = current->next;
        localOpCount++; 
    }

    opCount += localOpCount;
    std::cout << "HashTable: polynomial '" << key << "' not found for removal, operations: " << localOpCount << std::endl;
}

size_t HashTable::size() const {
    return size_;
}

float HashTable::getLoadFactor() const {
    return static_cast<float>(size_) / capacity;
}

size_t HashTable::getMaxBucketSize() const {
    size_t maxSize = 0;
    for (size_t i = 0; i < capacity; ++i) {
        size_t bucketSize = 0;
        HashNode* node = table[i];
        while (node != nullptr) {
            ++bucketSize;
            node = node->next;
        }
        if (bucketSize > maxSize) {
            maxSize = bucketSize;
        }
    }
    return maxSize;
}

void HashTable::rehash(size_t& localOpCount) {
    const size_t newCapacity = capacity == 0 ? 16 : capacity * 2;
    myVector<HashNode*> newTable(newCapacity, nullptr);

    myVector<HashNode*> oldTable = std::move(table);
    size_t oldSize = size_;

    table = std::move(newTable);
    capacity = newCapacity;
    size_ = 0;

    for (size_t i = 0; i < oldTable.size(); ++i) {
        HashNode* node = oldTable[i];
        while (node != nullptr) {
            HashNode* nextNode = node->next;

            size_t newIndex = hash(node->key, localOpCount) % capacity;

            node->next = table[newIndex];
            table[newIndex] = node;
            size_++;

            node = nextNode;
            localOpCount += 5;
        }
    }
    localOpCount += 2; 
}

void HashTable::clear() {
    for (size_t i = 0; i < capacity; ++i) {
        HashNode* node = table[i];
        while (node != nullptr) {
            HashNode* temp = node;
            node = node->next;
            delete temp;
        }
        table[i] = nullptr;
    }
    size_ = 0;
}

void HashTable::printStats() const {
    std::cout << "  HashTable total operations: " << opCount << std::endl;
    std::cout << "  Size: " << size_ << std::endl;
    std::cout << "  Capacity: " << capacity << std::endl;
    std::cout << "  Load factor: " << static_cast<float>(size_) / capacity << std::endl;
    std::cout << "  Max bucket size: " << getMaxBucketSize() << std::endl;
}