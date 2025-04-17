#include <gtest.h>
#include "arrayTable.h"
#include "polynomial.h"

TEST(ArrayTableTest, InsertAndFind) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("poly1", p1);
    EXPECT_NE(table.find("poly1"), nullptr);
}

TEST(ArrayTableTest, FindNonExistent) {
    ArrayTable table;

    EXPECT_EQ(table.find("nonexistent"), nullptr);
}

TEST(ArrayTableTest, OverwriteValue) {
    ArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("poly", p1);
    table.insert("poly", p2);

    EXPECT_EQ(table.find("poly")->getHead_()->monom.coefficient, 1.5);
}

TEST(ArrayTableTest, RemoveExisting) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("p1", p1);
    table.remove("p1");
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(ArrayTableTest, RemoveNonExistent) {
    ArrayTable table;

    EXPECT_NO_THROW(table.remove("nonexistent"));
}

TEST(ArrayTableTest, EmptyTable) {
    ArrayTable table;

    EXPECT_EQ(table.find("any"), nullptr);
}

TEST(ArrayTableTest, InsertEmptyKey) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);
    table.insert("", p1);
    EXPECT_NE(table.find(""), nullptr);
}

TEST(ArrayTableTest, LongKeys) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    std::string longKey(1000, 'a');
    table.insert(longKey, p1);
    EXPECT_NE(table.find(longKey), nullptr);
}

TEST(ArrayTableTest, SpecialCharsInKeys) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("!@#$%^&*()", p1);
    EXPECT_NE(table.find("!@#$%^&*()"), nullptr);
}

TEST(ArrayTableTest, NullPolynomial) {
    ArrayTable table;

    Polynomial nullPoly;
    table.insert("null", nullPoly);
    EXPECT_EQ(table.find("null")->getHead_(), nullptr);
}

TEST(ArrayTableTest, MultipleInsert) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 100; ++i) {
        table.insert("poly" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("poly50"), nullptr);
}

TEST(ArrayTableTest, InsertRemoveSequence) {
    ArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("temp", p1);
    table.remove("temp");
    table.insert("temp", p2);
    EXPECT_EQ(table.find("temp")->getHead_()->monom.coefficient, 1.5);
}

TEST(ArrayTableTest, RepeatedInsert) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 10; ++i) {
        table.insert("repeat", p1);
    }
    EXPECT_EQ(table.find("repeat")->getHead_()->monom.coefficient, 2.5);
}

TEST(ArrayTableTest, MultipleRemove) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("p1", p1);
    table.remove("p1");
    table.remove("p1"); 
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(ArrayTableTest, MixedOperations) {
    ArrayTable table;
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

TEST(ArrayTableTest, ValueIntegrity) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("original", p1);
    Polynomial* found = table.find("original");
    found->insert(4.0, 200);
    EXPECT_EQ(table.find("original")->getHead_()->monom.degree, 200);
}

TEST(ArrayTableTest, IndependentCopies) {
    ArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("copy1", p1);
    ArrayTable newTable = table;
    newTable.insert("copy2", p2);
    EXPECT_EQ(table.find("copy2"), nullptr);
}

TEST(ArrayTableTest, AssignmentOperator) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("orig", p1);
    ArrayTable newTable;
    newTable = table;
    EXPECT_NE(newTable.find("orig"), nullptr);
}

TEST(ArrayTableTest, SelfAssignment) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("self", p1);
    table = table;
    EXPECT_NE(table.find("self"), nullptr);
}

TEST(ArrayTableTest, MoveSemantics) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("move", p1);
    ArrayTable movedTable = std::move(table);
    EXPECT_NE(movedTable.find("move"), nullptr);
}

TEST(ArrayTableTest, LargeInsert) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; ++i) {
        table.insert("big" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("big500"), nullptr);
}

TEST(ArrayTableTest, SequentialAccess) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; ++i) {
        table.insert("seq" + std::to_string(i), p1);
    }
    for (int i = 0; i < 1000; ++i) {
        EXPECT_NE(table.find("seq" + std::to_string(i)), nullptr);
    }
}

TEST(ArrayTableTest, RandomAccess) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; ++i) {
        table.insert("rand" + std::to_string(i), p1);
    }
    for (int i = 0; i < 100; ++i) {
        int idx = rand() % 1000;
        EXPECT_NE(table.find("rand" + std::to_string(idx)), nullptr);
    }
}

TEST(ArrayTableTest, InsertAfterRemove) {
    ArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    for (int i = 0; i < 1000; ++i) {
        table.insert("temp" + std::to_string(i), p1);
    }
    for (int i = 0; i < 1000; ++i) {
        table.remove("temp" + std::to_string(i));
    }
    table.insert("final", p2);
    EXPECT_NE(table.find("final"), nullptr);
}

TEST(ArrayTableTest, MixedWorkload) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    const int TOTAL = 500;
    const int STEP = 10;
    const int OFFSET = 5;

    for (int i = 0; i < TOTAL; ++i) {
        table.insert("mix" + std::to_string(i), p1);
    }

    int removed_count = 0;
    for (int i = OFFSET; i < TOTAL; i += STEP) {
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
    for (int i = 0; i < TOTAL; ++i) {
        if (table.find("mix" + std::to_string(i)) != nullptr) {
            actual_count++;
        }
    }
    EXPECT_EQ(actual_count, TOTAL - 50);
}

TEST(ArrayTableTest, CaseSensitiveKeys) {
    ArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("Case", p1);
    table.insert("case", p2);
    EXPECT_NE(table.find("Case"), nullptr);
    EXPECT_NE(table.find("case"), nullptr);
    EXPECT_NE(table.find("Case")->getHead_()->monom.coefficient,
        table.find("case")->getHead_()->monom.coefficient);
}

TEST(ArrayTableTest, StressTest) {
    ArrayTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 10000; ++i) {
        table.insert("stress" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("stress5000"), nullptr);
}

TEST(ArrayTableTest, ClearAndReuse) {
    ArrayTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    for (int i = 0; i < 100; ++i) {
        table.insert("tmp" + std::to_string(i), p1);
    }
    for (int i = 0; i < 100; ++i) {
        table.remove("tmp" + std::to_string(i));
    }
    table.insert("reused", p2);
    EXPECT_NE(table.find("reused"), nullptr);
}

TEST(ArrayTableTest, ComplexPolynomials) {
    ArrayTable table;

    Polynomial complex;
    complex.insert(1.5, 300);
    complex.insert(2.5, 200);
    complex.insert(3.5, 100);
    table.insert("complex", complex);
    Polynomial* found = table.find("complex");
    EXPECT_EQ(found->getHead_()->monom.degree, 300);
    EXPECT_EQ(found->getHead_()->next->monom.degree, 200);
}