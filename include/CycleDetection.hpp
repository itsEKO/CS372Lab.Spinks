#pragma once
#include "Graph.hpp"
#include <vector>
#include <set>
#include <unordered_set>

template <class N>
bool isSimpleCycle(const Graph<N>& graph, const std::vector<N>& path) {
    if (path.size() < 3) {
        return false;
    }
    
    if (path.front() != path.back()) {
        return false;
    }
    
    std::unordered_set<N> visitedNodes;
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        const N& currentNode = path[i];
        
        if (visitedNodes.find(currentNode) != visitedNodes.end()) {
            return false;
        }
        
        visitedNodes.insert(currentNode);
    }
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        const N& currentNode = path[i];
        const N& nextNode = path[i + 1];
        
        if (!graph.adjacent(currentNode, nextNode)) {
            return false;
        }
    }
    
    return true;
}

template <class N>
struct CycleCheckResult {
    bool isValid;
    std::string errorMessage;
    
    CycleCheckResult(bool valid, const std::string& message = "") 
        : isValid(valid), errorMessage(message) {}
};

template <class N>
CycleCheckResult<N> checkSimpleCycleDetailed(const Graph<N>& graph, const std::vector<N>& path) {
    if (path.size() < 3) {
        return CycleCheckResult<N>(false, "Path too short - minimum cycle length is 3");
    }
    
    if (path.front() != path.back()) {
        return CycleCheckResult<N>(false, "Path does not start and end at the same node");
    }
    
    std::unordered_set<N> visitedNodes;
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        const N& currentNode = path[i];
        
        if (visitedNodes.find(currentNode) != visitedNodes.end()) {
            return CycleCheckResult<N>(false, "Node visited more than once (not a simple cycle)");
        }
        
        visitedNodes.insert(currentNode);
    }
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        const N& currentNode = path[i];
        const N& nextNode = path[i + 1];
        
        if (!graph.adjacent(currentNode, nextNode)) {
            return CycleCheckResult<N>(false, "Invalid edge in path - nodes are not adjacent");
        }
    }
    
    return CycleCheckResult<N>(true, "Valid simple cycle");
}