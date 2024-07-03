// A solution to Lifeguards: USACO 2018 January Contest, Bronze (Problem 2)

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Input and output files
const string INPUT_FILE_NAME = "lifeguards.in";
const string OUTPUT_FILE_NAME = "lifeguards.out";

// Constraints given by the prompt
const unsigned int MIN_TIME = 0;
const unsigned int MAX_TIME = 1000;
const unsigned int NUM_SHIFTS = (MAX_TIME - MIN_TIME) + 1;

// Store start and end times for a lifeguard shift
typedef struct lifeguard {
    unsigned int start;
    unsigned int end;
} lifeguard_t;

int main(int argc, char **argv) {
    // Check for command-line usage errors
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " " << INPUT_FILE_NAME << endl;
        return 1;
    }

    // Create a file stream to read the input file
    ifstream input_file(INPUT_FILE_NAME);

    // Input file error handling
    if (!input_file.is_open()) {
        cerr << "Unable to open file: " << INPUT_FILE_NAME << endl;
        return 1;
    }

    // Read the number of lifguards
    unsigned int num_lifeguards = 0;
    input_file >> num_lifeguards;

    // Declare lifeguard array
    lifeguard_t lifeguards[num_lifeguards];

    // Read start and end times for all lifeguards
    for (unsigned int i = 0; i < num_lifeguards; i++) {
        unsigned int start_time = 0;
        input_file >> start_time;
        unsigned int end_time = 0;
        input_file >> end_time;
        lifeguards[i] = lifeguard_t{start_time, end_time};
    }

    // Close the input file
    input_file.close();

    // Store the number of lifeguards on duty
    unsigned int lifeguards_on_duty[num_lifeguards][NUM_SHIFTS];
    // Initialize the number of lifeguards on duty to 0
    for (unsigned int i = 0; i < num_lifeguards; i++) {
        for (unsigned int j = 0; j < NUM_SHIFTS; j++) {
            lifeguards_on_duty[i][j] = 0;
        }
    }

    // Determine how many lifeguards are on duty at any given point in time
    for (unsigned int i = 0; i < num_lifeguards; i++) {
        for (unsigned int j = 0; j < num_lifeguards; j++) {
            if (i == j) continue;
            for (unsigned int k = 0; k < NUM_SHIFTS; k++) {
                if (k >= lifeguards[j].start && k < lifeguards[j].end) {
                    lifeguards_on_duty[i][k]++;
                }
            }
        }
    }

    // Determine the longest continuous interval of time that can be covered
    // after firing one lifeguard
    unsigned int max_interval = 0;
    for (unsigned int i = 0; i < num_lifeguards; i++) {
        unsigned int curr_max = 0;
        for (unsigned int j = 0; j < NUM_SHIFTS; j++) {
            while (lifeguards_on_duty[i][j] >= 1 && j < NUM_SHIFTS) {
                curr_max++;
                j++;
            }
            if (curr_max > max_interval) {
                max_interval = curr_max;
            }
        }
    }

    // Create a file stream to write the output file
    ofstream output_file(OUTPUT_FILE_NAME);

    // Output file error handling
    if (!output_file.is_open()) {
        cerr << "Unable to open file: " << OUTPUT_FILE_NAME << endl;
        return 1;
    }

    // Write to the output file
    output_file << max_interval << endl;

    // Close the output file
    output_file.close();

    return 0;
}
