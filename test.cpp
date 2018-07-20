#include "gtest/gtest.h"
#include "MyList.h"

using namespace MyList;

TEST(copy_constructor_testing, test1) {
    LinkedList l1;
    l1.push_back(9);
    l1.push_back(5);
    LinkedList l2(l1);
    LinkedList::iterator i = l2.begin();
    ASSERT_EQ(9, *i);
    ASSERT_EQ(5, *(++i));
}

TEST(move_constructor_testing, test2) {
    LinkedList l1;
    l1.push_back(2);
    l1.push_back(0);
    LinkedList l2(std::move(l1));
    LinkedList::iterator i = l2.begin();
    ASSERT_EQ(2, *i);
    ASSERT_EQ(0, *(++i));
}

TEST(copy_assignment_operator_testing, test3) {
    LinkedList l1;
    l1.push_back(9);
    l1.push_back(2);
    l1.push_back(5);
    LinkedList l2;
    l2.push_back(1);
    l2.push_back(8);
    l1 = l2;
    LinkedList::iterator i = l1.begin();
    ASSERT_EQ(1, *i);
    ASSERT_EQ(8, *(++i));
}

TEST(move_assignment_operator_testing, test4) {
    LinkedList l1;
    l1.push_back(4);
    l1.push_back(7);
    l1.push_back(3);
    LinkedList l2;
    l2.push_back(2);
    l2.push_back(6);
    l1 = std::move(l2);
    LinkedList::iterator i = l1.begin();
    ASSERT_EQ(2, *i);
    ASSERT_EQ(6, *(++i));
}

TEST(size_testing, test5) {
    LinkedList l;
    ASSERT_TRUE(l.empty());
    l.push_back(7);
    l.push_front(5);
    l.push_back(1);
    l.push_front(2);
    LinkedList::iterator i = l.begin();
    ++i;
    l.insert(i++, 3);
    ASSERT_EQ(5, l.size());
    ASSERT_FALSE(l.empty());
    l.pop_front();
    l.push_back(9);
    l.pop_back();
    ASSERT_EQ(4, l.size());
    l.erase(--i);
    ASSERT_EQ(3, l.size());
}

TEST (insert_testing, test6) {
    LinkedList l;
    LinkedList::iterator i = l.begin();
    l.push_back(8);
    l.push_front(1);
    l.insert(++i, 2);

    LinkedList::iterator j = l.begin();
    ASSERT_EQ(2, l.front());
    ASSERT_EQ(2, *j);
    ASSERT_EQ(1, *(++j));
    ASSERT_EQ(8, *(++j));
    ASSERT_EQ(8, l.back());

    l.push_back(3);
    l.push_back(5);
    l.push_front(0);
    l.pop_back();
    j = l.begin();
    ASSERT_EQ(0, l.front());
    ASSERT_EQ(0, *j);
    ASSERT_EQ(2, *(++j));
    ASSERT_EQ(1, *(++j));
    ASSERT_EQ(8, *(++j));
    ASSERT_EQ(3, *(++j));
    ASSERT_EQ(3, l.back());

    l.erase(i, --l.end());
    l.insert(--i, 4);
    l.pop_front();
    j = l.begin();
    ASSERT_EQ(4, l.front());
    ASSERT_EQ(4, *j);
    ASSERT_EQ(2, *(++j));
    ASSERT_EQ(3, *(++j));
    ASSERT_EQ(3, l.back());
}

TEST(remove_testing, test7) {
    LinkedList l;
    l.push_back(4);
    l.push_front(3);
    l.push_back(7);
    l.push_front(3);
    l.push_back(0);
    l.remove(3);
    LinkedList::iterator j = l.begin();
    ASSERT_EQ(4, *j);
    ASSERT_EQ(7, *(++j));
    ASSERT_EQ(0, *(++j));
    l.clear();
    ASSERT_TRUE(l.empty());
}

 TEST(concat_testing, test8) {
    LinkedList l1;
    LinkedList l2;
    l2.push_back(2);
    l2.push_front(0);
    l2.push_back(4);
    l1+=l2;
    LinkedList::iterator j = l1.begin();
    ASSERT_EQ(0, *j);
    ASSERT_EQ(2, *(++j));
    ASSERT_EQ(4, *(++j));
}

TEST(concat_testing, test9) {
    LinkedList l1;
    l1.push_back(3);
    l1.push_back(8);
    LinkedList l2;
    l2.push_back(2);
    l1 += l2;
    LinkedList::iterator j = l1.begin();
    ASSERT_EQ(3, *j);
    ASSERT_EQ(8, *(++j));
    ASSERT_EQ(2, *(++j));
}

TEST(compare_testing, test10) {
    LinkedList l1;
    l1.push_back(2);
    LinkedList l2;
    l2.push_back(2);
    l2.push_front(0);
    l2.push_back(4);
    ASSERT_FALSE(l1==l2);
    ASSERT_TRUE(l1!=l2);
}

TEST(compare_testing, test11) {
    LinkedList l1;
    l1.push_back(2);
    l1.push_front(0);
    l1.push_back(4);
    LinkedList l2;
    l2.push_back(2);
    l2.push_front(0);
    l2.push_back(4);
    ASSERT_TRUE(l1==l2);
    ASSERT_FALSE(l1!=l2);
}

TEST(merge_testing, test12) {
    LinkedList l1;
    l1.push_back(6);
    l1.push_front(9);
    LinkedList l2;
    l2.push_back(2);
    l2.push_front(0);
    l2.push_back(4);
    LinkedList l;
    l = l1+l2;
    LinkedList::iterator i = l.begin();
    ASSERT_EQ(9, *i);
    ASSERT_EQ(6, *(++i));
    ASSERT_EQ(0, *(++i));
    ASSERT_EQ(2, *(++i));
    ASSERT_EQ(4, *(++i));
    l = l2+l1;
    i = l.begin();
    ASSERT_EQ(0, *i);
    ASSERT_EQ(2, *(++i));
    ASSERT_EQ(4, *(++i));
    ASSERT_EQ(9, *(++i));
    ASSERT_EQ(6, *(++i));
}