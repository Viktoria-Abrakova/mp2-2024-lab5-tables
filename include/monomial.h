#pragma once
#include <iostream>

struct Monomial {

    double coefficient;
    int degree; 

    Monomial() : coefficient(0.0), degree(0) {}

    Monomial(double coeff, int x, int y, int z) : coefficient(coeff), degree(x * 100 + y * 10 + z) {
        if ((x < 0 || x > 9) || (y < 0 || y > 9) || (z < 0 || z > 9)) {
            throw std::out_of_range("The degree must be in the range from 0 to 9.");
        }
    }

};

struct List {
    Monomial monom;
    List* next;
    List() :next(nullptr) {}
    List(Monomial monom) : next(nullptr), monom(monom) {}

};