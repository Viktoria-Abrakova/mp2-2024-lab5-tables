#pragma once
#include "monomial.h"

class Polynomial {
private:
    List* head_;
    void clear();
    void copyFrom(const Polynomial& other);

public:
    Polynomial();

    ~Polynomial();

    Polynomial(const Polynomial& other);

    Polynomial clone() const;

    void insert(double coeff, int degree);

    Polynomial& operator=(const Polynomial& other);

    Polynomial operator+(const Polynomial& other);

    Polynomial operator-(const Polynomial& other);

    Polynomial operator*(double scalar);

    Polynomial operator*(const Polynomial& other);

    bool operator==(const Polynomial& other) const;

    Polynomial combineLikeMonomials();

    void inputPolynomial();

    std::string toString() const;
    
    void print() const;

    List* getHead_() const;

    Polynomial createDeepCopy() const;

    bool isSameInstance(const Polynomial& other) const;
};