#include "polynomial.h"

void Polynomial::clear() {
    while (head_) {
        List* temp = head_;
        head_ = head_->next;
        delete temp;
    }
}

void Polynomial::copyFrom(const Polynomial& other) {
    List** current = &head_;
    List* src = other.head_;

    while (src) {
        *current = new List(src->monom.coefficient, src->monom.degree);
        current = &((*current)->next);
        src = src->next;
    }
}

Polynomial::Polynomial() : head_(nullptr) {}

Polynomial::~Polynomial() {
    clear();
}

Polynomial::Polynomial(const Polynomial& other) : head_(nullptr) {
    copyFrom(other);
}

Polynomial Polynomial:: clone() const {
    return *this; 
}

void Polynomial::insert(double coeff, int degree) {
    if (degree < 0 || degree > 999) {
        throw std::out_of_range("Degree must be 0-999");
    }

    List* new_List = new List(coeff, degree);

    if (!head_ || degree > head_->monom.degree) {
        new_List->next = head_;
        head_ = new_List;
    }
    else {
        List* current = head_;
        while (current->next && current->next->monom.degree > degree) {
            current = current->next;
        }
        new_List->next = current->next;
        current->next = new_List;
    }
}


Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& other) {
    Polynomial result;
    List* p1 = head_;
    List* p2 = other.head_;

    while (p1 && p2) {
        if (p1->monom.degree == p2->monom.degree) {
            double newCoefficient = p1->monom.coefficient + p2->monom.coefficient;
            if (newCoefficient != 0) {
                result.insert(newCoefficient, p1->monom.degree);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->monom.degree > p2->monom.degree) {
            result.insert(p1->monom.coefficient, p1->monom.degree);
            p1 = p1->next;
        }
        else {
            result.insert(p2->monom.coefficient, p2->monom.degree);
            p2 = p2->next;
        }
    }
    while (p1) {
        result.insert(p1->monom.coefficient, p1->monom.degree);
        p1 = p1->next;
    }
    while (p2) {
        result.insert(p2->monom.coefficient, p2->monom.degree);
        p2 = p2->next;
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) {
    Polynomial result;
    List* p1 = head_;
    List* p2 = other.head_;

    while (p1 || p2) {
        if (!p1) {
            double newCoefficient = -p2->monom.coefficient;
            if (newCoefficient != 0) {
                result.insert(newCoefficient, p2->monom.degree);
                p2 = p2->next;
            }
        }
        else if (!p2) {
            result.insert(p1->monom.coefficient, p1->monom.degree); 
            p1 = p1->next;
        }
        else if (p1->monom.degree == p2->monom.degree) {
            double newCoefficient = p1->monom.coefficient - p2->monom.coefficient;
            if (newCoefficient != 0) { 
                result.insert(newCoefficient, p1->monom.degree);
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->monom.degree > p2->monom.degree) {
            result.insert(p1->monom.coefficient, p1->monom.degree); 
            p1 = p1->next;
        }
        else {
            double newCoefficient = -p2->monom.coefficient;
            if (newCoefficient != 0) { 
                result.insert(newCoefficient, p2->monom.degree);
            }
            p2 = p2->next;
        }
    }
    return result;
}

Polynomial Polynomial::operator*(double scalar) {
    Polynomial result;
    List* current = head_;
    while (current) {
        double newCoefficient = current->monom.coefficient * scalar;
        if (newCoefficient != 0) { 
            result.insert(newCoefficient, current->monom.degree);
        }
        current = current->next;
    }
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) {
    Polynomial result;
    List* p1 = head_;

    while (p1) {
        Polynomial temp;
        List* p2 = other.head_;
        while (p2) {
            double newCoefficient = p1->monom.coefficient * p2->monom.coefficient;
            int newDegree = p1->monom.degree + p2->monom.degree;
            if (newDegree < 0 || newDegree > 999) {
                throw std::out_of_range("The monom.degree must be in the range from 0 to 9.");
            }
            if (newCoefficient != 0) { 
                temp.insert(newCoefficient, newDegree);
            }
            p2 = p2->next;
        }
        result = result + temp;
        p1 = p1->next;
    }
    return result;
}

bool Polynomial::operator==(const Polynomial& other) const {
    List* curr1 = head_;
    List* curr2 = other.head_;
    while (curr1 && curr2) {
        if (curr1->monom.coefficient != curr2->monom.coefficient ||
            curr1->monom.degree != curr2->monom.degree) {
            return false;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    return curr1 == nullptr && curr2 == nullptr;
}

Polynomial Polynomial::combineLikeMonomials() {
    Polynomial result;
    List* current = head_;

    while (current) {
        double coefficientSum = current->monom.coefficient;
        int degree = current->monom.degree;
        List* temp = current->next;
        while (temp && temp->monom.degree == degree) {
            coefficientSum += temp->monom.coefficient;
            temp = temp->next;
        }
        if (coefficientSum != 0) {
            result.insert(coefficientSum, degree);
        }
        current = temp; 
    }
    return result;
}

void Polynomial::inputPolynomial() {
    int degree;
    double coefficient;

    std::cout << "Enter the number of Polynomial Monomials:";
    int monomials;
    std::cin >> monomials;

    for (int i = 0; i < monomials; ++i) {
        std::cout << "Enter the monom.coefficient and monom.degree for the Monomial " << (i + 1) << ": "; 
        std::cin >> coefficient >> degree; 
        if (coefficient != 0) {
            insert(coefficient, degree); 
        }
    }
}

std::string Polynomial::toString() const {
    std::string result;
    List* current = head_;
    bool first = true;

    while (current) {
        if (!first && current->monom.coefficient > 0) {
            result += " + ";
        }
        result += current->monom.toString();
        first = false;
        current = current->next;
    }

    return result.empty() ? "0" : result;
}

void Polynomial::print() const {
    if (head_ == nullptr) {
        std::cout << "0";
        return;
    }
    List* current = head_;
    bool first = true;
    while (current != nullptr) {
        if (current->monom.coefficient == 0) {
            current = current->next;
            continue;
        }
        if (!first) {
            std::cout << (current->monom.coefficient > 0 ? " + " : " - ");
        }
        else if (current->monom.coefficient < 0) {
            std::cout << "-";
        }
        if (std::abs(current->monom.coefficient) != 1 || current->monom.degree == 0) {
            std::cout << std::abs(current->monom.coefficient);
        }
        int x = current->monom.degree / 100;
        int y = (current->monom.degree / 10) % 10;
        int z = current->monom.degree % 10;
        if (x != 0) {
            std::cout << "x^" << x;
        }
        if (y != 0) {
            std::cout << "y^" << y;
        }
        if (z != 0) {
            std::cout << "z^" << z;
        }
        first = false;
        current = current->next;
    }
    std::cout << std::endl;
}

List* Polynomial::getHead_() const {
    return head_;
}

Polynomial Polynomial::createDeepCopy() const {
    Polynomial result;
    List* current = head_;
    List** tail = &result.head_;

    while (current) {
        *tail = new List(current->monom);
        tail = &((*tail)->next);
        current = current->next;
    }

    return result;
}

bool Polynomial::isSameInstance(const Polynomial& other) const {
    return this == &other;
}