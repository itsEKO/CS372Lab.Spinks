#include <iostream>
#include <vector>
#include <string>
#include "../include/SocialGraph.hpp"

using namespace std;

void testKevinBaconConnection(SocialGraph& socialNet, const string& person) {
    vector<string> path;
    bool connected = socialNet.findPathToKevinBacon(person, path);
    
    cout << "\n=== Testing connection: " << person << " -> Kevin Bacon ===" << endl;
    
    if (connected) {
        cout << "* " << person << " IS connected to Kevin Bacon!" << endl;
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
        
        int kevinBaconNumber = socialNet.getKevinBaconNumber(person);
        cout << person << "'s Kevin Bacon Number: " << kevinBaconNumber << endl;
    } else {
        cout << "X " << person << " is NOT connected to Kevin Bacon." << endl;
        cout << "Kevin Bacon Number: -1 (not connected)" << endl;
    }
}

void testGeneralPath(SocialGraph& socialNet, const string& start, const string& end) {
    vector<string> path;
    bool connected = socialNet.findPath(start, end, path);
    
    cout << "\n=== Testing path: " << start << " -> " << end << " ===" << endl;
    
    if (connected) {
        cout << "* Connected! Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
        cout << "Distance: " << (path.size() - 1) << " hops" << endl;
    } else {
        cout << "X No path found between " << start << " and " << end << endl;
    }
}

void demonstrateSevenDegreesRule(SocialGraph& socialNet) {
    cout << "\n=== Seven Degrees of Kevin Bacon Analysis ===" << endl;
    cout << "Testing all people in the network:" << endl;
    cout << "===================================" << endl;
    
    vector<string> allPeople = socialNet.getAllPeople();
    bool allWithinSevenDegrees = true;
    int maxDegrees = 0;
    
    for (const string& person : allPeople) {
        if (person == "Kevin Bacon") continue;
        
        int kevinBaconNumber = socialNet.getKevinBaconNumber(person);
        cout << person << ": Kevin Bacon Number = " << kevinBaconNumber;
        
        if (kevinBaconNumber > 7) {
            cout << " [EXCEEDS 7 DEGREES!]";
            allWithinSevenDegrees = false;
        } else if (kevinBaconNumber == -1) {
            cout << " [NOT CONNECTED!]";
            allWithinSevenDegrees = false;
        } else {
            cout << " [OK]";
            maxDegrees = max(maxDegrees, kevinBaconNumber);
        }
        cout << endl;
    }
    
    cout << "\nSeven Degrees Rule Analysis:" << endl;
    cout << "Maximum degrees in network: " << maxDegrees << endl;
    cout << "All within 7 degrees? " << (allWithinSevenDegrees ? "YES" : "NO") << endl;
}

int main() {
    cout << "Seven Degrees of Kevin Bacon Social Network" << endl;
    cout << "===========================================" << endl;
    
    SocialGraph socialNetwork;
    
    cout << "\nNetwork Statistics:" << endl;
    vector<string> allPeople = socialNetwork.getAllPeople();
    cout << "Total people in network: " << allPeople.size() << endl;
    cout << "Includes: You and Kevin Bacon" << endl;
    
    testKevinBaconConnection(socialNetwork, "You");
    
    testKevinBaconConnection(socialNetwork, "Alice Johnson");
    testKevinBaconConnection(socialNetwork, "Henry Taylor");
    testKevinBaconConnection(socialNetwork, "Quinn Thompson");
    testKevinBaconConnection(socialNetwork, "Emma Brown");
    
    testGeneralPath(socialNetwork, "You", "Alice Johnson");
    testGeneralPath(socialNetwork, "Bob Smith", "Carol Davis");
    testGeneralPath(socialNetwork, "David Wilson", "Kevin Bacon");
    
    demonstrateSevenDegreesRule(socialNetwork);
    
    cout << "\nSocial Network Visualization:" << endl;
    socialNetwork.printGraph();
    
    cout << "\nKey Functions Demonstrated:" << endl;
    cout << "1. findPathToKevinBacon() - finds path from any person to Kevin Bacon" << endl;
    cout << "2. getKevinBaconNumber() - returns the Kevin Bacon number (path length)" << endl;
    cout << "3. findPath() - finds path between any two people" << endl;
    cout << "4. Uses BFS algorithm for shortest path finding" << endl;
    
    cout << "\nFun Fact: Your Kevin Bacon number in this network is: " 
         << socialNetwork.getKevinBaconNumber("You") << endl;
    
    return 0;
}