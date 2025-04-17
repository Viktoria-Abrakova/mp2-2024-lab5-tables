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
    ArrayTable arrayTable;
    SortedArrayTable sortedTable;
    BinaryTreeTable treeTable;  
    HashTable hashTable;

    Polynomial p1, p2, result;
    int mainChoice, polyChoice, tableTypeChoice, tableOpChoice;
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
                displayTableTypeMenu();
                std::cin >> tableTypeChoice;

                if (tableTypeChoice == 5) break;

                Table* currentTable = nullptr;
                std::string tableName;

                switch (tableTypeChoice) {
                case 1:
                    currentTable = &arrayTable;
                    tableName = "Unsorted Array Table";
                    break;
                case 2:
                    currentTable = &sortedTable;
                    tableName = "Sorted Array Table";
                    break;
                case 3:  
                    currentTable = &treeTable;
                    tableName = "Binary Search Tree Table";
                    break;
                case 4:
                    currentTable = &hashTable;
                    tableName = "Hash Table";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    continue;
                }

                while (true) {
                    std::cout << "\nCurrent table: " << tableName << "\n";
                    displayTableOperationsMenu();
                    std::cin >> tableOpChoice;

                    switch (tableOpChoice) {
                    case 1: // Insert
                        std::cout << "Enter key: ";
                        std::cin >> key;
                        std::cout << "Enter polynomial to store:\n";
                        p1.inputPolynomial();
                        currentTable->insert(key, p1);
                        std::cout << "Polynomial stored successfully.\n";
                        break;

                    case 2: // Find
                        std::cout << "Enter key: ";
                        std::cin >> key;
                        if (Polynomial* found = currentTable->find(key)) {
                            std::cout << "Found polynomial: ";
                            found->print();
                        }
                        else {
                            std::cout << "Polynomial not found.\n";
                        }
                        break;

                    case 3: // Remove
                        std::cout << "Enter key: ";
                        std::cin >> key;
                        currentTable->remove(key);
                        std::cout << "Operation completed.\n";
                        break;

                    case 4: // Stats
                        currentTable->printStats();
                        break;

                    case 5: // Back
                        break;

                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                    }

                    if (tableOpChoice == 5) break;
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