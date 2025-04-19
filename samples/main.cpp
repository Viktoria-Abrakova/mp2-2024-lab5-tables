#include <iostream>
#include "polynomial.h"
#include "arrayTable.h"
#include "sortedArrayTable.h"
#include "binaryTreeTable.h"
#include "hashTable.h"


void displayMainMenu() {
    std::cout << "\n=== Main Menu ===\n";
    std::cout << "1. Polynomial Operations\n";
    std::cout << "2. Table Operations\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void displayPolynomialMenu() {
    std::cout << "\n=== Polynomial Operations ===\n";
    std::cout << "1. Add Polynomials\n";
    std::cout << "2. Subtract Polynomials\n";
    std::cout << "3. Multiply by Scalar\n";
    std::cout << "4. Multiply Polynomials\n";
    std::cout << "5. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayTableTypeMenu() {
    std::cout << "\n=== Select Table Type ===\n";
    std::cout << "1. Unsorted Array Table\n";
    std::cout << "2. Sorted Array Table\n";
    std::cout << "3. Binary Search Tree Table\n";
    std::cout << "4. Hash Table\n";
    std::cout << "5. Back to Main Menu\n";
    std::cout << "Enter your choice: ";
}

void displayTableOperationsMenu() {
    std::cout << "\n=== Table Operations ===\n";
    std::cout << "1. Insert Polynomial\n";
    std::cout << "2. Find Polynomial\n";
    std::cout << "3. Remove Polynomial\n";
    std::cout << "4. Print Statistics\n";
    std::cout << "5. Back to Table Selection\n";
    std::cout << "Enter your choice: ";
}

int main() {

    // Инициализация всех таблиц
    ArrayTable arrayTable;
    SortedArrayTable sortedTable;
    BinaryTreeTable treeTable;
    HashTable hashTable;

    Polynomial p1, p2, result;
    int mainChoice, polyChoice, tableOpChoice;
    double scalar;
    std::string key;
 
    while (true) {
        displayMainMenu();
        std::cin >> mainChoice;

        switch (mainChoice) {
        case 1: // Polynomial Operations
            while (true) {
                displayPolynomialMenu();
                std::cin >> polyChoice;

                switch (polyChoice) {
                case 1: // Add
                    std::cout << "Enter first polynomial:\n";
                    p1.inputPolynomial();
                    std::cout << "Enter second polynomial:\n";
                    p2.inputPolynomial();
                    result = p1 + p2;
                    result = result.combineLikeMonomials();
                    std::cout << "Result: ";
                    result.print();

                    // Сохранение во все таблицы
                    std::cout << "\nSave this result to all tables? (y/n): ";
                    char saveChoice;
                    std::cin >> saveChoice;
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        std::cout << "Enter key for saving: ";
                        std::cin >> key;
                        arrayTable.insert(key, result);
                        sortedTable.insert(key, result);
                        treeTable.insert(key, result);
                        hashTable.insert(key, result);
                        std::cout << "Result saved to all tables successfully.\n";
                    }
                    break;

                case 2: // Subtract
                    std::cout << "Enter first polynomial:\n";
                    p1.inputPolynomial();
                    std::cout << "Enter second polynomial:\n";
                    p2.inputPolynomial();
                    result = p1 - p2;
                    result = result.combineLikeMonomials();
                    std::cout << "Result: ";
                    result.print();

                    std::cout << "\nSave this result to all tables? (y/n): ";
                    std::cin >> saveChoice;
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        std::cout << "Enter key for saving: ";
                        std::cin >> key;
                        arrayTable.insert(key, result);
                        sortedTable.insert(key, result);
                        treeTable.insert(key, result);
                        hashTable.insert(key, result);
                        std::cout << "Result saved to all tables successfully.\n";
                    }
                    break;

                case 3: // Multiply by scalar
                    std::cout << "Enter polynomial:\n";
                    p1.inputPolynomial();
                    std::cout << "Enter scalar value: ";
                    std::cin >> scalar;
                    result = p1 * scalar;
                    result = result.combineLikeMonomials();
                    std::cout << "Result: ";
                    result.print();

                    std::cout << "\nSave this result to all tables? (y/n): ";
                    std::cin >> saveChoice;
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        std::cout << "Enter key for saving: ";
                        std::cin >> key;
                        arrayTable.insert(key, result);
                        sortedTable.insert(key, result);
                        treeTable.insert(key, result);
                        hashTable.insert(key, result);
                        std::cout << "Result saved to all tables successfully.\n";
                    }
                    break;

                case 4: // Multiply polynomials
                    std::cout << "Enter first polynomial:\n";
                    p1.inputPolynomial();
                    std::cout << "Enter second polynomial:\n";
                    p2.inputPolynomial();
                    result = p1 * p2;
                    result = result.combineLikeMonomials();
                    std::cout << "Result: ";
                    result.print();

                    std::cout << "\nSave this result to all tables? (y/n): ";
                    std::cin >> saveChoice;
                    if (saveChoice == 'y' || saveChoice == 'Y') {
                        std::cout << "Enter key for saving: ";
                        std::cin >> key;
                        arrayTable.insert(key, result);
                        sortedTable.insert(key, result);
                        treeTable.insert(key, result);
                        hashTable.insert(key, result);
                        std::cout << "Result saved to all tables successfully.\n";
                    }
                    break;

                case 5: // Back
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }

                if (polyChoice == 5) break;
            }
            break;

        case 2: // Table Operations
            while (true) {
                std::cout << "\n=== Table Operations (all tables) ===\n";
                displayTableOperationsMenu();
                std::cin >> tableOpChoice;

                if (tableOpChoice == 5) break;

                switch (tableOpChoice) {
                case 1: // Insert
                    std::cout << "Enter key: ";
                    std::cin >> key;
                    std::cout << "Enter polynomial to store:\n";
                    p1.inputPolynomial();
                    arrayTable.insert(key, p1);
                    sortedTable.insert(key, p1);
                    treeTable.insert(key, p1);
                    hashTable.insert(key, p1);
                    std::cout << "Polynomial stored in all tables successfully.\n";
                    break;

                case 2: // Find
                    std::cout << "Enter key: ";
                    std::cin >> key;
                    std::cout << "\nSearch results:\n";
                    try {
                        std::cout << "1. Unsorted Array Table: ";
                        Polynomial* found = arrayTable.find(key);
                        found->print();
                    }
                    catch (...) {
                        std::cout << "Not found\n";
                    }

                    try {
                        std::cout << "2. Sorted Array Table: ";
                        Polynomial* found = sortedTable.find(key);
                        found->print();
                    }
                    catch (...) {
                        std::cout << "Not found\n";
                    }

                    try {
                        std::cout << "3. Binary Search Tree Table: ";
                        Polynomial* found = treeTable.find(key);
                        found->print();
                    }
                    catch (...) {
                        std::cout << "Not found\n";
                    }

                    try {
                        std::cout << "4. Hash Table: ";
                        Polynomial* found = hashTable.find(key);
                        found->print();
                    }
                    catch (...) {
                        std::cout << "Not found\n";
                    }
                    break;

                case 3: // Remove
                    std::cout << "Enter key: ";
                    std::cin >> key;
                    arrayTable.remove(key);
                    sortedTable.remove(key);
                    treeTable.remove(key);
                    hashTable.remove(key);
                    std::cout << "Polynomial removed from all tables.\n";
                    break;

                case 4: // Stats
                    std::cout << "\nStatistics for all tables:\n";
                    std::cout << "1. Unsorted Array Table:\n";
                    arrayTable.printStats();
                    std::cout << "2. Sorted Array Table:\n";
                    sortedTable.printStats();
                    std::cout << "3. Binary Search Tree Table:\n";
                    treeTable.printStats();
                    std::cout << "4. Hash Table:\n";
                    hashTable.printStats();
                    break;

                case 5: // Back
                    break;

                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
                    break;

        case 3: // Exit
            std::cout << "Exiting...\n";
            return 0;
        
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}