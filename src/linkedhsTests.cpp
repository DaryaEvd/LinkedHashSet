#include <gtest/gtest.h>
#include <string.h>

#include "linkedhashset.hpp"

TEST(LHS, RemoveTwoWithSameHash) {
    linkedhs set;
    set.insert(element(0, "Anton")); // the same hash
    set.insert(element(5, "Kapop")); // the same hash

    ASSERT_TRUE(set.remove(element(0, "Anton")));
    ASSERT_TRUE(set.remove(element(5, "Kapop")));
}

TEST(LHS, RemoveSameHashAndInsert) {
    linkedhs set;
    set.insert(element(0, "Anton")); // the same hash
    set.insert(element(5, "Kapop")); // the same hash

    set.remove(element(0, "Anton"));

    ASSERT_TRUE(set.insert(element(5, "Yura"))); // the same hash
    ASSERT_TRUE(set.insert(element(15, "Kirill"))); // the same hash)
}

TEST(LHS, RemoveLotsElems) {
    linkedhs set;
    for (int i = 0; i < 100; i++) {
        set.insert(element(i, "name" + (std::to_string(i))));
    }

    for (int i = 0; i < 99; i++) {
        set.remove(element(i, "name" + (std::to_string(i))));
    }

    ASSERT_EQ(set.size(), 1);

    linkedhs::iterator iter = set.begin();
    ASSERT_EQ((*iter).age_, 99);
    ASSERT_EQ((*iter).name_, "name99");

    iter++;
    ASSERT_EQ(iter, set.end());
}

TEST(LHS, RemoveFromEmpty) {
    linkedhs set;
    ASSERT_EQ(set.size(), 0);

    ASSERT_FALSE(set.remove(element(0, "name0")));
}

TEST(LHS, InsertInEmpty) {
    linkedhs set;
    ASSERT_TRUE(set.empty());

    set.insert(element(0, "Petya"));

    ASSERT_EQ(set.size(), 1);
}

TEST(LHS, InsertNewElem) {
    linkedhs set;

    set.insert(element(0, "student0"));
    ASSERT_TRUE(set.insert(element(1, "student1")));
}

TEST(LHS, InsertSameElem) {
    linkedhs set;

    set.insert(element(0, "Petya"));
    ASSERT_FALSE(set.insert(element(0, "Petya")));
}
TEST(LHS, InsertAndResize) {
    linkedhs set;
    for (int i = 0; i < 100; i++) {
        set.insert(element(i, "name" + (std::to_string(i))));
    }

    ASSERT_EQ(set.size(), 100);

    for (int i = 0; i < set.size(); i++) {
        ASSERT_TRUE(
            set.contains(element(i, "name" + (std::to_string(i)))));
    }
}

TEST(LHS, InsertResizeRemoveAllButOne) {
    linkedhs set;
    for (int i = 0; i < 100; i++) {
        set.insert(element(i, "name" + (std::to_string(i))));
    }

    ASSERT_EQ(set.size(), 100);

    for (int i = 0; i < 99; i++) {
        ASSERT_TRUE(
            set.remove(element(i, "name" + (std::to_string(i)))));
    }

    ASSERT_EQ(set.size(), 1);

    ASSERT_TRUE(set.contains(element(99, "name99")));
}

TEST(LHS, DeleteStartElem) {
    linkedhs set1;

    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    ASSERT_EQ(set1.size(), 100);

    set1.remove(element(0, "student0"));

    for (int i = 0; i < set1.size(); i++) {
        if (!set1.contains(
                element(i, "student" + (std::to_string(i))))) {
            ASSERT_FALSE(set1.contains(element(0, "student0")));
        }
    }
}

TEST(LHS, DeleteMiddleElem) {
    linkedhs set1;

    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    ASSERT_EQ(set1.size(), 100);

    set1.remove(element(50, "student50"));

    for (int i = 0; i < set1.size(); i++) {
        if (!set1.contains(
                element(i, "student" + (std::to_string(i))))) {
            ASSERT_FALSE(set1.contains(element(50, "student50")));
        }
    }
}

TEST(LHS, DeleteLastElem) {
    linkedhs set1;

    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    ASSERT_EQ(set1.size(), 100);

    set1.remove(element(100, "student100"));

    for (int i = 0; i < set1.size(); i++) {
        if (!set1.contains(
                element(i, "student" + (std::to_string(i))))) {
            ASSERT_FALSE(set1.contains(element(1000, "student100")));
        }
    }
}

// tests for clear
TEST(LHS, CheckClearThenInsert) {
    linkedhs set;
    for (int i = 0; i < 100; i++) {
        set.insert(element(i, "student" + (std::to_string(i))));
    }

    set.clear();
    ASSERT_EQ(set.size(), 0);
    ASSERT_TRUE(set.empty());

    set.insert(element(90, "student"));
    ASSERT_EQ(set.size(), 1);
    ASSERT_FALSE(set.empty());
}

TEST(LHS, CheckAfterClearingEmptyLHS) {
    linkedhs set;

    set.clear();
    ASSERT_EQ(set.size(), 0);
    ASSERT_TRUE(set.empty());
}

// tests for operator=
TEST(LHS, CheckAssignOperator) {
    linkedhs set1;
    for (int i = 0; i < 50; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    linkedhs set2;
    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "name" + (std::to_string(i))));
    }

    set1 = set2;

    ASSERT_EQ(set2.size(), set1.size());

    for (int i = 0; i < set1.size(); i++) {
        ASSERT_FALSE(
            !set1.contains(element(i, "name" + (std::to_string(i)))));
    }

    for (int i = 0; i < set2.size(); i++) {
        ASSERT_FALSE(
            !set2.contains(element(i, "name" + (std::to_string(i)))));
    }
}

TEST(LHS, CheckAssignOpClearThenAssign) {
    linkedhs set1;
    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    set1.clear();
    linkedhs set2;
    set2 = set1;

    ASSERT_EQ(set1.size(), 0);
    ASSERT_EQ(set2.size(), set1.size());

    for (int i = 0; i < 100; i++) {
        ASSERT_FALSE(set2.contains(
            element(i, "student" + (std::to_string(i)))));
    }
}

// tests for copy ctor
TEST(LHS, CheckCopyCtor) {
    linkedhs set1;
    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }
    linkedhs set2(set1);

    ASSERT_EQ(set2.size(), set1.size());
    for (int i = 0; i < set2.size(); i++) {
        ASSERT_TRUE(set2.contains(
            element(i, "student" + (std::to_string(i)))));
    }
}

TEST(LHS, CheckCopyCtorClearThenCopy) {
    linkedhs set1;
    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    set1.clear();
    linkedhs set2(set1);

    ASSERT_EQ(set2.size(), 0);
    ASSERT_EQ(set2.size(), set1.size());

    for (int i = 0; i < 1000; i++) {
        ASSERT_FALSE(set2.contains(
            element(i, "student" + (std::to_string(i)))));
    }
}

// tests for operator== and !=
TEST(LHS, CheckEqualityOperator) {
    linkedhs set1;
    for (int i = 0; i < 100; i++) {
        set1.insert(element(i, "student" + (std::to_string(i))));
    }

    linkedhs set2;
    for (int i = 0; i < 100; i++) {
        set2.insert(element(i, "name" + (std::to_string(i))));
    }

    ASSERT_FALSE(set1 == set2);
    ASSERT_TRUE(set1 != set2);
}

// tests for contains
TEST(LHS, CheckContainsElement) {
    linkedhs set1;
    set1.insert(element(0, "Anton"));
    set1.insert(element(19, "Yura"));
    set1.insert(element(5, "Sasha"));

    ASSERT_TRUE(set1.contains(element(5, "Sasha")));
    ASSERT_FALSE(set1.contains(element(90, "Avdey")));
}

// tests for swap
TEST(LHS, CheckSwapDifferentSets) {
    linkedhs set1;
    for (int i = 0; i < 5; i++) {
        set1.insert(element(i, "student girls"));
    }

    linkedhs set2;
    for (int i = 0; i < 12; i++) {
        set2.insert(element(i, "student boys"));
    }

    set2.swap(set1);

    ASSERT_EQ(set1.size(), 12);
    ASSERT_EQ(set2.size(), 5);

    for (int i = 0; i < set2.size(); i++) {
        if (set2.contains(element(i, "student girls"))) {
            ASSERT_TRUE(set2.contains(element(i, "student girls")));
        }
    }

    for (int i = 0; i < set1.size(); i++) {
        if (set2.contains(element(i, "student boys"))) {
            ASSERT_TRUE(set2.contains(element(i, "student boys")));
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
            ASSERT_TRUE(set1.contains(element(i, "student girls")));
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
    ASSERT_TRUE(iter3 == set1.end());
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
        ASSERT_TRUE((*iter1) == (*iter2));
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
        ASSERT_TRUE((*iter1) != (*iter2));
    }
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
