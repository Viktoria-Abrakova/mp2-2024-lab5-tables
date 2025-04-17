#include <gtest.h>
#include "binaryTreeTable.h"

TEST(BinaryTreeTableTest, EmptyTree) {
    BinaryTreeTable table;
    EXPECT_EQ(table.find("any"), nullptr);
}

TEST(BinaryTreeTableTest, SingleInsert) {
    BinaryTreeTable table;
    Polynomial p;
    p.insert(1.5, 2);
    table.insert("key1", p);
    EXPECT_NE(table.find("key1"), nullptr);
}

TEST(BinaryTreeTableTest, FindInEmpty) {
    BinaryTreeTable table;
    EXPECT_EQ(table.find("nonexistent"), nullptr);
}

TEST(BinaryTreeTableTest, MultipleInsertFind) {
    BinaryTreeTable table;
    Polynomial p1, p2;
    p1.insert(1.0, 1);
    p2.insert(2.0, 2);

    table.insert("key1", p1);
    table.insert("key2", p2);

    EXPECT_NE(table.find("key1"), nullptr);
    EXPECT_NE(table.find("key2"), nullptr);
}

TEST(BinaryTreeTableTest, OverwriteValue) {
    BinaryTreeTable table;
    Polynomial p1, p2;
    p1.insert(1.0, 1);  
    p2.insert(2.0, 2); 

    table.insert("key", p1);
    table.insert("key", p2);

    auto found = table.find("key");
    ASSERT_NE(found, nullptr);

    ASSERT_NE(found->getHead_(), nullptr);
    EXPECT_DOUBLE_EQ(found->getHead_()->monom.coefficient, 2.0);
}

TEST(BinaryTreeTableTest, RemoveExisting) {
    BinaryTreeTable table;
    Polynomial p;
    p.insert(1.0, 1);

    table.insert("key", p);
    table.remove("key");

    EXPECT_EQ(table.find("key"), nullptr);
}

TEST(BinaryTreeTableTest, RemoveNonExistent) {
    BinaryTreeTable table;
    EXPECT_NO_THROW(table.remove("nonexistent"));
}

TEST(BinaryTreeTableTest, ClearTree) {
    BinaryTreeTable table;
    Polynomial p;
    p.insert(1.0, 1);

    table.insert("key1", p);
    table.insert("key2", p);
}

TEST(BinaryTreeTableTest, ReverseOrderInsert) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("key3", p);
    table.insert("key2", p);
    table.insert("key1", p);

    EXPECT_NE(table.find("key1"), nullptr);
    EXPECT_NE(table.find("key2"), nullptr);
    EXPECT_NE(table.find("key3"), nullptr);
}

TEST(BinaryTreeTableTest, RemoveRoot) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("root", p);
    table.insert("left", p);
    table.insert("right", p);

    table.remove("root");

    EXPECT_EQ(table.find("root"), nullptr);
    EXPECT_NE(table.find("left"), nullptr);
    EXPECT_NE(table.find("right"), nullptr);
}

TEST(BinaryTreeTableTest, RemoveNodeWithTwoChildren) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("50", p);
    table.insert("30", p);
    table.insert("70", p);
    table.insert("20", p);
    table.insert("40", p);
    table.insert("60", p);
    table.insert("80", p);

    table.remove("50");

    EXPECT_EQ(table.find("50"), nullptr);
    EXPECT_NE(table.find("60"), nullptr);
}

TEST(BinaryTreeTableTest, RemoveAllElements) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("1", p);
    table.insert("2", p);
    table.insert("3", p);

    table.remove("2");
    table.remove("1");
    table.remove("3");

    EXPECT_EQ(table.find("1"), nullptr);
    EXPECT_EQ(table.find("2"), nullptr);
    EXPECT_EQ(table.find("3"), nullptr);
}

TEST(BinaryTreeTableTest, DuplicateInsert) {
    BinaryTreeTable table;
    Polynomial p1, p2;
    p1.insert(1.0, 1);
    p2.insert(2.0, 2);

    table.insert("key", p1);
    table.insert("key", p2);

    auto found = table.find("key");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getHead_()->monom.coefficient, 2.0);
}

TEST(BinaryTreeTableTest, EmptyKey) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("", p);
    EXPECT_NE(table.find(""), nullptr);
}

TEST(BinaryTreeTableTest, LongKeys) {
    BinaryTreeTable table;
    Polynomial p;
    std::string longKey(1000, 'a');

    table.insert(longKey, p);
    EXPECT_NE(table.find(longKey), nullptr);
}

TEST(BinaryTreeTableTest, SpecialCharsInKeys) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("!@#$%^&*()", p);
    EXPECT_NE(table.find("!@#$%^&*()"), nullptr);
}

TEST(BinaryTreeTableTest, LargeInsert) {
    BinaryTreeTable table;
    Polynomial p;

    for (int i = 0; i < 1000; ++i) {
        table.insert("key" + std::to_string(i), p);
    }

    for (int i = 0; i < 1000; ++i) {
        EXPECT_NE(table.find("key" + std::to_string(i)), nullptr);
    }
}

TEST(BinaryTreeTableTest, SequentialAccess) {
    BinaryTreeTable table;
    Polynomial p;
    const int COUNT = 100;

    for (int i = 0; i < COUNT; ++i) {
        table.insert(std::to_string(i), p);
    }

    for (int i = 0; i < COUNT; ++i) {
        EXPECT_NE(table.find(std::to_string(i)), nullptr);
    }
}

TEST(BinaryTreeTableTest, RandomAccess) {
    BinaryTreeTable table;
    Polynomial p;
    std::vector<std::string> keys;

    for (int i = 0; i < 100; ++i) {
        std::string key = "key" + std::to_string(rand() % 1000);
        keys.push_back(key);
        table.insert(key, p);
    }

    for (const auto& key : keys) {
        EXPECT_NE(table.find(key), nullptr);
    }
}

TEST(BinaryTreeTableTest, InsertAfterRemove) {
    BinaryTreeTable table;
    Polynomial p1, p2;
    p1.insert(1.0, 1);
    p2.insert(2.0, 2);

    table.insert("key", p1);
    table.remove("key");
    table.insert("key", p2);

    auto found = table.find("key");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getHead_()->monom.coefficient, 2.0);
}

TEST(BinaryTreeTableTest, MixedWorkload) {
    BinaryTreeTable table;
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

TEST(BinaryTreeTableTest, CaseSensitiveKeys) {
    BinaryTreeTable table;
    Polynomial p1, p2;
    p1.insert(1.0, 1);
    p2.insert(2.0, 2);

    table.insert("KEY", p1);
    table.insert("key", p2);

    EXPECT_NE(table.find("KEY"), nullptr);
    EXPECT_NE(table.find("key"), nullptr);
}

TEST(BinaryTreeTableTest, StressTest) {
    BinaryTreeTable table;
    Polynomial p;

    for (int i = 0; i < 10000; ++i) {
        table.insert("stress" + std::to_string(i), p);
    }

    for (int i = 0; i < 10000; ++i) {
        EXPECT_NE(table.find("stress" + std::to_string(i)), nullptr);
    }
}

TEST(BinaryTreeTableTest, ClearAndReuse) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("first", p);

    table.insert("second", p);
    EXPECT_NE(table.find("second"), nullptr);
}

TEST(BinaryTreeTableTest, RebalancingPreservesData) {
    BinaryTreeTable table;
    Polynomial p;

    for (int i = 0; i < 100; ++i) {
        table.insert(std::to_string(i), p);
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_NE(table.find(std::to_string(i)), nullptr);
    }
}

TEST(BinaryTreeTableTest, ClearEmptyTable) {
    BinaryTreeTable table;
}

TEST(BinaryTreeTableTest, ClearNonEmptyTable) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("key1", p);
    table.insert("key2", p);
}

TEST(BinaryTreeTableTest, InsertAfterClear) {
    BinaryTreeTable table;
    Polynomial p1, p2;
    p1.insert(1.0, 1);
    p2.insert(2.0, 2);

    table.insert("key1", p1);

    table.insert("key2", p2);
    EXPECT_NE(table.find("key2"), nullptr);
}

TEST(BinaryTreeTableTest, NullPolynomial) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("null", p);
    auto found = table.find("null");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getHead_(), nullptr);
}

TEST(BinaryTreeTableTest, InsertRemoveSequence) {
    BinaryTreeTable table;
    Polynomial p;

    table.insert("50", p);
    table.insert("30", p);
    table.insert("20", p);
    table.insert("40", p);
    table.insert("70", p);
    table.insert("60", p);
    table.insert("80", p);

    table.remove("20");
    table.remove("30");
    table.insert("35", p);
    table.remove("50");
    table.insert("45", p);

    EXPECT_EQ(table.find("20"), nullptr);
    EXPECT_EQ(table.find("30"), nullptr);
    EXPECT_EQ(table.find("50"), nullptr);
    EXPECT_NE(table.find("35"), nullptr);
    EXPECT_NE(table.find("45"), nullptr);
    EXPECT_NE(table.find("70"), nullptr);
}