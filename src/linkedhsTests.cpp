#include <gtest/gtest.h>

#include "linkedhashset.hpp"

#include <string.h>
#include <string>

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

    for (int i = 0; i < set.size(); i++) {
        ASSERT_EQ(set.contains(element(i, "name")), true);
    }
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

TEST(LHS, DeleteElemFromTheStart) {
    linkedhs set1;

    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    ASSERT_EQ(set1.size(), 100);

    set1.remove(element(0, "student0"));

    for (int i = 0; i < set1.size(); i++) {
        if (!set1.contains(
                element(i, "student" + (std::to_string(i))))) {
            ASSERT_EQ(set1.contains(element(0, "student0")), false);
            // ASSERT_EQ(set1.contains(element(i, "student" +
            // (std::to_string(i)))), true);
        }
    }
}

TEST(LHS, DeleteElemFromTheMiddle) {
    linkedhs set1;

    for (int i = 0; i < 1000; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    ASSERT_EQ(set1.size(), 1000);

    set1.remove(element(1000, "student100"));

    for (int i = 0; i < set1.size(); i++) {
        if (!set1.contains(
                element(i, "student" + (std::to_string(i))))) {
            ASSERT_EQ(set1.contains(element(1000, "student100")),
                      false);
        }
    }
}

TEST(LHS, DeleteElemFromTheEnd) {
    linkedhs set1;

    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    ASSERT_EQ(set1.size(), 100);

    set1.remove(element(50, "student50"));

    for (int i = 0; i < set1.size(); i++) {
        if (!set1.contains(
                element(i, "student" + (std::to_string(i))))) {
            ASSERT_EQ(set1.contains(element(50, "student50")), false);
        }
    }
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
            set1.contains(element(5, "Sasha")) &&
            set1.size() == set2.size()) {
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

// tests for correct order
TEST(LHS, CheckOrderInsert) {
    linkedhs set;
    set.insert(element(0, "Anton"));
    set.insert(element(19, "Yura"));
    set.insert(element(5, "Sasha"));

    linkedhs::iterator iter = set.begin();
    ASSERT_EQ((*iter).age_, 0);
    ASSERT_EQ((*iter).name_, "Anton");

    iter++;
    ASSERT_EQ((*iter).age_, 19);
    ASSERT_EQ((*iter).name_, "Yura");

    iter++;
    ASSERT_EQ((*iter).age_, 5);
    ASSERT_EQ((*iter).name_, "Sasha");
}

TEST(LHS, CheckOrderAfterDeletingFromStart) {
    linkedhs set;
    set.insert(element(78, "Pavel"));
    set.insert(element(19, "Yura"));
    set.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set.begin();
    ASSERT_EQ((*iter1).age_, 78);
    ASSERT_EQ((*iter1).name_, "Pavel");

    iter1++;
    ASSERT_EQ((*iter1).age_, 19);
    ASSERT_EQ((*iter1).name_, "Yura");

    iter1++;
    ASSERT_EQ((*iter1).age_, 6);
    ASSERT_EQ((*iter1).name_, "Mishka");

    set.remove(element(78, "Pavel"));

    linkedhs::iterator iter2 = set.begin();
    ASSERT_EQ((*iter2).age_, 19);
    ASSERT_EQ((*iter2).name_, "Yura");

    iter2++;
    ASSERT_EQ((*iter2).age_, 6);
    ASSERT_EQ((*iter2).name_, "Mishka");
}

TEST(LHS, CheckOrderAfterDeletingFromMiddle) {
    linkedhs set;
    set.insert(element(78, "Pavel"));
    set.insert(element(19, "Yura"));
    set.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set.begin();
    ASSERT_EQ((*iter1).age_, 78);
    ASSERT_EQ((*iter1).name_, "Pavel");

    iter1++;
    ASSERT_EQ((*iter1).age_, 19);
    ASSERT_EQ((*iter1).name_, "Yura");

    iter1++;
    ASSERT_EQ((*iter1).age_, 6);
    ASSERT_EQ((*iter1).name_, "Mishka");

    set.remove(element(19, "Yura"));

    linkedhs::iterator iter2 = set.begin();
    ASSERT_EQ((*iter2).age_, 78);
    ASSERT_EQ((*iter2).name_, "Pavel");

    iter2++;
    ASSERT_EQ((*iter2).age_, 6);
    ASSERT_EQ((*iter2).name_, "Mishka");
}

TEST(LHS, CheckOrderAfterDeletingFromEnd) {
    linkedhs set;
    set.insert(element(78, "Pavel"));
    set.insert(element(19, "Yura"));
    set.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set.begin();
    ASSERT_EQ((*iter1).age_, 78);
    ASSERT_EQ((*iter1).name_, "Pavel");

    iter1++;
    ASSERT_EQ((*iter1).age_, 19);
    ASSERT_EQ((*iter1).name_, "Yura");

    iter1++;
    ASSERT_EQ((*iter1).age_, 6);
    ASSERT_EQ((*iter1).name_, "Mishka");

    set.remove(element(6, "Mishka"));

    linkedhs::iterator iter2 = set.begin();
    ASSERT_EQ((*iter2).age_, 78);
    ASSERT_EQ((*iter2).name_, "Pavel");

    iter2++;
    ASSERT_EQ((*iter2).age_, 19);
    ASSERT_EQ((*iter2).name_, "Yura");
}

TEST(LHS, CheckOrderAfterDelElemsWithSameHash) {
    linkedhs set1;
    set1.insert(element(0, "Anton")); // the same hash
    set1.insert(element(5, "Kapop")); // the same hash

    linkedhs::iterator iter1 = set1.begin();
    ASSERT_EQ((*iter1).age_, 0);
    ASSERT_EQ((*iter1).name_, "Anton");

    iter1++;
    ASSERT_EQ((*iter1).age_, 5);
    ASSERT_EQ((*iter1).name_, "Kapop");

    set1.remove(element(0, "Anton"));

    linkedhs::iterator iter2 = set1.begin();
    ASSERT_EQ((*iter2).age_, 5);
    ASSERT_EQ((*iter2).name_, "Kapop");

    set1.remove(element(5, "Kapop"));
    linkedhs::iterator iter3 = set1.begin();
    ASSERT_EQ(iter3 == set1.end(), true);
}

// tests for iterator
TEST(ITERATOR, CheckPostfixIncrement) {
    linkedhs set;
    set.insert(element(19, "Yura"));
    set.insert(element(19, "Nadya"));
    set.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set.find(element(19, "Nadya"));
    iter1++;
    ASSERT_EQ(*iter1, element(6, "Mishka"));
}

TEST(ITERATOR, CheckPostfixDecrement) {
    linkedhs set;
    set.insert(element(19, "Yura"));
    set.insert(element(19, "Nadya"));
    set.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set.find(element(19, "Nadya"));
    iter1--;
    ASSERT_EQ(*iter1, element(19, "Yura"));
}

TEST(ITERATOR, CheckPrefixIncrement) {
    linkedhs set;
    set.insert(element(19, "Yura"));
    set.insert(element(19, "Nadya"));
    set.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set.find(element(19, "Nadya"));
    ++iter1;
    ASSERT_EQ(*iter1, element(6, "Mishka"));
}

TEST(ITERATOR, CheckPrefixDecrement) {
    linkedhs set;
    set.insert(element(19, "Yura"));
    set.insert(element(19, "Nadya"));
    set.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set.find(element(19, "Nadya"));
    --iter1;
    ASSERT_EQ(*iter1, element(19, "Yura"));
}

TEST(ITERATOR, CheckComparisonOperator) {
    linkedhs set1;
    set1.insert(element(19, "Yura"));
    set1.insert(element(19, "Nadya"));
    set1.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set1.begin();

    linkedhs set2;
    set2.insert(element(19, "Yura"));
    set2.insert(element(19, "Nadya"));
    set2.insert(element(6, "Mishka"));
    linkedhs::iterator iter2 = set2.begin();

    for (iter1, iter2; iter1 != set1.end() && iter2 != set2.end();
         iter1++, iter2++) {
        ASSERT_EQ((*iter1) == (*iter2), true);
    }
}

TEST(ITERATOR, CheckNotComparisonOperator) {
    linkedhs set1;
    set1.insert(element(19, "Yura"));
    set1.insert(element(19, "Nadya"));
    set1.insert(element(6, "Mishka"));

    linkedhs::iterator iter1 = set1.begin();

    linkedhs set2;
    set2.insert(element(77, "Anatoliy"));
    set2.insert(element(45, "Ashot"));
    set2.insert(element(61, "Sergey"));
    linkedhs::iterator iter2 = set2.begin();

    for (iter1, iter2; iter1 != set1.end() && iter2 != set2.end();
         iter1++, iter2++) {
        ASSERT_EQ((*iter1) != (*iter2), true);
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
