#include "queue.hpp"
#include <stdexcept>

int josephus(int N, int M) {
    if (N < 1) throw std::invalid_argument("Number of players must be positive");
    if (M < 0) throw std::invalid_argument("Number of passes cannot be negative");
    if (N == 1) return 1;

    Queue<int> circle;
    for (int i = 1; i <= N; ++i) {
        circle.push(i); 
    }

    // Game loop
    while (!circle.empty()) {
        if (circle.front() == circle.back()) {
            return circle.front();
        }

        for (int i = 0; i < M; ++i) {
            if (circle.empty()) break;
            int player = circle.back();
            circle.pop();
            circle.push(player);
        }

        // Eliminate the player holding the potato
        if (!circle.empty()) {
            circle.pop();
        }
    }
}
    int main() {
    int N, M;
    std::cout << "Enter the number of players (N): ";
    std::cin >> N;
    std::cout << "Enter the number of passes (M): ";
    std::cin >> M;

    try {
        int winner = josephus(N, M);
        std::cout << "The winner is player: " << winner << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
