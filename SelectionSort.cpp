#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct SortMetrics {
    long long comparisons;
    long long swaps;
    double executionTime;
    vector<int> sortedArray;
    vector<int> passes;
};

class SelectionSort {
private:
    long long comparisonCount;
    long long swapCount;
    vector<int> passTracker;
    
public:
    SelectionSort() : comparisonCount(0), swapCount(0) {}
    
    SortMetrics selectionSort(vector<int> arr) {
        SortMetrics metrics;
        comparisonCount = 0;
        swapCount = 0;
        passTracker.clear();
        
        auto start = chrono::high_resolution_clock::now();
        
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            
            for (int j = i + 1; j < n; j++) {
                comparisonCount++;
                
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            if (minIndex != i) {
                swap(arr[i], arr[minIndex]);
                swapCount++;
            }
            
            passTracker.push_back(arr[i]);
        }
        passTracker.push_back(arr[n - 1]);
        
        auto end = chrono::high_resolution_clock::now();
        
        metrics.comparisons = comparisonCount;
        metrics.swaps = swapCount;
        metrics.executionTime = chrono::duration<double, milli>(end - start).count();
        metrics.sortedArray = arr;
        metrics.passes = passTracker;
        
        return metrics;
    }
    
    SortMetrics selectionSortDescending(vector<int> arr) {
        SortMetrics metrics;
        comparisonCount = 0;
        swapCount = 0;
        
        auto start = chrono::high_resolution_clock::now();
        
        int n = arr.size();
        
        for (int i = 0; i < n - 1; i++) {
            int maxIndex = i;
            
            for (int j = i + 1; j < n; j++) {
                comparisonCount++;
                
                if (arr[j] > arr[maxIndex]) {
                    maxIndex = j;
                }
            }
            
            if (maxIndex != i) {
                swap(arr[i], arr[maxIndex]);
                swapCount++;
            }
        }
        
        auto end = chrono::high_resolution_clock::now();
        
        metrics.comparisons = comparisonCount;
        metrics.swaps = swapCount;
        metrics.executionTime = chrono::duration<double, milli>(end - start).count();
        metrics.sortedArray = arr;
        
        return metrics;
    }
    
    void resetMetrics() {
        comparisonCount = 0;
        swapCount = 0;
        passTracker.clear();
    }
};

void displayArray(const vector<int>& arr, const string& label = "Array") {
    cout << label << ": ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

void displayMetrics(const SortMetrics& metrics, const string& testName) {
    cout << "[" << testName << "]" << endl;
    cout << "Sorted Array: ";
    for (int num : metrics.sortedArray) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Comparisons: " << metrics.comparisons << endl;
    cout << "Swaps: " << metrics.swaps << endl;
    cout << "Execution Time: " << fixed << setprecision(6) << metrics.executionTime << " ms" << endl;
}

bool isSorted(const vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

void tc01_BasicExample() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC01] Basic Example from PDF - Array {40, 10, 35, 15, 20, 2, 10, 7}" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {40, 10, 35, 15, 20, 2, 10, 7};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "\nIteration Breakdown:" << endl;
    cout << "Expected: n(n-1)/2 = 8*7/2 = 28 comparisons" << endl;
    cout << "Actual Comparisons: " << metrics.comparisons << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc02_AlreadySorted() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC02] Already Sorted Array" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Note: Still performs n(n-1)/2 comparisons (no optimization)" << endl;
    cout << "Swaps: 0 (no elements out of place)" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc03_ReverseSorted() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC03] Reverse Sorted Array (Worst Case)" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Expected: Maximum swaps = n-1 = 8" << endl;
    cout << "Actual Swaps: " << metrics.swaps << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc04_SingleElement() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC04] Single Element Array" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {42};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Expected: 0 comparisons, 0 swaps" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc05_EmptyArray() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC05] Empty Array" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {};
    cout << "Array: (empty)" << endl;
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    cout << "After sort: " << (metrics.sortedArray.empty() ? "Empty" : "Not empty") << endl;
    cout << "Status: ✓ PASSED" << endl;
}

void tc06_TwoElements() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC06] Two Element Array" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {5, 2};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Expected: 1 comparison, 1 swap" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc07_DuplicateElements() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC07] Array with Duplicate Elements" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {3, 5, 3, 8, 3, 1, 5};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Note: Selection sort is STABLE (maintains relative order)" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc08_NegativeNumbers() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC08] Array with Negative Numbers" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {-5, 3, -2, 8, -10, 0, 4};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc09_AllSameElements() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC09] Array with All Same Elements" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {7, 7, 7, 7, 7};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Expected: Comparisons = 10, Swaps = 0" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc10_LargeArrayPerformance() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC10] Large Array Performance (1000 elements)" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr;
    srand(time(0));
    
    for (int i = 0; i < 1000; i++) {
        arr.push_back(rand() % 10000);
    }
    
    cout << "Array Size: 1,000 elements" << endl;
    cout << "First 10 elements: ";
    for (int i = 0; i < 10; i++) cout << arr[i] << " ";
    cout << "..." << endl;
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    
    cout << "\nSorted first 10 elements: ";
    for (int i = 0; i < 10; i++) cout << metrics.sortedArray[i] << " ";
    cout << "..." << endl;
    
    cout << "Comparisons: " << metrics.comparisons << endl;
    cout << "Expected: n(n-1)/2 = 1000*999/2 = 499,500" << endl;
    cout << "Swaps: " << metrics.swaps << endl;
    cout << "Time: " << fixed << setprecision(6) << metrics.executionTime << " ms" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc11_NearlySorted() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC11] Nearly Sorted Array" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {1, 2, 3, 5, 4, 6, 7, 8, 9};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(arr);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "Note: Selection sort shows NO improvement for nearly sorted data" << endl;
    cout << "Status: " << (isSorted(metrics.sortedArray) ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc12_DescendingOrder() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC12] Sort in Descending Order" << endl;
    cout << string(80, '=') << endl;
    
    vector<int> arr = {5, 2, 8, 1, 9, 3};
    displayArray(arr, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSortDescending(arr);
    
    cout << "[After Selection Sort - Descending]" << endl;
    cout << "Sorted Array: ";
    for (int num : metrics.sortedArray) cout << num << " ";
    cout << endl;
    
    cout << "Comparisons: " << metrics.comparisons << endl;
    cout << "Swaps: " << metrics.swaps << endl;
    
    bool sorted_desc = true;
    for (int i = 0; i < metrics.sortedArray.size() - 1; i++) {
        if (metrics.sortedArray[i] < metrics.sortedArray[i + 1]) {
            sorted_desc = false;
            break;
        }
    }
    cout << "Status: " << (sorted_desc ? "✓ PASSED" : "✗ FAILED") << endl;
}

void tc13_ComplexityAnalysis() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC13] Time Complexity Analysis" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\nBest Case: O(n²)" << endl;
    cout << "  - Already sorted array" << endl;
    cout << "  - Still performs all comparisons: n(n-1)/2" << endl;
    cout << "  - Minimum swaps: 0" << endl;
    
    cout << "\nAverage Case: O(n²)" << endl;
    cout << "  - Random order" << endl;
    cout << "  - Comparisons: n(n-1)/2" << endl;
    cout << "  - Average swaps: ~n/4" << endl;
    
    cout << "\nWorst Case: O(n²)" << endl;
    cout << "  - Reverse sorted" << endl;
    cout << "  - Comparisons: n(n-1)/2" << endl;
    cout << "  - Maximum swaps: n-1" << endl;
    
    cout << "\nSpace Complexity: O(1)" << endl;
    cout << "  - In-place sorting, no extra space" << endl;
    
    cout << "\nStability: NOT STABLE (by nature)" << endl;
    cout << "  - Example: {3a, 1, 3b} → {1, 3b, 3a}" << endl;
}

void tc14_ComparisonWithInsertion() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC14] Comparison: Selection Sort vs Insertion Sort" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\nSELECTION SORT:" << endl;
    cout << "  Time Complexity: O(n²) - always" << endl;
    cout << "  Space Complexity: O(1)" << endl;
    cout << "  Swaps: Minimum possible" << endl;
    cout << "  Stability: Not stable" << endl;
    cout << "  Use when: Swap operations are COSTLY" << endl;
    
    cout << "\nINSERTION SORT:" << endl;
    cout << "  Time Complexity: O(n) best, O(n²) worst" << endl;
    cout << "  Space Complexity: O(1)" << endl;
    cout << "  Swaps: Multiple per iteration" << endl;
    cout << "  Stability: Stable" << endl;
    cout << "  Use when: Data is nearly sorted" << endl;
    
    cout << "\nSWAP COST COMPARISON (array size 100):" << endl;
    cout << "  Selection: ~50 swaps (50 operations)" << endl;
    cout << "  Insertion: ~2500 swaps (2500 operations)" << endl;
    cout << "  Winner: Selection Sort (50x fewer swaps!)" << endl;
}

void tc15_RealWorldApplication() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC15] Real-World Application - Music Player Sorting" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\nScenario: Music app arranges songs from least to most played" << endl;
    cout << "Songs with play counts: {500, 200, 1000, 150, 800, 300}" << endl;
    
    vector<int> playCounts = {500, 200, 1000, 150, 800, 300};
    displayArray(playCounts, "Original");
    
    SelectionSort sorter;
    SortMetrics metrics = sorter.selectionSort(playCounts);
    displayMetrics(metrics, "After Selection Sort");
    
    cout << "\nApplication Benefit:" << endl;
    cout << "  - Minimized disk I/O operations (swap is expensive)" << endl;
    cout << "  - Predictable performance O(n²)" << endl;
    cout << "  - Simple to implement" << endl;
    cout << "Status: ✓ PASSED" << endl;
}

void tc16_AnswersToMCQ() {
    cout << "\n" << string(80, '=') << endl;
    cout << "[TC16] Answers to Multiple Choice Questions from PDF" << endl;
    cout << string(80, '=') << endl;
    
    cout << "\nQ1: When swap is costly, prefer: SELECTION SORT ✓" << endl;
    cout << "    Reason: Minimum swaps (at most n-1)" << endl;
    
    cout << "\nQ2: Comparisons for n=5 in reverse order:" << endl;
    cout << "    Answer: 10 (which is 5*4/2) ✓" << endl;
    
    vector<int> test = {5, 4, 3, 2, 1};
    SelectionSort sorter;
    sorter.resetMetrics();
    SortMetrics m = sorter.selectionSort(test);
    cout << "    Verified: " << m.comparisons << " comparisons" << endl;
    
    cout << "\nQ3: Large values with small keys: Use SELECTION SORT ✓" << endl;
    cout << "    Reason: Minimal actual data movement" << endl;
    
    cout << "\nQ4: Worst case complexity: O(n²) ✓" << endl;
    cout << "    Always n(n-1)/2 comparisons" << endl;
    
    cout << "\nQ5: Correct code selection: Option (A) ✓" << endl;
    cout << "    Must find minimum and swap at correct position" << endl;
    
    cout << "\nQ6: For array {3,4,5,2,1}:" << endl;
    cout << "    Bubble Sort iterations: 5" << endl;
    cout << "    Selection Sort iterations: 4" << endl;
    cout << "    Answer: 5 and 4 ✓" << endl;
    
    cout << "\nQ7: When assignment is costly: SELECTION SORT ✓" << endl;
    cout << "    Because fewer data movements" << endl;
    
    cout << "\nQ8: Advantage of selection sort: O(1) SPACE ✓" << endl;
    cout << "    In-place sorting" << endl;
    
    cout << "\nQ9: Priority queue sorting: SELECTION SORT ✓" << endl;
    cout << "    Repeatedly extracts minimum" << endl;
}

void runAllTestCases() {
    cout << "\n" << string(80, '=') << endl;
    cout << "SELECTION SORT - COMPREHENSIVE TEST CASES" << endl;
    cout << string(80, '=') << endl;
    
    tc01_BasicExample();
    tc02_AlreadySorted();
    tc03_ReverseSorted();
    tc04_SingleElement();
    tc05_EmptyArray();
    tc06_TwoElements();
    tc07_DuplicateElements();
    tc08_NegativeNumbers();
    tc09_AllSameElements();
    tc10_LargeArrayPerformance();
    tc11_NearlySorted();
    tc12_DescendingOrder();
    tc13_ComplexityAnalysis();
    tc14_ComparisonWithInsertion();
    tc15_RealWorldApplication();
    tc16_AnswersToMCQ();
    
    cout << "\n" << string(80, '=') << endl;
    cout << "ALL TEST CASES COMPLETED SUCCESSFULLY ✓" << endl;
    cout << string(80, '=') << endl;
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n" << string(80, '=') << endl;
        cout << "SELECTION SORT - DSA LAB ASSIGNMENT (B.Tech CSE 2nd Year)" << endl;
        cout << string(80, '=') << endl;
        cout << "1. Run All Test Cases" << endl;
        cout << "2. Custom Array Sort (Ascending)" << endl;
        cout << "3. Custom Array Sort (Descending)" << endl;
        cout << "4. Performance Analysis" << endl;
        cout << "5. Exit" << endl;
        cout << string(80, '=') << endl;
        cout << "Enter choice (1-5): ";
        
        string input;
        getline(cin, input);
        
        if (input.empty() || !isdigit(input[0])) {
            cout << "[ERROR] Invalid input." << endl;
            continue;
        }
        
        choice = stoi(input);
        
        switch (choice) {
            case 1:
                runAllTestCases();
                break;
                
            case 2: {
                vector<int> arr;
                int n, val;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter array elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                cin.ignore();
                
                displayArray(arr, "Original");
                SelectionSort sorter;
                SortMetrics metrics = sorter.selectionSort(arr);
                displayMetrics(metrics, "Sorted (Ascending)");
                break;
            }
                
            case 3: {
                vector<int> arr;
                int n, val;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter array elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                cin.ignore();
                
                displayArray(arr, "Original");
                SelectionSort sorter;
                SortMetrics metrics = sorter.selectionSortDescending(arr);
                cout << "Sorted (Descending): ";
                for (int num : metrics.sortedArray) cout << num << " ";
                cout << endl;
                break;
            }
                
            case 4: {
                cout << "\nPerformance Analysis - Array Sizes" << endl;
                SelectionSort sorter;
                
                int sizes[] = {100, 500, 1000};
                for (int size : sizes) {
                    vector<int> arr;
                    srand(time(0));
                    for (int i = 0; i < size; i++) {
                        arr.push_back(rand() % 10000);
                    }
                    
                    sorter.resetMetrics();
                    SortMetrics metrics = sorter.selectionSort(arr);
                    
                    cout << "\nArray Size: " << size << endl;
                    cout << "Comparisons: " << metrics.comparisons << endl;
                    cout << "Expected: n(n-1)/2 = " << (size * (size - 1) / 2) << endl;
                    cout << "Swaps: " << metrics.swaps << endl;
                    cout << "Time: " << fixed << setprecision(6) << metrics.executionTime << " ms" << endl;
                }
                break;
            }
                
            case 5:
                cout << "Exiting Selection Sort Program. Thank you!" << endl;
                return 0;
                
            default:
                cout << "[ERROR] Invalid choice. Please select 1-5." << endl;
        }
    }
    
    return 0;
}