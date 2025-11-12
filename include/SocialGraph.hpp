#pragma once
#include "AdjListGraph.hpp"
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

class SocialGraph {
private:
    AdjListGraph<std::string> graph;
    
public:
    SocialGraph() {
        buildSocialNetwork();
    }
    
    bool findPathToKevinBacon(const std::string& startPerson, std::vector<std::string>& path) {
        return findPath(startPerson, "Kevin Bacon", path);
    }
    
    bool findPath(const std::string& start, const std::string& end, std::vector<std::string>& path) {
        path.clear();
        
        if (start == end) {
            path.push_back(start);
            return true;
        }
        
        std::queue<std::string> queue;
        std::map<std::string, bool> visited;
        std::map<std::string, std::string> parent;
        
        queue.push(start);
        visited[start] = true;
        parent[start] = "";
        
        while (!queue.empty()) {
            std::string current = queue.front();
            queue.pop();
            
            if (current == end) {
                std::string node = end;
                while (!node.empty()) {
                    path.push_back(node);
                    node = parent[node];
                }
                std::reverse(path.begin(), path.end());
                return true;
            }
            
            std::vector<std::string> neighbors = graph.neighbors(current);
            for (const std::string& neighbor : neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    parent[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }
        
        return false;
    }
    
    int getKevinBaconNumber(const std::string& person) {
        std::vector<std::string> path;
        if (findPathToKevinBacon(person, path)) {
            return path.size() - 1;
        }
        return -1;
    }
    
    void printGraph() {
        std::cout << "Social Network Connections:" << std::endl;
        std::cout << "===========================" << std::endl;
        for (const std::string& person : getAllPeople()) {
            std::cout << person << " -> ";
            std::vector<std::string> connections = graph.neighbors(person);
            for (size_t i = 0; i < connections.size(); ++i) {
                std::cout << connections[i];
                if (i < connections.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    
    std::vector<std::string> getAllPeople() {
        std::vector<std::string> people = {
            "You", "Kevin Bacon", "Alice Johnson", "Bob Smith", "Carol Davis",
            "David Wilson", "Emma Brown", "Frank Miller", "Grace Lee", "Henry Taylor",
            "Ivy Chen", "Jack Robinson", "Kelly White", "Liam Green", "Mia Clark",
            "Noah Adams", "Olivia Martinez", "Paul Anderson", "Quinn Thompson", "Ruby Hall"
        };
        return people;
    }

private:
    void buildSocialNetwork() {
        std::vector<std::string> people = getAllPeople();
        
        std::vector<std::pair<std::string, std::string>> connections = {
            {"You", "Alice Johnson"},
            {"You", "Bob Smith"},
            {"You", "David Wilson"},
            
            {"Alice Johnson", "Carol Davis"},
            {"Alice Johnson", "Emma Brown"},
            {"Alice Johnson", "Frank Miller"},
            
            {"Bob Smith", "Grace Lee"},
            {"Bob Smith", "Henry Taylor"},
            
            {"Carol Davis", "Ivy Chen"},
            {"Carol Davis", "Jack Robinson"},
            
            {"David Wilson", "Kelly White"},
            {"David Wilson", "Liam Green"},
            
            {"Emma Brown", "Mia Clark"},
            {"Emma Brown", "Noah Adams"},
            
            {"Frank Miller", "Olivia Martinez"},
            {"Frank Miller", "Paul Anderson"},
            
            {"Grace Lee", "Quinn Thompson"},
            {"Grace Lee", "Ruby Hall"},
            
            {"Henry Taylor", "Kevin Bacon"},
            
            {"Ivy Chen", "Kevin Bacon"},
            
            {"Jack Robinson", "Quinn Thompson"},
            
            {"Kelly White", "Ruby Hall"},
            
            {"Liam Green", "Noah Adams"},
            
            {"Mia Clark", "Paul Anderson"},
            
            {"Olivia Martinez", "Kevin Bacon"},
            
            {"Quinn Thompson", "Kevin Bacon"},
            
            {"Ruby Hall", "Kevin Bacon"}
        };
        
        graph = AdjListGraph<std::string>(people, connections);
        
        for (const auto& connection : connections) {
            graph.addEdge(connection.second, connection.first);
        }
    }
};