#pragma once
#include <iostream>
#include <string>

struct Monomial {

    double coefficient;
    int degree; 

    Monomial() : coefficient(0.0), degree(0) {}

    Monomial(double coeff, int x, int y, int z) : coefficient(coeff), degree(x * 100 + y * 10 + z) {
        if ((x < 0 || x > 9) || (y < 0 || y > 9) || (z < 0 || z > 9)) {
            throw std::out_of_range("The degree must be in the range from 0 to 9.");
        }
    }

    std::string toString() const {
        std::string result;
        if (coefficient == 0) return "0";

        result = std::to_string(coefficient);

        int x = degree / 100;
        int y = (degree / 10) % 10;
        int z = degree % 10;

        if (x > 0) result += "x^" + std::to_string(x);
        if (y > 0) result += "y^" + std::to_string(y);
        if (z > 0) result += "z^" + std::to_string(z);

        return result;
    }

};

struct List {
    Monomial monom;
    List* next;
    List() :next(nullptr) {}
    List(Monomial monom) : next(nullptr), monom(monom) {}
    List(double coeff, int deg, List* nxt = nullptr)
        : monom(coeff, deg / 100, (deg / 10) % 10, deg % 10), next(nxt) {
    }
};