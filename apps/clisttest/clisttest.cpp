
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include "CircularList.hpp"

class CircularListTest : public ::testing::Test {
protected:
    CircularList<int> list;
    std::string captureTraverseOutput(CircularList<int>& l) {
        std::stringstream ss;
        l.traverse([&ss](int& data) {
            ss << data << " ";
        });
        return ss.str();
    }
};

// Test default constructor and empty list
TEST_F(CircularListTest, DefaultConstructor) {
    EXPECT_TRUE(list.empty()) << "Default list should be empty";
    EXPECT_EQ(captureTraverseOutput(list), "") << "Empty list traversal should be empty";
}

// Test single-element constructor
TEST_F(CircularListTest, SingleElementConstructor) {
    CircularList<int> singleList(42);
    EXPECT_FALSE(singleList.empty()) << "Single-element list should not be empty";
    EXPECT_EQ(singleList.front(), 42) << "Front should return 42";
    EXPECT_EQ(singleList.back(), 42) << "Back should return 42";
    EXPECT_EQ(captureTraverseOutput(singleList), "42 ") << "Traverse should output 42";
}

// Test push_front
TEST_F(CircularListTest, PushFront) {
    list.push_front(10);
    list.push_front(20);
    EXPECT_FALSE(list.empty()) << "List should not be empty after push_front";
    EXPECT_EQ(list.front(), 20) << "Front should be 20";
    EXPECT_EQ(list.back(), 10) << "Back should be 10";
    EXPECT_EQ(captureTraverseOutput(list), "20 10 ") << "Traverse should output 20 10";
}

// Test push_back
TEST_F(CircularListTest, PushBack) {
    list.push_back(30);
    list.push_back(40);
    EXPECT_FALSE(list.empty()) << "List should not be empty after push_back";
    EXPECT_EQ(list.front(), 30) << "Front should be 30";
    EXPECT_EQ(list.back(), 40) << "Back should be 40";
    EXPECT_EQ(captureTraverseOutput(list), "30 40 ") << "Traverse should output 30 40";
}

// Test pop_front
TEST_F(CircularListTest, PopFront) {
    list.push_back(10);
    list.push_back(20);
    list.pop_front();
    EXPECT_FALSE(list.empty()) << "List should not be empty after one pop_front";
    EXPECT_EQ(list.front(), 20) << "Front should be 20 after pop_front";
    EXPECT_EQ(captureTraverseOutput(list), "20 ") << "Traverse should output 20";
    list.pop_front();
    EXPECT_TRUE(list.empty()) << "List should be empty after popping all elements";
}

// Test pop_back
TEST_F(CircularListTest, PopBack) {
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    EXPECT_FALSE(list.empty()) << "List should not be empty after one pop_back";
    EXPECT_EQ(list.back(), 10) << "Back should be 10 after pop_back";
    EXPECT_EQ(captureTraverseOutput(list), "10 ") << "Traverse should output 10";
    list.pop_back();
    EXPECT_TRUE(list.empty()) << "List should be empty after popping all elements";
};