#include <iostream>
#include <limits> 
#include "routine.h"

using namespace std;

int main() {
    Routine process = average_calculator();

    while (!process.done()) {

        cout << "\nThe coroutine is paused" << endl;
        cout << "Press ENTER to continue...";
        
        cin.clear();

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        process.resume();
    }

    return 0;
}