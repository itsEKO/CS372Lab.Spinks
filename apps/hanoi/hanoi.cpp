#include <iostream>
#include <chrono>
using namespace std;

void moveDisks(int, int, int, int);
void printIt(int, int, int);

int main() {
    const int FROMPEG = 1;
    const int TOPEG = 3;
    const int TEMPPEG = 2;

    cout << "--- Recursive Version Timings ---" << endl;

    for (int numdisks : {5, 10, 15, 20, 25, 30, 35}) {
        cout << "Number of disks: " << numdisks << endl;

        auto start = chrono::high_resolution_clock::now();

        moveDisks(numdisks, FROMPEG, TOPEG, TEMPPEG);

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
        cout << "Time taken: " << duration.count() << " milliseconds" << endl;
        cout << "---------------------------------" << endl;
    }
    return 0;
}

void moveDisks(int num, int fromPeg, int toPeg, int tempPeg) {
    if (num > 0) {
        moveDisks(num - 1, fromPeg, tempPeg, toPeg);
        moveDisks(num - 1, tempPeg, toPeg, fromPeg);
    }
}

void printIt(int disk, int fromPeg, int toPeg) {
    // keep empty
}