// A solution to Lifeguards: USACO 2018 January Contest, Bronze (Problem 2)

#include <assert.h>

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
const unsigned int NUM_SHIFTS = MAX_TIME - MIN_TIME;

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
    assert(num_lifeguards >= 1 && num_lifeguards <= 1000);

    // Declare lifeguard array
    lifeguard_t lifeguards[num_lifeguards];

    // Read start and end times for all lifeguards
    for (unsigned int i = 0; i < num_lifeguards; i++) {
        unsigned int start_time = 0;
        input_file >> start_time;
        assert(start_time >= 0 && start_time <= 1000);
        unsigned int end_time = 0;
        input_file >> end_time;
        assert(end_time >= 0 && end_time <= 1000);
        lifeguards[i] = lifeguard_t{start_time, end_time};
    }

    // Close the input file
    input_file.close();

    // Store the number of lifeguards on duty at any given point in time
    unsigned int lifeguards_on_duty[NUM_SHIFTS];
    // Initialize the number of lifeguards on duty at all points in time to 0
    for (unsigned int i = 0; i < NUM_SHIFTS; i++) {
        lifeguards_on_duty[i] = 0;
    }

    // Populate the number of lifeguards on duty
    for (unsigned int i = 0; i < num_lifeguards; i++) {
        lifeguard_t lifeguard = lifeguards[i];
        for (unsigned int j = lifeguard.start; j < lifeguard.end; j++) {
            lifeguards_on_duty[j]++;
        }
    }

    // Determine the maximum amount of time that can be covered by the remaining
    // lifeguards after firing exactly one lifeguard
    unsigned int max_time = 0;
    for (unsigned int i = 0; i < num_lifeguards; i++) {
        // Choose which lifeguard will be fired
        lifeguard_t fired_lifeguard = lifeguards[i];
        unsigned int curr_max = 0;
        for (unsigned int j = 0; j < NUM_SHIFTS; j++) {
            unsigned int num_on_duty = lifeguards_on_duty[j];
            // Decrement the number of lifeguards on duty if the current shift
            // will be affected by the fired lifeguard
            if (j >= fired_lifeguard.start && j < fired_lifeguard.end) {
                num_on_duty--;
            }
            // Increment the amount of time covered
            if (num_on_duty >= 1) {
                curr_max++;
            }
        }
        // Update the maximum amount of time that can be covered
        if (curr_max > max_time) {
            max_time = curr_max;
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
    output_file << max_time << endl;

    // Close the output file
    output_file.close();

    return 0;
}
