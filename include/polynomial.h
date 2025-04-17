#pragma once
#include "monomial.h"

class Polynomial {
private:
    List* head_;

public:
    Polynomial();

    ~Polynomial();

    Polynomial(const Polynomial& other);

    void insert(double coeff, int degree);

    Polynomial& operator=(const Polynomial& other);

    Polynomial operator+(const Polynomial& other);

    Polynomial operator-(const Polynomial& other);

    Polynomial operator*(double scalar);

    Polynomial operator*(const Polynomial& other);

    Polynomial combineLikeMonomials();

    void inputPolynomial();
    
    void print() const;

    List* getHead_() const;
};