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

size_t HashTable::hash(const std::string& key) const {
    size_t hash = 0;
    const size_t prime = 31;
    for (char c : key) {
        hash = hash * prime + static_cast<size_t>(c);
    }
    return hash % capacity;
}

void HashTable::insert(const std::string& key, const Polynomial& value) {
    if (static_cast<float>(size_ + 1) / capacity > 0.75f) {
        rehash();
    }

    size_t index = hash(key) % capacity;

    HashNode* node = table[index];
    while (node != nullptr) {
        if (node->key == key) {
            node->value = value; 
            return;
        }
        node = node->next;
    }

    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;
    size_++;
}

Polynomial* HashTable::find(const std::string& key) {
    size_t index = hash(key);
    HashNode* node = table[index];
    while (node) {
        opCount++;
        if (node->key == key) {
            return &node->value;
        }
        node = node->next;
    }
    return nullptr;
}

void HashTable::remove(const std::string& key) {
    size_t index = hash(key) % capacity;
    HashNode* prev = nullptr;
    HashNode* current = table[index];

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next; 
            }
            else {
                prev->next = current->next;   
            }

            delete current;
            size_--;
            return;  
        }

        prev = current;
        current = current->next;
    }
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

void HashTable::rehash() {
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

            size_t newIndex = hash(node->key) % capacity;

            node->next = table[newIndex];
            table[newIndex] = node;
            size_++;

            node = nextNode;
        }
    }
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
    opCount = 0;     
}

void HashTable::printStats() const {
    std::cout << "HashTable operations: " << opCount << std::endl;
}