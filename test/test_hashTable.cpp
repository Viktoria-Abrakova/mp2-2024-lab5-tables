#include <gtest.h>
#include "hashTable.h"
#include "polynomial.h"

TEST(HashTableTest, InsertAndFind) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100); 

    table.insert("poly1", p1);
    EXPECT_NE(table.find("poly1"), nullptr);
}

TEST(HashTableTest, FindNonExistent) {
    HashTable table;

    EXPECT_EQ(table.find("nonexistent"), nullptr);
}

TEST(HashTableTest, OverwriteValue) {
    HashTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("poly", p1);
    table.insert("poly", p2);
    EXPECT_EQ(table.find("poly")->getHead_()->monom.coefficient, 1.5);
}

TEST(HashTableTest, RemoveExisting) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("p1", p1);
    table.remove("p1");
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(HashTableTest, RemoveNonExistent) {
    HashTable table;

    EXPECT_NO_THROW(table.remove("nonexistent"));
}

TEST(HashTableTest, EmptyTable) {
    HashTable table;

    EXPECT_EQ(table.find("any"), nullptr);
}

TEST(HashTableTest, InsertEmptyKey) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("", p1);
    EXPECT_NE(table.find(""), nullptr);
}

TEST(HashTableTest, LongKeys) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    std::string longKey(1000, 'a');
    table.insert(longKey, p1);
    EXPECT_NE(table.find(longKey), nullptr);
}

TEST(HashTableTest, SpecialCharsInKeys) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("!@#$%^&*()", p1);
    EXPECT_NE(table.find("!@#$%^&*()"), nullptr);
}

TEST(HashTableTest, NullPolynomial) {
    HashTable table;
    Polynomial nullPoly;
    table.insert("null", nullPoly);
    EXPECT_EQ(table.find("null")->getHead_(), nullptr);
}

TEST(HashTableTest, HandleCollisions) {
    HashTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("abc", p1);
    table.insert("cba", p2);
    EXPECT_NE(table.find("abc"), nullptr);
    EXPECT_NE(table.find("cba"), nullptr);
}

TEST(HashTableTest, SameHashDifferentKeys) {
    HashTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("key1", p1);
    table.insert("key2", p2);
    EXPECT_NE(table.find("key1"), nullptr);
    EXPECT_NE(table.find("key2"), nullptr);
}

TEST(HashTableTest, RehashWhenNeeded) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; ++i) {
        table.insert("key" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("key500"), nullptr);
}

TEST(HashTableTest, LoadFactor) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 50; ++i) {
        table.insert("key" + std::to_string(i), p1);
    }
    EXPECT_LT(table.getLoadFactor(), 0.75); 
}

TEST(HashTableTest, BucketDistribution) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 100; ++i) {
        table.insert("key" + std::to_string(i), p1);
    }
    EXPECT_LE(table.getMaxBucketSize(), 5);
}

TEST(HashTableTest, MultipleInsert) {
    HashTable table;
    Polynomial p1;
    p1.insert(2.5, 100);

    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        table.insert(key, p1);

        EXPECT_NE(table.find(key), nullptr);
    }

    EXPECT_NE(table.find("poly50"), nullptr);

    for (int i = 0; i < 100; ++i) {
        std::string key = "poly" + std::to_string(i);
        EXPECT_NE(table.find(key), nullptr) << "Failed for key: " << key;
    }
}
TEST(HashTableTest, InsertRemoveSequence) {
    HashTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    table.insert("temp", p1);
    table.remove("temp");
    table.insert("temp", p2);
    EXPECT_EQ(table.find("temp")->getHead_()->monom.coefficient, 1.5);
}

TEST(HashTableTest, RepeatedInsert) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 10; ++i) {
        table.insert("repeat", p1);
    }
    EXPECT_EQ(table.find("repeat")->getHead_()->monom.coefficient, 2.5);
}

TEST(HashTableTest, MultipleRemove) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    table.insert("p1", p1);
    table.remove("p1");
    table.remove("p1"); 
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(HashTableTest, MixedOperations) {
    HashTable table;
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

TEST(HashTableTest, LargeInsert) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 10000; ++i) {
        table.insert("big" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("big5000"), nullptr);
}

TEST(HashTableTest, SequentialAccess) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 1000; ++i) {
        table.insert("seq" + std::to_string(i), p1);
    }
    for (int i = 0; i < 1000; ++i) {
        EXPECT_NE(table.find("seq" + std::to_string(i)), nullptr);
    }
}

TEST(HashTableTest, RandomAccess) {
    HashTable table;
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

TEST(HashTableTest, InsertAfterRemove) {
    HashTable table;
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

TEST(HashTableTest, MixedWorkload) {
    HashTable table;
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

TEST(HashTableTest, CaseSensitiveKeys) {
    HashTable table;
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

TEST(HashTableTest, StressTest) {
    HashTable table;
    Polynomial p1;

    p1.insert(2.5, 100);

    for (int i = 0; i < 100000; ++i) {
        table.insert("stress" + std::to_string(i), p1);
    }
    EXPECT_NE(table.find("stress50000"), nullptr);
}

TEST(HashTableTest, ClearAndReuse) {
    HashTable table;
    Polynomial p1, p2;

    p1.insert(2.5, 100);
    p2.insert(1.5, 10);

    for (int i = 0; i < 100; ++i) {
        table.insert("tmp" + std::to_string(i), p1);
    }
    table.clear();
    table.insert("reused", p2);
    EXPECT_NE(table.find("reused"), nullptr);
}

TEST(HashTableTest, RehashingPreservesData) {
    HashTable table;
    Polynomial p1;
    p1.insert(2.5, 100);

    std::vector<std::string> keys;
    for (int i = 0; i < 80; ++i) {
        keys.push_back("key" + std::to_string(i));
        table.insert(keys.back(), p1);
    }

    for (const auto& key : keys) {
        EXPECT_NE(table.find(key), nullptr)
            << "Key " << key << " should exist after rehashing";
    }
}

TEST(HashTableTest, LoadFactorAfterRehashing) {
    HashTable table;
    Polynomial p1;
    p1.insert(2.5, 100);

    for (int i = 0; i < 200; ++i) {
        table.insert("key" + std::to_string(i), p1);
        EXPECT_LT(table.getLoadFactor(), 0.76f)
            << "Load factor should never exceed 0.75 for long";
    }
}

TEST(HashTableTest, ClearEmptyTable) {
    HashTable table;
    EXPECT_NO_THROW(table.clear());
    EXPECT_EQ(table.getLoadFactor(), 0.0f);
}

TEST(HashTableTest, ClearNonEmptyTable) {
    HashTable table;
    Polynomial p;
    p.insert(1.0, 100);

    for (int i = 0; i < 10; ++i) {
        table.insert("key" + std::to_string(i), p);
    }

    table.clear();

    EXPECT_EQ(table.getLoadFactor(), 0.0f);
    EXPECT_EQ(table.getMaxBucketSize(), 0);

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(table.find("key" + std::to_string(i)), nullptr);
    }
}

TEST(HashTableTest, InsertAfterClear) {
    HashTable table;
    Polynomial p;
    p.insert(1.0, 100);

    table.insert("key1", p);
    table.clear();
    table.insert("key2", p);

    EXPECT_EQ(table.find("key1"), nullptr);
    EXPECT_NE(table.find("key2"), nullptr);
}

TEST(HashTableTest, ComplexPolynomials) {
    HashTable table;

    Polynomial complex;
    complex.insert(1.5, 300);
    complex.insert(2.5, 200);
    complex.insert(3.5, 100);
    table.insert("complex", complex);
    Polynomial* found = table.find("complex");
    EXPECT_EQ(found->getHead_()->monom.degree, 300);
    EXPECT_EQ(found->getHead_()->next->monom.degree, 200);
}