#pragma once
#include <string>

template <typename T>
class myVector {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

public:
    myVector() = default;

    myVector(size_t size, const T& value) : size_(size), capacity_(size) {
        data_ = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data_[i] = value;
        }
    }

    myVector(T* arr, size_t size) : size_(size), capacity_(size) {
        data_ = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data_[i] = arr[i];
        }
    }

    myVector(myVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~myVector() {
        delete[] data_;
    }

    myVector(const myVector& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    myVector<T>& operator=(const myVector& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            resize(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void erase(size_t index) {
        if (index >= size_) return;
        for (size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
    }

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }
};