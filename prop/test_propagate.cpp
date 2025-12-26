#include "prop.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Test result structure
struct TestResult {
    string test_name;
    bool passed;
    string message;
};

// Test 1: Check output size
TestResult test_output_size() {
    TestResult result;
    result.test_name = "Output Size Test";

    vector<double> res = propogate_sin(10.0);

    if (res.size() == 100) {
        result.passed = true;
        result.message = "Size correct: 100 samples";
    } else {
        result.passed = false;
        result.message = "Expected 100, got " + to_string(res.size());
    }

    return result;
}

// Test 2: Check accuracy against analytical solution
TestResult test_accuracy() {
    TestResult result;
    result.test_name = "Accuracy Test (Early Time)";

    vector<double> res = propogate_sin(1.0);
    double w = 2.0;

    // Check first few values
    double max_error = 0.0;
    for (int i = 0; i < min(10, (int)res.size()); i++) {
        double t = (i + 1) * 0.1;
        double analytical = sin(w * t);
        double error = abs(res[i] - analytical);
        if (error > max_error) max_error = error;
    }

    double tolerance = 0.05;  // 5% tolerance
    if (max_error < tolerance) {
        result.passed = true;
        result.message = "Max error: " + to_string(max_error);
    } else {
        result.passed = false;
        result.message = "Error too large: " + to_string(max_error);
    }

    return result;
}

// Test 3: Initial condition test
TestResult test_initial_condition() {
    TestResult result;
    result.test_name = "Initial Condition Test";

    vector<double> res = propogate_sin(1.0);
    double w = 2.0;

    // At t=0.1, should be close to sin(0.2)
    double expected = sin(w * 0.1);
    double error = abs(res[0] - expected);

    if (error < 0.01) {
        result.passed = true;
        result.message = "Error: " + to_string(error);
    } else {
        result.passed = false;
        result.message = "Error: " + to_string(error) + " (too large)";
    }

    return result;
}

// Test runner
void run_tests() {
    vector<TestResult> results;

    cout << "========================================" << endl;
    cout << "    PROPAGATE FUNCTION TESTS" << endl;
    cout << "========================================" << endl << endl;

    // Run all tests
    results.push_back(test_output_size());
    results.push_back(test_initial_condition());
    results.push_back(test_accuracy());

    // Print results
    int passed = 0;
    for (const auto& r : results) {
        cout << "[" << (r.passed ? "PASS" : "FAIL") << "] "
             << r.test_name << endl;
        cout << "       " << r.message << endl << endl;
        if (r.passed) passed++;
    }

    // Summary
    cout << "========================================" << endl;
    cout << "Results: " << passed << "/" << results.size() << " tests passed" << endl;
    cout << "========================================" << endl;
}

int main() {
    run_tests();
    return 0;
}
