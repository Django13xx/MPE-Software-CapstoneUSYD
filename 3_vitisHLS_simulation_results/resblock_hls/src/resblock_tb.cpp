#include <iostream>
using namespace std;

// Declaration of the top-level function
void resblock(float input[64][56][56], float output[64][56][56]);

int main() {
    float input[64][56][56];
    float output[64][56][56];

    // Initialize test data
    for (int c = 0; c < 64; c++) {
        for (int i = 0; i < 56; i++) {
            for (int j = 0; j < 56; j++) {
                input[c][i][j] = c + i + j;
            }
        }
    }

    // Call the design function
    resblock(input, output);

    // Verify the result
    bool correct = true;
    for (int c = 0; c < 64; c++) {
        for (int i = 0; i < 56; i++) {
            for (int j = 0; j < 56; j++) {
                if (input[c][i][j] != output[c][i][j]) {
                    correct = false;
                    break;
                }
            }
        }
    }

    // Output the test result
    if (correct) {
        cout << "Test Passed!" << endl;
    } else {
        cout << "Test Failed!" << endl;
    }

    return 0;
}
