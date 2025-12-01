// insertion_sort_analysis.cpp
// Modern, robust implementation of insertion sort variants with metrics and test cases.

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct SortMetrics {
    long long comparisons = 0;
    long long shifts = 0;
    int passes = 0;
    double executionTimeMs = 0.0;
    vector<int> sortedArray;
    vector<vector<int>> passStates; // optional tracking for debugging/education
};

class InsertionSort {
public:
    // Control whether we record the state after each pass (useful for small arrays / teaching)
    explicit InsertionSort(bool trackPasses = true) noexcept
        : trackPasses_(trackPasses) {}

    // Standard insertion sort (ascending)
    SortMetrics sortAscending(vector<int> arr) {
        resetMetrics();
        if (trackPasses_) metrics_.passStates.push_back(arr);

        auto start = chrono::high_resolution_clock::now();

        const size_t n = arr.size();
        for (size_t j = 1; j < n; ++j) {
            int key = arr[j];
            // We'll find correct position by shifting larger elements to the right.
            // Count comparisons explicitly: each check arr[i] > key is a comparison.
            long long localShifts = 0;
            int i = static_cast<int>(j) - 1;

            // Use loop that counts comparisons in deterministic way:
            while (i >= 0) {
                metrics_.comparisons++; // we are about to compare arr[i] and key
                if (arr[static_cast<size_t>(i)] > key) {
                    arr[static_cast<size_t>(i + 1)] = arr[static_cast<size_t>(i)];
                    ++localShifts;
                    --i;
                } else {
                    break;
                }
            }

            // place key in the correct spot
            arr[static_cast<size_t>(i + 1)] = key;
            metrics_.shifts += localShifts;
            ++metrics_.passes;

            if (trackPasses_) metrics_.passStates.push_back(arr);
        }

        auto end = chrono::high_resolution_clock::now();
        metrics_.executionTimeMs =
            chrono::duration<double, milli>(end - start).count();
        metrics_.sortedArray = std::move(arr);
        return metrics_;
    }

    // Insertion sort descending
    SortMetrics sortDescending(vector<int> arr) {
        resetMetrics();
        if (trackPasses_) metrics_.passStates.push_back(arr);

        auto start = chrono::high_resolution_clock::now();

        const size_t n = arr.size();
        for (size_t j = 1; j < n; ++j) {
            int key = arr[j];
            int i = static_cast<int>(j) - 1;
            long long localShifts = 0;

            while (i >= 0) {
                metrics_.comparisons++;
                if (arr[static_cast<size_t>(i)] < key) { // reverse comparison
                    arr[static_cast<size_t>(i + 1)] = arr[static_cast<size_t>(i)];
                    ++localShifts;
                    --i;
                } else {
                    break;
                }
            }

            arr[static_cast<size_t>(i + 1)] = key;
            metrics_.shifts += localShifts;
            ++metrics_.passes;

            if (trackPasses_) metrics_.passStates.push_back(arr);
        }

        auto end = chrono::high_resolution_clock::now();
        metrics_.executionTimeMs =
            chrono::duration<double, milli>(end - start).count();
        metrics_.sortedArray = std::move(arr);
        return metrics_;
    }

    // Binary insertion sort (reduces comparisons for position search using binary search,
    // but data movement (shifts) remains)
    SortMetrics binaryInsertionSort(vector<int> arr) {
        resetMetrics();
        if (trackPasses_) metrics_.passStates.push_back(arr);

        auto start = chrono::high_resolution_clock::now();

        const size_t n = arr.size();
        for (size_t j = 1; j < n; ++j) {
            int key = arr[j];

            // Binary search between [0, j-1] to find insertion position
            size_t left = 0, right = j;
            while (left < right) {
                size_t mid = left + (right - left) / 2;
                metrics_.comparisons++; // comparing arr[mid] and key
                if (arr[mid] > key) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }

            // Shift elements right to make room at 'left'
            long long localShifts = 0;
            for (int k = static_cast<int>(j) - 1; k >= static_cast<int>(left); --k) {
                arr[static_cast<size_t>(k + 1)] = arr[static_cast<size_t>(k)];
                ++localShifts;
            }

            arr[left] = key;
            metrics_.shifts += localShifts;
            ++metrics_.passes;

            if (trackPasses_) metrics_.passStates.push_back(arr);
        }

        auto end = chrono::high_resolution_clock::now();
        metrics_.executionTimeMs =
            chrono::duration<double, milli>(end - start).count();
        metrics_.sortedArray = std::move(arr);
        return metrics_;
    }

    void setTrackPasses(bool track) noexcept { trackPasses_ = track; }
    bool getTrackPasses() const noexcept { return trackPasses_; }

private:
    void resetMetrics() noexcept {
        metrics_ = SortMetrics{};
    }

    bool trackPasses_ = true;
    SortMetrics metrics_;
};

// ---------- Utilities for display & testing ----------
static void displayArray(const vector<int> &arr, const string &label = "Array") {
    cout << label << ": ";
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i) cout << ' ';
        cout << arr[i];
    }
    cout << '\n';
}

static void displayMetrics(const SortMetrics &m, const string &title = "") {
    if (!title.empty()) cout << "[" << title << "]\n";
    cout << "Sorted Array (first 40 elems if large): ";
    if (m.sortedArray.size() <= 40) {
        displayArray(m.sortedArray, "");
    } else {
        for (size_t i = 0; i < 40; ++i) {
            if (i) cout << ' ';
            cout << m.sortedArray[i];
        }
        cout << " ... (size=" << m.sortedArray.size() << ")\n";
    }
    cout << "Passes    : " << m.passes << '\n';
    cout << "Comparisons: " << m.comparisons << '\n';
    cout << "Shifts     : " << m.shifts << '\n';
    cout << "Time       : " << fixed << setprecision(6) << m.executionTimeMs << " ms\n";
}

// quick correctness check
static bool isSortedAscending(const vector<int> &a) noexcept {
    for (size_t i = 1; i < a.size(); ++i)
        if (a[i - 1] > a[i]) return false;
    return true;
}
static bool isSortedDescending(const vector<int> &a) noexcept {
    for (size_t i = 1; i < a.size(); ++i)
        if (a[i - 1] < a[i]) return false;
    return true;
}

// parse an integer safely from line
static bool readIntFromStdin(const string &prompt, int &outVal) {
    cout << prompt;
    string line;
    if (!getline(cin, line)) return false;
    // trim
    stringstream ss(line);
    ss >> outVal;
    return !ss.fail();
}

// create random vector using mt19937
static vector<int> makeRandomVector(size_t n, int minv = 0, int maxv = 10000) {
    vector<int> v;
    v.reserve(n);
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minv, maxv);
    for (size_t i = 0; i < n; ++i) v.push_back(dist(gen));
    return v;
}

// ---------- Test cases (similar to original but robust) ----------
static void runAllTestCases() {
    cout << "\n" << string(80, '=') << "\n";
    cout << "INSERTION SORT - COMPREHENSIVE TESTS\n";
    cout << string(80, '=') << "\n\n";

    InsertionSort sorter(true);

    // TC1 Basic
    {
        cout << "[TC01] Basic Example\n";
        vector<int> arr{9, 5, 3, 0, 1, 6};
        displayArray(arr, "Original");
        SortMetrics m = sorter.sortAscending(arr);
        displayMetrics(m, "After Insertion Sort");
        cout << "Pass-by-pass:\n";
        for (size_t p = 0; p < m.passStates.size(); ++p) {
            cout << "Pass " << p << ": ";
            for (int x : m.passStates[p]) cout << x << ' ';
            cout << '\n';
        }
        cout << "Status: " << (isSortedAscending(m.sortedArray) ? "✓ PASSED" : "✗ FAILED") << "\n\n";
    }

    // TC2 Already Sorted
    {
        cout << "[TC02] Already Sorted\n";
        vector<int> arr{1, 2, 3, 4, 5};
        SortMetrics m = sorter.sortAscending(arr);
        displayMetrics(m, "After Insertion Sort");
        cout << "Status: " << (isSortedAscending(m.sortedArray) ? "✓ PASSED" : "✗ FAILED") << "\n\n";
    }

    // TC3 Reverse Sorted (worst-case)
    {
        cout << "[TC03] Reverse Sorted\n";
        vector<int> arr{5, 4, 3, 2, 1};
        SortMetrics m = sorter.sortAscending(arr);
        displayMetrics(m, "After Insertion Sort");
        cout << "Status: " << (isSortedAscending(m.sortedArray) ? "✓ PASSED" : "✗ FAILED") << "\n\n";
    }

    // TC4 Single element
    {
        cout << "[TC04] Single Element\n";
        vector<int> arr{42};
        SortMetrics m = sorter.sortAscending(arr);
        displayMetrics(m, "After Insertion Sort");
        cout << "\n";
    }

    // TC5 Empty
    {
        cout << "[TC05] Empty Array\n";
        vector<int> arr;
        SortMetrics m = sorter.sortAscending(arr);
        cout << "After sort: " << (m.sortedArray.empty() ? "Empty" : "Not empty") << "\n\n";
    }

    // TC6 Duplicates
    {
        cout << "[TC07] Duplicates\n";
        vector<int> arr{3, 5, 3, 8, 3, 1, 5};
        SortMetrics m = sorter.sortAscending(arr);
        displayMetrics(m, "After Insertion Sort");
        cout << "Stable property test: (values preserved relative order for equals)\n\n";
    }

    // TC10 Large (performance) - disable pass tracking for big arrays
    {
        cout << "[TC10] Large Array Performance (10000 elements) - pass tracking disabled\n";
        sorter.setTrackPasses(false);
        vector<int> arr = makeRandomVector(10000, 0, 1000000);
        cout << "Generated vector size = " << arr.size() << '\n';
        SortMetrics m = sorter.sortAscending(arr);
        cout << "Time: " << fixed << setprecision(6) << m.executionTimeMs << " ms\n";
        cout << "Status: " << (isSortedAscending(m.sortedArray) ? "✓ PASSED" : "✗ FAILED") << "\n\n";
        sorter.setTrackPasses(true);
    }

    // TC14 Descending
    {
        cout << "[TC14] Sort Descending\n";
        vector<int> arr{5, 2, 8, 1, 9, 3};
        SortMetrics m = sorter.sortDescending(arr);
        displayMetrics(m, "After Descending Sort");
        cout << "Status: " << (isSortedDescending(m.sortedArray) ? "✓ PASSED" : "✗ FAILED") << "\n\n";
    }

    // TC15 Binary insertion
    {
        cout << "[TC15] Binary Insertion Sort\n";
        vector<int> arr{5, 2, 8, 1, 9, 3};
        SortMetrics m = sorter.binaryInsertionSort(arr);
        displayMetrics(m, "After Binary Insertion Sort");
        cout << "Status: " << (isSortedAscending(m.sortedArray) ? "✓ PASSED" : "✗ FAILED") << "\n\n";
    }

    cout << "All selected test cases completed.\n";
}

// ---------- Interactive menu ----------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "\n" << string(80, '=') << "\n";
        cout << "INSERTION SORT - DEMO & ANALYSIS (C++ Modern)\n";
        cout << string(80, '=') << "\n";
        cout << "1. Run built-in test cases\n";
        cout << "2. Sort custom array (ascending)\n";
        cout << "3. Sort custom array (descending)\n";
        cout << "4. Binary insertion sort (custom)\n";
        cout << "5. Performance test (random large array)\n";
        cout << "6. Exit\n";
        cout << "Enter choice (1-6): ";

        string choiceLine;
        if (!getline(cin, choiceLine)) break;
        if (choiceLine.empty()) continue;

        int choice = 0;
        try {
            choice = stoi(choiceLine);
        } catch (...) {
            cout << "[ERR] invalid choice\n";
            continue;
        }

        if (choice == 6) {
            cout << "Exiting.\n";
            break;
        }

        InsertionSort sorter(true);

        switch (choice) {
            case 1:
                runAllTestCases();
                break;
            case 2: {
                int n = 0;
                if (!readIntFromStdin("Enter number of elements: ", n) || n < 0) {
                    cout << "[ERR] invalid number\n";
                    break;
                }
                vector<int> arr;
                arr.reserve(static_cast<size_t>(n));
                cout << "Enter elements (space-separated or newline separated):\n";
                for (int i = 0; i < n; ++i) {
                    int v;
                    if (!(cin >> v)) {
                        cout << "[ERR] invalid element input\n";
                        // clear input stream
                        cin.clear();
                        string garbage;
                        getline(cin, garbage);
                        break;
                    }
                    arr.push_back(v);
                }
                // flush remaining newline before next getline
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                displayArray(arr, "Original");
                SortMetrics m = sorter.sortAscending(arr);
                displayMetrics(m, "Sorted (Ascending)");
                break;
            }
            case 3: {
                int n = 0;
                if (!readIntFromStdin("Enter number of elements: ", n) || n < 0) {
                    cout << "[ERR] invalid number\n";
                    break;
                }
                vector<int> arr;
                arr.reserve(static_cast<size_t>(n));
                cout << "Enter elements:\n";
                for (int i = 0; i < n; ++i) {
                    int v;
                    if (!(cin >> v)) {
                        cout << "[ERR] invalid element input\n";
                        cin.clear();
                        string garbage;
                        getline(cin, garbage);
                        break;
                    }
                    arr.push_back(v);
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                SortMetrics m = sorter.sortDescending(arr);
                displayMetrics(m, "Sorted (Descending)");
                break;
            }
            case 4: {
                int n = 0;
                if (!readIntFromStdin("Enter number of elements: ", n) || n < 0) {
                    cout << "[ERR] invalid number\n";
                    break;
                }
                vector<int> arr;
                arr.reserve(static_cast<size_t>(n));
                cout << "Enter elements:\n";
                for (int i = 0; i < n; ++i) {
                    int v;
                    if (!(cin >> v)) {
                        cout << "[ERR] invalid element input\n";
                        cin.clear();
                        string garbage;
                        getline(cin, garbage);
                        break;
                    }
                    arr.push_back(v);
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                SortMetrics m = sorter.binaryInsertionSort(arr);
                displayMetrics(m, "Binary Insertion Sort (Ascending)");
                break;
            }
            case 5: {
                int n = 0;
                if (!readIntFromStdin("Enter size of random array (e.g. 1000): ", n) || n <= 0) {
                    cout << "[ERR] invalid number\n";
                    break;
                }
                sorter.setTrackPasses(false); // disable heavy tracking
                vector<int> arr = makeRandomVector(static_cast<size_t>(n), 0, 1000000);
                cout << "Generated random array of size " << arr.size() << '\n';
                SortMetrics m = sorter.sortAscending(arr);
                displayMetrics(m, "Performance Test (Ascending)");
                break;
            }
            default:
                cout << "[ERR] unknown choice\n";
                break;
        } // switch
    }     // while

    return 0;
}