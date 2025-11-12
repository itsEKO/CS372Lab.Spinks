#include "gtest/gtest.h"
#include "AdjListGraph.hpp"
#include "AdjMatrixGraph.hpp"
#include "CycleDetection.hpp"
#include <vector>
#include <string>

using namespace std;

class CycleDetectionTest : public ::testing::Test {
protected:
    void SetUp() override {
        vector<int> nodes = {1, 2, 3, 4, 5};
        vector<pair<int, int>> edges = {
            {1, 2}, {2, 3}, {3, 4}, {4, 1},
            {4, 5}
        };
        
        adjListGraph = make_unique<AdjListGraph<int>>(nodes, edges);
        adjMatrixGraph = make_unique<AdjMatrixGraph<int>>(nodes, edges);
    }
    
    unique_ptr<AdjListGraph<int>> adjListGraph;
    unique_ptr<AdjMatrixGraph<int>> adjMatrixGraph;
};

TEST_F(CycleDetectionTest, ValidSimpleCycle_Square) {
    vector<int> validCycle = {1, 2, 3, 4, 1};
    
    EXPECT_TRUE(isSimpleCycle(*adjListGraph, validCycle));
    EXPECT_TRUE(isSimpleCycle(*adjMatrixGraph, validCycle));
    
    auto result = checkSimpleCycleDetailed(*adjListGraph, validCycle);
    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.errorMessage, "Valid simple cycle");
}

TEST_F(CycleDetectionTest, ValidSimpleCycle_ReverseDirection) {
    vector<int> validCycle = {1, 4, 3, 2, 1};
    
    EXPECT_TRUE(isSimpleCycle(*adjListGraph, validCycle));
    EXPECT_TRUE(isSimpleCycle(*adjMatrixGraph, validCycle));
}

TEST_F(CycleDetectionTest, InvalidCycle_TooShort) {
    vector<int> shortPath = {1, 2};
    
    EXPECT_FALSE(isSimpleCycle(*adjListGraph, shortPath));
    EXPECT_FALSE(isSimpleCycle(*adjMatrixGraph, shortPath));
    
    auto result = checkSimpleCycleDetailed(*adjListGraph, shortPath);
    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(result.errorMessage, "Path too short - minimum cycle length is 3");
}

TEST_F(CycleDetectionTest, InvalidCycle_DifferentStartEnd) {
    vector<int> invalidPath = {1, 2, 3, 4};
    
    EXPECT_FALSE(isSimpleCycle(*adjListGraph, invalidPath));
    EXPECT_FALSE(isSimpleCycle(*adjMatrixGraph, invalidPath));
    
    auto result = checkSimpleCycleDetailed(*adjListGraph, invalidPath);
    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(result.errorMessage, "Path does not start and end at the same node");
}

TEST_F(CycleDetectionTest, InvalidCycle_RepeatedNode) {
    vector<int> invalidPath = {1, 2, 1, 3, 1};
    
    EXPECT_FALSE(isSimpleCycle(*adjListGraph, invalidPath));
    EXPECT_FALSE(isSimpleCycle(*adjMatrixGraph, invalidPath));
    
    auto result = checkSimpleCycleDetailed(*adjListGraph, invalidPath);
    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(result.errorMessage, "Node visited more than once (not a simple cycle)");
}

TEST_F(CycleDetectionTest, InvalidCycle_NonAdjacentNodes) {
    vector<int> invalidPath = {1, 3, 2, 1};
    
    EXPECT_FALSE(isSimpleCycle(*adjListGraph, invalidPath));
    EXPECT_FALSE(isSimpleCycle(*adjMatrixGraph, invalidPath));
    
    auto result = checkSimpleCycleDetailed(*adjListGraph, invalidPath);
    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(result.errorMessage, "Invalid edge in path - nodes are not adjacent");
}

TEST_F(CycleDetectionTest, ValidSimpleCycle_Triangle) {
    vector<int> triangleNodes = {1, 2, 3};
    vector<pair<int, int>> triangleEdges = {{1, 2}, {2, 3}, {3, 1}};
    
    AdjListGraph<int> triangleGraph(triangleNodes, triangleEdges);
    AdjMatrixGraph<int> triangleMatrixGraph(triangleNodes, triangleEdges);
    
    vector<int> triangleCycle = {1, 2, 3, 1};
    
    EXPECT_TRUE(isSimpleCycle(triangleGraph, triangleCycle));
    EXPECT_TRUE(isSimpleCycle(triangleMatrixGraph, triangleCycle));
}

TEST_F(CycleDetectionTest, InvalidCycle_EmptyPath) {
    vector<int> emptyPath = {};
    
    EXPECT_FALSE(isSimpleCycle(*adjListGraph, emptyPath));
    EXPECT_FALSE(isSimpleCycle(*adjMatrixGraph, emptyPath));
}

TEST_F(CycleDetectionTest, InvalidCycle_SingleNode) {
    vector<int> singleNode = {1};
    
    EXPECT_FALSE(isSimpleCycle(*adjListGraph, singleNode));
    EXPECT_FALSE(isSimpleCycle(*adjMatrixGraph, singleNode));
}

TEST_F(CycleDetectionTest, ValidCycle_StringNodes) {
    vector<string> nodes = {"A", "B", "C", "D"};
    vector<pair<string, string>> edges = {
        {"A", "B"}, {"B", "C"}, {"C", "D"}, {"D", "A"}
    };
    
    AdjListGraph<string> stringGraph(nodes, edges);
    vector<string> cycle = {"A", "B", "C", "D", "A"};
    
    EXPECT_TRUE(isSimpleCycle(stringGraph, cycle));
    
    auto result = checkSimpleCycleDetailed(stringGraph, cycle);
    EXPECT_TRUE(result.isValid);
}

TEST_F(CycleDetectionTest, ValidCycle_LargerCycle) {
    vector<int> largeNodes = {1, 2, 3, 4, 5, 6};
    vector<pair<int, int>> largeEdges = {
        {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 1}
    };
    
    AdjListGraph<int> largeGraph(largeNodes, largeEdges);
    vector<int> largeCycle = {1, 2, 3, 4, 5, 6, 1};
    
    EXPECT_TRUE(isSimpleCycle(largeGraph, largeCycle));
}

TEST_F(CycleDetectionTest, InvalidCycle_PathNotCycle) {
    vector<int> path = {1, 2, 3, 4, 5};
    
    EXPECT_FALSE(isSimpleCycle(*adjListGraph, path));
    EXPECT_FALSE(isSimpleCycle(*adjMatrixGraph, path));
}

TEST_F(CycleDetectionTest, PerformanceComparison) {
    vector<int> validCycle = {1, 2, 3, 4, 1};
    
    for (int i = 0; i < 1000; ++i) {
        EXPECT_TRUE(isSimpleCycle(*adjListGraph, validCycle));
        EXPECT_TRUE(isSimpleCycle(*adjMatrixGraph, validCycle));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}