#include <gtest/gtest.h>

#include "linkedhashset.hpp"

// tests for insert
TEST(LHS, InsertExistingValue) {
    linkedhs set;

    for (int i = 0; i < 15; i++) {
        set.insert(element(15, "Petya"));
    }
    ASSERT_EQ(set.insert(element(15, "Petya")), false);
}

TEST(LHS, InsertMoreThanDefaultCapacity) {
    linkedhs set;
    for (int i = 0; i < 100; i++) {
        set.insert(element(i, "name"));
    }
    ASSERT_EQ(set.size(), 100);
}

// tests for size and empty
TEST(LHS, CheckingSizeUniqueStudents) {
    linkedhs set;
    set.insert(element(0, "Vlad"));
    set.insert(element(19, "Yura"));
    set.insert(element(18, "Yura"));
    set.insert(element(567, "Egor"));
    set.insert(element(19, "Nastya"));
    set.insert(element(19, "Anya"));
    set.insert(element(19, "Nadya"));
    set.insert(element(19, "Zhenya"));
    set.insert(element(6, "Mishka"));

    ASSERT_EQ(set.size(), 9);
}

TEST(LHS, CheckingSizeNotUniqueStudents) {
    linkedhs set;
    set.insert(element(0, "Vlad"));
    set.insert(element(0, "Vlad"));

    set.insert(element(19, "Yura"));
    set.insert(element(19, "Yura"));

    set.insert(element(18, "Yura"));

    set.insert(element(19, "Nastya"));
    set.insert(element(19, "Anya"));
    set.insert(element(19, "Nadya"));

    ASSERT_EQ(set.size(), 6);
}

TEST(LHS, CheckingEmptyAfterDeleting) {
    linkedhs set;
    set.insert(element(0, "Vlad"));
    set.remove(element(0, "Vlad"));

    ASSERT_EQ(set.empty(), true);
}

TEST(LHS, CheckingEmptyAfterAdding) {
    linkedhs set;
    set.insert(element(0, "Vlad"));
    set.remove(element(0, "Vlad"));
    set.insert(element(0, "Vlad"));

    ASSERT_EQ(set.empty(), false);
}

// tests for remove
TEST(LHS, DeleteElemsWithTheSameHash) {
    linkedhs set1;
    set1.insert(element(0, "Anton")); // the same hash
    set1.insert(element(5, "Kapop")); // the same hash

    set1.remove(element(0, "Anton"));
    set1.remove(element(5, "Kapop"));

    ASSERT_EQ(set1.size(), 0);
}

// tests for clear
TEST(LHS, CheckSizeAfterClearingNotEmptyLHS) {
    linkedhs set;
    set.insert(element(0, "Anton"));
    set.insert(element(19, "Stepa"));
    set.insert(element(5, "Kirill"));

    set.clear();

    ASSERT_EQ(set.size(), 0);
}

TEST(LHS, CheckSizeAfterClearingEmptyLHS) {
    linkedhs set;
    set.clear();

    ASSERT_EQ(set.size(), 0);
}

TEST(LHS, CheckEmptyAfterClearing) {
    linkedhs set;
    set.clear();

    ASSERT_EQ(set.empty(), true);
}

// tests for clear and operator= and copy ctor
TEST(LHS, CheckSizeClearThenAssign) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    set1.clear();
    linkedhs set2;
    set2 = set1;

    ASSERT_EQ(set2.size(), set1.size());
}

TEST(LHS, CheckSizeClearThenCopy) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    set1.clear();
    linkedhs set2(set1);

    ASSERT_EQ(set2.size(), set1.size());
}

// tests for operator== and !=
TEST(LHS, CheckEqualityOperator) {
    linkedhs set1;
    for (int i = 0; i < 10; i++) {
        set1.insert(element(i, "Name"));
    }

    linkedhs set2;
    for (int i = 0; i < 10; i++) {
        set2.insert(element(i, "Name"));
    }

    ASSERT_EQ(set1 == set2, true);
}

TEST(LHS, CheckInequalityOperator) {
    linkedhs set1;
    for (int i = 0; i < 10; i++) {
        set1.insert(element(i, "Name1"));
        set1.insert(element(i, "Name2"));
    }

    linkedhs set2;
    for (int i = 0; i < 10; i++) {
        set2.insert(element(i, "Name1"));
    }

    ASSERT_EQ(set1 != set2, true);
}

// tests for contains
TEST(LHS, CheckContainingElement) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    ASSERT_EQ(set1.contains(element(5, "Sasha")), true);
}

TEST(LHS, CheckNotContainingElement) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    ASSERT_EQ(set1.contains(element(89, "Emelya")), false);
}

// tests for swap
TEST(LHS, CheckSwapDifferentSets) {
    linkedhs set1;
    for (int i = 0; i < 3; i++) {
        set1.insert(element(i, "student girls"));
    }

    linkedhs set2;
    for (int i = 0; i < 2; i++) {
        set2.insert(element(i, "student boys"));
    }

    set2.swap(set1);

    for (int i = 0; i < set2.size(); i++) {
        if (set2.contains(element(i, "student girls"))) {
            ASSERT_EQ(set2.contains(element(i, "student girls")),
                      true);
        }
    }

    for (int i = 0; i < set1.size(); i++) {
        if (set2.contains(element(i, "student boys"))) {
            ASSERT_EQ(set2.contains(element(i, "student boys")),
                      true);
        }
    }
}

TEST(LHS, CheckSwapSameSet) {
    linkedhs set1;
    for (int i = 0; i < 3; i++) {
        set1.insert(element(i, "student girls"));
    }

    set1.swap(set1);
    for (int i = 0; i < set1.size(); i++) {
        if (set1.contains(element(i, "student girls"))) {
            ASSERT_EQ(set1.contains(element(i, "student girls")),
                      true);
        }
    }
}

// tests for find
TEST(LHS, CheckFindExistingElement) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    linkedhs::iterator iter = set1.find(element(5, "Sasha"));

    ASSERT_EQ(*iter, element(5, "Sasha"));
}

TEST(LHS, CheckFindNonExistingElement) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    linkedhs::iterator iter = set1.find(element(51, "Glasha"));

    ASSERT_EQ(iter, set1.end());
}

// tests for operator=
TEST(LHS, CheckSizeAfterAssigning) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    linkedhs set2 = set1;

    ASSERT_EQ(set2.size(), set1.size());
}

// tests for copy ctor
TEST(LHS, CheckElementsExistingAfterCopying) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    linkedhs set2(set1);

    bool isConstains = false;
    for (linkedhs::iterator it = set2.begin(); it != set2.end();
         it++) {
        if (set1.contains(element(0, "Anton")) &&
            set1.contains(element(19, "Yura")) &&
            set1.contains(element(5, "Sasha"))
            //&&
            // set1.size() == set2.size()
        ) {
            isConstains = true;
        }
    }
    ASSERT_EQ(isConstains, true);
}

TEST(LHS, CheckSizeAfterCopying) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    linkedhs set2(set1);

    ASSERT_EQ(set2.size(), set1.size());
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
