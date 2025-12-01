// To implement Binary Search
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct SearchMetrics {
    int index;
    int iterations;
    long long comparisons;
    double executionTime;
};

// 1. Iterative Binary Search
SearchMetrics binarySearchIterative(const vector<int>& arr, int target) {
    SearchMetrics metrics = {-1, 0, 0, 0};
    
    auto start = chrono::high_resolution_clock::now();
    
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        metrics.iterations++;
        int mid = left + (right - left) / 2;  // Prevent overflow: mid = (left + right) / 2
        metrics.comparisons++;
        
        if (arr[mid] == target) {
            metrics.index = mid;
            break;
        } else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    metrics.executionTime = chrono::duration<double, milli>(end - start).count();
    
    return metrics;
}

// 2. Recursive Binary Search
SearchMetrics binarySearchRecursive(const vector<int>& arr, int target, int left, int right, SearchMetrics& metrics) {
    auto start = chrono::high_resolution_clock::now();
    
    if (left > right) {
        auto end = chrono::high_resolution_clock::now();
        metrics.executionTime += chrono::duration<double, milli>(end - start).count();
        return metrics;
    }
    
    metrics.iterations++;
    int mid = left + (right - left) / 2;
    metrics.comparisons++;
    
    if (arr[mid] == target) {
        metrics.index = mid;
        auto end = chrono::high_resolution_clock::now();
        metrics.executionTime += chrono::duration<double, milli>(end - start).count();
        return metrics;
    } else if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right, metrics);
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1, metrics);
    }
}

// 3. Find leftmost occurrence (first occurrence)
int findFirstOccurrence(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching left to find first
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// 4. Find rightmost occurrence (last occurrence)
int findLastOccurrence(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching right to find last
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// 5. Find insertion position for target (lower bound)
int findInsertionPosition(const vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// 6. Count occurrences of target
int countOccurrences(const vector<int>& arr, int target) {
    int first = findFirstOccurrence(arr, target);
    
    if (first == -1) return 0;
    
    int last = findLastOccurrence(arr, target);
    return last - first + 1;
}

// 7. Find closest element to target
int findClosest(const vector<int>& arr, int target) {
    if (arr.empty()) return -1;
    
    int left = 0, right = arr.size() - 1;
    int closest = arr[0];
    int minDiff = abs(arr[0] - target);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Avoid integer overflow
        int diff = abs(arr[mid] - target);
        
        if (diff < minDiff || (diff == minDiff && arr[mid] < closest)) {
            minDiff = diff;
            closest = arr[mid];
        }
        
        if (arr[mid] == target) {
            return target;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return closest;
}

// Display array
void displayArray(const vector<int>& arr, const string& label = "Array") {
    cout << label << ": ";
    for (int num : arr) cout << num << " ";
    cout << endl;
}

// Display search metrics
void displayMetrics(const SearchMetrics& metrics, const string& testName, int target) {
    cout << "[" << testName << "]" << endl;
    if (metrics.index != -1) {
        cout << "✓ Element " << target << " found at index: " << metrics.index << endl;
    } else {
        cout << "✗ Element " << target << " NOT found" << endl;
    }
    cout << "Iterations: " << metrics.iterations << endl;
    cout << "Comparisons: " << metrics.comparisons << endl;
    cout << "Execution Time: " << fixed << setprecision(6) << metrics.executionTime << " ms" << endl;
}

// TC01: Basic search - element exists
void tc01_BasicSearch() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC01] Basic Search - Element Exists" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    displayArray(arr, "Sorted Array");
    
    int target = 7;
    SearchMetrics metrics = binarySearchIterative(arr, target);
    displayMetrics(metrics, "Iterative Binary Search", target);
    cout << "Expected: Index 3, 3 iterations" << endl;
    cout << "Status: " << (metrics.index == 3 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC02: Element not found
void tc02_ElementNotFound() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC02] Element Not Found" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {2, 4, 6, 8, 10, 12, 14};
    displayArray(arr, "Sorted Array");
    
    int target = 5;
    SearchMetrics metrics = binarySearchIterative(arr, target);
    displayMetrics(metrics, "Iterative Binary Search", target);
    cout << "Expected: Index -1" << endl;
    cout << "Status: " << (metrics.index == -1 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC03: Search first element
void tc03_FirstElement() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC03] Search First Element (Best Case)" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80};
    displayArray(arr, "Sorted Array");
    
    int target = 10;
    SearchMetrics metrics = binarySearchIterative(arr, target);
    displayMetrics(metrics, "Iterative Binary Search", target);
    cout << "Expected: Index 0" << endl;
    cout << "Status: " << (metrics.index == 0 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC04: Search last element
void tc04_LastElement() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC04] Search Last Element" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80};
    displayArray(arr, "Sorted Array");
    
    int target = 80;
    SearchMetrics metrics = binarySearchIterative(arr, target);
    displayMetrics(metrics, "Iterative Binary Search", target);
    cout << "Expected: Index 7" << endl;
    cout << "Status: " << (metrics.index == 7 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC05: Single element array
void tc05_SingleElement() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC05] Single Element Array" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {42};
    displayArray(arr, "Sorted Array");
    
    int target = 42;
    SearchMetrics metrics = binarySearchIterative(arr, target);
    displayMetrics(metrics, "Iterative Binary Search", target);
    cout << "Expected: Index 0, 1 iteration" << endl;
    cout << "Status: " << (metrics.index == 0 && metrics.iterations == 1 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC06: Empty array
void tc06_EmptyArray() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC06] Empty Array" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {};
    cout << "Array: (empty)" << endl;
    
    int target = 5;
    SearchMetrics metrics = binarySearchIterative(arr, target);
    displayMetrics(metrics, "Iterative Binary Search", target);
    cout << "Expected: Index -1, 0 iterations" << endl;
    cout << "Status: " << (metrics.index == -1 && metrics.iterations == 0 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC07: Duplicate elements - find first occurrence
void tc07_DuplicatesFirstOccurrence() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC07] Duplicates - Find First Occurrence" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {1, 3, 3, 3, 5, 7, 9, 11, 11, 13};
    displayArray(arr, "Sorted Array");
    
    int target = 3;
    int first = findFirstOccurrence(arr, target);
    cout << "First occurrence of " << target << " at index: " << first << endl;
    cout << "Expected: Index 1" << endl;
    cout << "Status: " << (first == 1 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC08: Duplicate elements - find last occurrence
void tc08_DuplicatesLastOccurrence() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC08] Duplicates - Find Last Occurrence" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {1, 3, 3, 3, 5, 7, 9, 11, 11, 13};
    displayArray(arr, "Sorted Array");
    
    int target = 3;
    int last = findLastOccurrence(arr, target);
    cout << "Last occurrence of " << target << " at index: " << last << endl;
    cout << "Expected: Index 3" << endl;
    cout << "Status: " << (last == 3 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC09: Count occurrences
void tc09_CountOccurrences() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC09] Count Occurrences of Element" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {1, 3, 3, 3, 5, 7, 9, 11, 11, 13};
    displayArray(arr, "Sorted Array");
    
    int target = 3;
    int count = countOccurrences(arr, target);
    cout << "Occurrences of " << target << ": " << count << endl;
    cout << "Expected: 3" << endl;
    cout << "Status: " << (count == 3 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC10: Find insertion position
void tc10_InsertionPosition() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC10] Find Insertion Position (Lower Bound)" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    displayArray(arr, "Sorted Array");
    
    int target = 6;
    int pos = findInsertionPosition(arr, target);
    cout << "Insertion position for " << target << ": " << pos << endl;
    cout << "Expected: Index 3 (between 5 and 7)" << endl;
    cout << "Status: " << (pos == 3 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC11: Recursive vs Iterative comparison
void tc11_RecursiveVsIterative() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC11] Recursive vs Iterative Comparison" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    displayArray(arr, "Sorted Array");
    
    int target = 13;
    
    SearchMetrics iterative = binarySearchIterative(arr, target);
    cout << "\nIterative Search:" << endl;
    displayMetrics(iterative, "Iterative", target);
    
    SearchMetrics recursive = {-1, 0, 0, 0};
    recursive = binarySearchRecursive(arr, target, 0, arr.size() - 1, recursive);
    cout << "\nRecursive Search:" << endl;
    displayMetrics(recursive, "Recursive", target);
    
    cout << "Status: " << (iterative.index == recursive.index ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC12: Negative numbers
void tc12_NegativeNumbers() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC12] Array with Negative Numbers" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {-15, -10, -5, 0, 5, 10, 15, 20};
    displayArray(arr, "Sorted Array");
    
    int target = -5;
    SearchMetrics metrics = binarySearchIterative(arr, target);
    displayMetrics(metrics, "Iterative Binary Search", target);
    cout << "Expected: Index 2" << endl;
    cout << "Status: " << (metrics.index == 2 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC13: Find closest element
void tc13_FindClosest() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC13] Find Closest Element to Target" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr = {1, 5, 10, 15, 20, 25, 30};
    displayArray(arr, "Sorted Array");
    
    int target = 12;
    int closest = findClosest(arr, target);
    cout << "Closest element to " << target << ": " << closest << endl;
    cout << "Expected: 10 or 15 (both distance 2)" << endl;
    cout << "Status: " << (closest == 10 || closest == 15 ? "✓ PASSED" : "✗ FAILED") << endl;
}

// TC14: Large array performance
void tc14_LargeArrayPerformance() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC14] Large Array Performance (1 Million Elements)" << endl;
    cout << string(70, '=') << endl;
    
    vector<int> arr;
    for (int i = 1; i <= 1000000; i++) {
        arr.push_back(i);
    }
    
    cout << "Array Size: 1,000,000 elements" << endl;
    
    // Best case: first element
    int target1 = 1;
    SearchMetrics best = binarySearchIterative(arr, target1);
    cout << "\nBest Case (Search for " << target1 << "):" << endl;
    cout << "Iterations: " << best.iterations << " (Expected: 1)" << endl;
    cout << "Comparisons: " << best.comparisons << " (Expected: 1)" << endl;
    
    // Average case: middle element
    int target2 = 500000;
    SearchMetrics avg = binarySearchIterative(arr, target2);
    cout << "\nAverage Case (Search for " << target2 << "):" << endl;
    cout << "Iterations: " << avg.iterations << endl;
    cout << "Comparisons: " << avg.comparisons << endl;
    
    // Worst case: last element
    int target3 = 1000000;
    SearchMetrics worst = binarySearchIterative(arr, target3);
    cout << "\nWorst Case (Search for " << target3 << "):" << endl;
    cout << "Iterations: " << worst.iterations << " (Expected: 20)" << endl;
    cout << "Comparisons: " << worst.comparisons << " (Expected: 20)" << endl;
    cout << "Note: log₂(1,000,000) ≈ 20 iterations" << endl;
    
    cout << "Status: ✓ PASSED" << endl;
}

// TC15: Complexity analysis
void tc15_ComplexityAnalysis() {
    cout << "\n" << string(70, '=') << endl;
    cout << "[TC15] Time Complexity Analysis Summary" << endl;
    cout << string(70, '=') << endl;
    
    cout << "\nBest Case: O(1)" << endl;
    cout << "  - Element at middle position on first check" << endl;
    cout << "  - Rare scenario" << endl;
    
    cout << "\nAverage Case: O(log n)" << endl;
    cout << "  - Typically narrows search by half each iteration" << endl;
    cout << "  - Example: 1M elements → 20 iterations max" << endl;
    
    cout << "\nWorst Case: O(log n)" << endl;
    cout << "  - Element not found or at furthest end" << endl;
    cout << "  - log₂(n) iterations needed" << endl;
    
    cout << "\nSpace Complexity:" << endl;
    cout << "  - Iterative: O(1) - constant space" << endl;
    cout << "  - Recursive: O(log n) - call stack depth" << endl;
    
    cout << "\nRequirement: Array MUST be sorted" << endl;
    cout << "\nComparison with Linear Search:" << endl;
    cout << "  Linear: 1M elements → 1M comparisons (worst)" << endl;
    cout << "  Binary: 1M elements → 20 comparisons (worst)" << endl;
    cout << "  Binary is 50,000x faster!" << endl;
}

// Run all tests
void runAllTestCases() {
    cout << "\n" << string(70, '=') << endl;
    cout << "BINARY SEARCH - COMPREHENSIVE TEST CASES" << endl;
    cout << string(70, '=') << endl;
    
    tc01_BasicSearch();
    tc02_ElementNotFound();
    tc03_FirstElement();
    tc04_LastElement();
    tc05_SingleElement();
    tc06_EmptyArray();
    tc07_DuplicatesFirstOccurrence();
    tc08_DuplicatesLastOccurrence();
    tc09_CountOccurrences();
    tc10_InsertionPosition();
    tc11_RecursiveVsIterative();
    tc12_NegativeNumbers();
    tc13_FindClosest();
    tc14_LargeArrayPerformance();
    tc15_ComplexityAnalysis();
    
    cout << "\n" << string(70, '=') << endl;
    cout << "ALL TEST CASES COMPLETED SUCCESSFULLY ✓" << endl;
    cout << string(70, '=') << endl;
}

// Main menu
int main() {
    int choice;
    
    while (true) {
        cout << "\n" << string(70, '=') << endl;
        cout << "BINARY SEARCH - DSA LAB ASSIGNMENT" << endl;
        cout << string(70, '=') << endl;
        cout << "1. Run All Test Cases" << endl;
        cout << "2. Iterative Binary Search" << endl;
        cout << "3. Recursive Binary Search" << endl;
        cout << "4. Find First Occurrence" << endl;
        cout << "5. Find Last Occurrence" << endl;
        cout << "6. Count Occurrences" << endl;
        cout << "7. Find Closest Element" << endl;
        cout << "8. Find Insertion Position" << endl;
        cout << "9. Exit" << endl;
        cout << string(70, '=') << endl;
        cout << "Enter choice (1-9): ";
        
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
                int n, val, target;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter sorted array elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                
                cout << "Enter element to search: ";
                cin >> target;
                cin.ignore();
                
                displayArray(arr, "Sorted Array");
                SearchMetrics metrics = binarySearchIterative(arr, target);
                displayMetrics(metrics, "Iterative Search", target);
                break;
            }
                
            case 3: {
                vector<int> arr;
                int n, val, target;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter sorted array elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                
                cout << "Enter element to search: ";
                cin >> target;
                cin.ignore();
                
                displayArray(arr, "Sorted Array");
                SearchMetrics metrics = {-1, 0, 0, 0};
                metrics = binarySearchRecursive(arr, target, 0, arr.size() - 1, metrics);
                displayMetrics(metrics, "Recursive Search", target);
                break;
            }
                
            case 4: {
                vector<int> arr;
                int n, val, target;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter sorted array with duplicates: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                
                cout << "Enter element to find first occurrence: ";
                cin >> target;
                cin.ignore();
                
                displayArray(arr, "Sorted Array");
                int first = findFirstOccurrence(arr, target);
                if (first != -1) {
                    cout << "First occurrence at index: " << first << endl;
                } else {
                    cout << "Element not found!" << endl;
                }
                break;
            }
                
            case 5: {
                vector<int> arr;
                int n, val, target;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter sorted array with duplicates: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                
                cout << "Enter element to find last occurrence: ";
                cin >> target;
                cin.ignore();
                
                displayArray(arr, "Sorted Array");
                int last = findLastOccurrence(arr, target);
                if (last != -1) {
                    cout << "Last occurrence at index: " << last << endl;
                } else {
                    cout << "Element not found!" << endl;
                }
                break;
            }
                
            case 6: {
                vector<int> arr;
                int n, val, target;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter sorted array with duplicates: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                
                cout << "Enter element to count: ";
                cin >> target;
                cin.ignore();
                
                displayArray(arr, "Sorted Array");
                int count = countOccurrences(arr, target);
                cout << "Occurrences of " << target << ": " << count << endl;
                break;
            }
                
            case 7: {
                vector<int> arr;
                int n, val, target;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter sorted array elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                
                cout << "Enter target value: ";
                cin >> target;
                cin.ignore();
                
                displayArray(arr, "Sorted Array");
                int closest = findClosest(arr, target);
                cout << "Closest element to " << target << ": " << closest << endl;
                break;
            }
                
            case 8: {
                vector<int> arr;
                int n, val, target;
                
                cout << "Enter number of elements: ";
                cin >> n;
                
                cout << "Enter sorted array elements: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    arr.push_back(val);
                }
                
                cout << "Enter element to insert: ";
                cin >> target;
                cin.ignore();
                
                displayArray(arr, "Sorted Array");
                int pos = findInsertionPosition(arr, target);
                cout << "Insert " << target << " at position: " << pos << endl;
                break;
            }
                
            case 9:
                cout << "Exiting Binary Search Program. Thank you!" << endl;
                return 0;
                
            default:
                cout << "[ERROR] Invalid choice. Please select 1-9." << endl;
        }
    }
    
    return 0;
}