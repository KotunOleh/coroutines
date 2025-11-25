#include "routine.h"
#include <iostream>
#include <iomanip>
#include <numeric>

using namespace std;

Routine average_calculator() {
    deque<int> buffer;
    int input;

    cout << "Enter integer numbers (enter not-a-number to stop):" << endl;

    while (cin >> input) {
        buffer.push_back(input);
        
        if (buffer.size() > 10) {
            buffer.pop_front();
        }

        double sum = 0;
        for (int val : buffer) {
            sum += val;
        }
        double avg = (buffer.empty()) ? 0.0 : (sum / buffer.size());

        cout << "Current: " << input << " | Avg (last " << buffer.size() << "): " 
             << fixed << setprecision(2) << avg << endl;

        co_await Awaiter{buffer};
    }
    
    cout << "Input error or finish. Routine ending" << endl;
}