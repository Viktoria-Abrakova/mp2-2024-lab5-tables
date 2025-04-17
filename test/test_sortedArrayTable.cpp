#include <gtest.h>
#include "sortedArrayTable.h"
#include "polynomial.h"

TEST(SortedArrayTableTest, InsertAndFind) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);  

    table.insert("poly1", p1);
    EXPECT_NE(table.find("poly1"), nullptr);
}

TEST(SortedArrayTableTest, FindNonExistent) {
    SortedArrayTable table;

    EXPECT_EQ(table.find("nonexistent"), nullptr);
}

TEST(SortedArrayTableTest, OverwriteValue) {
    SortedArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("poly", p1);
    table.insert("poly", p2);
    EXPECT_EQ(table.find("poly")->getHead_()->monom.coefficient, 1.5);
}

TEST(SortedArrayTableTest, RemoveExisting) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("p1", p1);
    table.remove("p1");
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(SortedArrayTableTest, RemoveNonExistent) {
    SortedArrayTable table;

    EXPECT_NO_THROW(table.remove("nonexistent"));
}

TEST(SortedArrayTableTest, MaintainsOrder) {
    SortedArrayTable table;
    Polynomial p1, p2, p3;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);
    p3.insert(3.0, 1);

    table.insert("b", p1);
    table.insert("a", p2);
    table.insert("c", p3);
    EXPECT_EQ(table.find("a")->getHead_()->monom.coefficient, 1.5);
}

TEST(SortedArrayTableTest, BinarySearchCorrectness) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 9; i >= 0; i--) {
        table.insert(std::to_string(i), p1);
    }
    EXPECT_NE(table.find("5"), nullptr);
}

TEST(SortedArrayTableTest, InsertReverseOrder) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (char c = 'z'; c >= 'a'; c--) {
        table.insert(std::string(1, c), p1);
    }
    EXPECT_NE(table.find("m"), nullptr);
}

TEST(SortedArrayTableTest, InsertRandomOrder) {
    SortedArrayTable table;
    Polynomial p1, p2, p3;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);
    p3.insert(3.0, 1);

    table.insert("m", p1);
    table.insert("a", p2);
    table.insert("z", p3);
    table.insert("b", p1);
    EXPECT_EQ(table.find("a")->getHead_()->monom.coefficient, 1.5);
}

TEST(SortedArrayTableTest, CaseSensitiveOrder) {
    SortedArrayTable table;
    Polynomial p1, p2, p3;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);
    p3.insert(3.0, 1);

    table.insert("Apple", p1);
    table.insert("apple", p2);
    table.insert("Banana", p3);
    EXPECT_NE(table.find("apple"), nullptr);
    EXPECT_NE(table.find("Apple"), nullptr);
}

TEST(SortedArrayTableTest, EmptyTable) {
    SortedArrayTable table;

    EXPECT_EQ(table.find("any"), nullptr);
}

TEST(SortedArrayTableTest, InsertEmptyKey) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("", p1);
    EXPECT_NE(table.find(""), nullptr);
}

TEST(SortedArrayTableTest, LongKeys) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    std::string longKey(1000, 'a');
    table.insert(longKey, p1);
    EXPECT_NE(table.find(longKey), nullptr);
}

TEST(SortedArrayTableTest, SpecialCharsInKeys) {
    SortedArrayTable table;
    Polynomial p1, p2, p3;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);
    p3.insert(3.0, 1);

    table.insert("!@#$", p1);
    table.insert("&*()", p2);
    EXPECT_NE(table.find("!@#$"), nullptr);
}

TEST(SortedArrayTableTest, NullPolynomial) {
    SortedArrayTable table;

    Polynomial nullPoly;
    table.insert("null", nullPoly);
    EXPECT_EQ(table.find("null")->getHead_(), nullptr);
}

TEST(SortedArrayTableTest, MultipleInsert) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 100; i++) {
        table.insert("poly" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("poly50"), nullptr);
}

TEST(SortedArrayTableTest, InsertRemoveSequence) {
    SortedArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("temp", p1);
    table.remove("temp");
    table.insert("temp", p2);
    EXPECT_EQ(table.find("temp")->getHead_()->monom.coefficient, 1.5);
}

TEST(SortedArrayTableTest, RepeatedInsert) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 10; i++) {
        table.insert("repeat", p1);
    }
    EXPECT_EQ(table.find("repeat")->getHead_()->monom.coefficient, 2.5);
}

TEST(SortedArrayTableTest, MultipleRemove) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("p1", p1);
    table.remove("p1");
    table.remove("p1"); 
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(SortedArrayTableTest, MixedOperations) {
    SortedArrayTable table;
    Polynomial p1, p2, p3;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);
    p3.insert(3.0, 1);

    table.insert("a", p1);
    table.insert("b", p2);
    table.remove("a");
    table.insert("c", p3);
    EXPECT_EQ(table.find("a"), nullptr);
    EXPECT_NE(table.find("b"), nullptr);
}

TEST(SortedArrayTableTest, LargeInsert) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; i++) {
        table.insert("big" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("big500"), nullptr);
}

TEST(SortedArrayTableTest, SequentialAccess) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; i++) {
        table.insert("seq" + std::to_string(i), p1);
    }
    for (int i = 0; i < 1000; i++) {
        EXPECT_NE(table.find("seq" + std::to_string(i)), nullptr);
    }
}

TEST(SortedArrayTableTest, RandomAccess) {
    SortedArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; i++) {
        table.insert("rand" + std::to_string(i), p1);
    }
    for (int i = 0; i < 100; i++) {
        int idx = rand() % 1000;
        EXPECT_NE(table.find("rand" + std::to_string(idx)), nullptr);
    }
}

TEST(SortedArrayTableTest, InsertAfterRemove) {
    SortedArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    for (int i = 0; i < 1000; i++) {
        table.insert("temp" + std::to_string(i), p1);
    }
    for (int i = 0; i < 1000; i++) {
        table.remove("temp" + std::to_string(i));
    }
    table.insert("final", p2);
    EXPECT_NE(table.find("final"), nullptr);
}

TEST(SortedArrayTableTest, MixedWorkload) {
    SortedArrayTable table;
    Polynomial p1;
    p1.insert(2.5, 100);

    for (int i = 0; i < 500; i++) {
        table.insert("mix" + std::to_string(i), p1);
    }

    int removed_count = 0;
    for (int i = 5; i < 500; i += 10) {
        std::string key = "mix" + std::to_string(i);
        ASSERT_NE(table.find(key), nullptr);

        table.remove(key);
        removed_count++;

        ASSERT_EQ(table.find(key), nullptr);
    }

    EXPECT_EQ(removed_count, 50);

    EXPECT_EQ(table.find("mix495"), nullptr);
    EXPECT_NE(table.find("mix400"), nullptr);

    int actual_count = 0;
    for (int i = 0; i < 500; i++) {
        if (table.find("mix" + std::to_string(i)) != nullptr) {
            actual_count++;
        }
    }
    EXPECT_EQ(actual_count, 450);
}

TEST(SortedArrayTableTest, DuplicateKeys) {
    SortedArrayTable table;
    Polynomial p1, p2, p3;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);
    p3.insert(3.0, 1);

    table.insert("dup", p1);
    table.insert("dup", p2);
    table.insert("dup", p3);
    EXPECT_EQ(table.find("dup")->getHead_()->monom.coefficient, 3.0);
}

TEST(SortedArrayTableTest, KeyOrderPreservation) {
    SortedArrayTable table;
    Polynomial p1, p2, p3;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);
    p3.insert(3.0, 1);

    table.insert("b", p1);
    table.insert("a", p2);
    table.insert("c", p3);
    table.insert("aa", p1);
    EXPECT_EQ(table.find("a")->getHead_()->monom.coefficient, 1.5);
}

TEST(SortedArrayTableTest, StressTest) {
    SortedArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 10000; i++) {
        table.insert("stress" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("stress5000"), nullptr);
}

TEST(SortedArrayTableTest, ClearAndReuse) {
    SortedArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    for (int i = 0; i < 100; i++) {
        table.insert("tmp" + std::to_string(i), p1);
    }
    for (int i = 0; i < 100; i++) {
        table.remove("tmp" + std::to_string(i));
    }
    table.insert("reused", p2);
    EXPECT_NE(table.find("reused"), nullptr);
}

TEST(SortedArrayTableTest, ComplexPolynomials) {
    SortedArrayTable table;

    Polynomial complex;
    complex.insert(1.5, 300);
    complex.insert(2.5, 200);
    complex.insert(3.5, 100);
    table.insert("complex", complex);
    Polynomial* found = table.find("complex");
    EXPECT_EQ(found->getHead_()->monom.degree, 300);
}