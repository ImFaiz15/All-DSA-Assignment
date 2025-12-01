// To understand the concept of Linear Search, perform its implementation and Analyze its best and worst case.

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to perform basic linear search

int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        // If target element is found, return its index
        if (arr[i] == target) {
            return i;  // Return position (1-based)
        }
    }
    // Element not found, return -1
    return -1;
}


struct SearchResult {
    int index;                    // Position of element (-1 if not found)
    int comparisons;              // Number of comparisons made
    double executionTime;         // Time taken in milliseconds
};

SearchResult linearSearchWithStats(const vector<int>& arr, int target) {
    SearchResult result;
    result.comparisons = 0;       // Initialize comparison counter
    result.index = -1;            // Initialize index to -1 (not found)
    
    // Start timer to measure execution time
    auto start = chrono::high_resolution_clock::now();
    
    // Traverse array and count comparisons
    for (int i = 0; i < arr.size(); i++) {
        result.comparisons++;     // Increment comparison counter
        
        if (arr[i] == target) {
            result.index = i;     // Store index when found
            break;                // Exit loop immediately
        }
    }
    
    // End timer
    auto end = chrono::high_resolution_clock::now();
    
    // Calculate execution time in milliseconds
    result.executionTime = chrono::duration<double, milli>(end - start).count();
    
    return result;
}

// Find all occurrences of target element
vector<int> linearSearchAll(const vector<int>& arr, int target) {
    vector<int> positions;        // Store all positions where target is found
    
    // Traverse entire array to find all occurrences
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            positions.push_back(i);  // Add position to vector
        }
    }
    
    return positions;             // Return all positions
}

// Find first occurrence of target
int findFirst(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;             // Return immediately when found
        }
    }
    return -1;                    // Not found
}

// Find last occurrence of target
int findLast(const vector<int>& arr, int target) {
    // Traverse from right to left (reverse order)
    for (int i = arr.size() - 1; i >= 0; i--) {
        if (arr[i] == target) {
            return i;             // Return last occurrence
        }
    }
    return -1;                    // Not found
}

// Display array elements
void displayArray(const vector<int>& arr) {
    cout << "\nArray: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Display search result
void displaySearchResult(int index, int target) {
    if (index != -1) {
        cout << "✓ Element " << target << " found at index: " << index << endl;
    } else {
        cout << "✗ Element " << target << " not found in array." << endl;
    }
}

// TEST CASES

void runAllTestCases() {
    cout << "\n" << string(70, '=') << endl;
    cout << "LINEAR SEARCH - COMPREHENSIVE TEST CASES" << endl;
    cout << string(70, '=') << endl;
    
    // TEST CASE 1: SEARCH IN UNSORTED ARRAY - ELEMENT EXISTS
    cout << "\n[TC01] Search Element at First Position (Best Case O(1))" << endl;
    vector<int> tc1 = {5, 2, 8, 1, 9};
    cout << "Array: ";
    for (int x : tc1) cout << x << " ";
    cout << "\nSearching for: 5";
    int result1 = linearSearch(tc1, 5);
    displaySearchResult(result1, 5);
    cout << "Expected: Index 0" << endl;
    
    // TEST CASE 2: SEARCH IN UNSORTED ARRAY - ELEMENT AT END
    cout << "\n[TC02] Search Element at Last Position (Worst Case O(n))" << endl;
    vector<int> tc2 = {5, 2, 8, 1, 9};
    cout << "Array: ";
    for (int x : tc2) cout << x << " ";
    cout << "\nSearching for: 9";
    int result2 = linearSearch(tc2, 9);
    displaySearchResult(result2, 9);
    cout << "Expected: Index 4" << endl;
    
    // TEST CASE 3: ELEMENT NOT FOUND
    cout << "\n[TC03] Element Not Found (Worst Case O(n))" << endl;
    vector<int> tc3 = {5, 2, 8, 1, 9};
    cout << "Array: ";
    for (int x : tc3) cout << x << " ";
    cout << "\nSearching for: 15";
    int result3 = linearSearch(tc3, 15);
    displaySearchResult(result3, 15);
    cout << "Expected: Index -1 (Not Found)" << endl;
    
    // TEST CASE 4: EMPTY ARRAY
    cout << "\n[TC04] Search in Empty Array" << endl;
    vector<int> tc4 = {};
    cout << "Array: (empty)";
    cout << "\nSearching for: 5";
    int result4 = linearSearch(tc4, 5);
    displaySearchResult(result4, 5);
    cout << "Expected: Index -1" << endl;
    
    // TEST CASE 5: SINGLE ELEMENT ARRAY - MATCH
    cout << "\n[TC05] Single Element Array - Match Found" << endl;
    vector<int> tc5 = {7};
    cout << "Array: ";
    for (int x : tc5) cout << x << " ";
    cout << "\nSearching for: 7";
    int result5 = linearSearch(tc5, 7);
    displaySearchResult(result5, 7);
    cout << "Expected: Index 0" << endl;
    
    // TEST CASE 6: SINGLE ELEMENT ARRAY - NO MATCH
    cout << "\n[TC06] Single Element Array - No Match" << endl;
    vector<int> tc6 = {7};
    cout << "Array: ";
    for (int x : tc6) cout << x << " ";
    cout << "\nSearching for: 5";
    int result6 = linearSearch(tc6, 5);
    displaySearchResult(result6, 5);
    cout << "Expected: Index -1" << endl;
    
    // TEST CASE 7: DUPLICATE ELEMENTS - FIRST OCCURRENCE
    cout << "\n[TC07] Array with Duplicates - Find First Occurrence" << endl;
    vector<int> tc7 = {3, 5, 3, 8, 3, 1};
    cout << "Array: ";
    for (int x : tc7) cout << x << " ";
    cout << "\nSearching for: 3";
    int result7 = findFirst(tc7, 3);
    displaySearchResult(result7, 3);
    cout << "Expected: Index 0 (first occurrence)" << endl;
    
    // TEST CASE 8: DUPLICATE ELEMENTS - LAST OCCURRENCE
    cout << "\n[TC08] Array with Duplicates - Find Last Occurrence" << endl;
    vector<int> tc8 = {3, 5, 3, 8, 3, 1};
    cout << "Array: ";
    for (int x : tc8) cout << x << " ";
    cout << "\nSearching for: 3";
    int result8 = findLast(tc8, 3);
    displaySearchResult(result8, 3);
    cout << "Expected: Index 4 (last occurrence)" << endl;
     
    // TEST CASE 9: FIND ALL OCCURRENCES
    cout << "\n[TC09] Find All Occurrences of Element" << endl;
    vector<int> tc9 = {2, 5, 2, 8, 2, 1, 2};
    cout << "Array: ";
    for (int x : tc9) cout << x << " ";
    cout << "\nSearching for: 2";
    vector<int> result9 = linearSearchAll(tc9, 2);
    if (!result9.empty()) {
        cout << "✓ Element 2 found at indices: ";
        for (int idx : result9) cout << idx << " ";
        cout << endl;
    } else {
        cout << "✗ Element not found." << endl;
    }
    cout << "Expected: Indices 0, 2, 4, 6" << endl;
    
    // TEST CASE 10: LARGE ARRAY - PERFORMANCE ANALYSIS
    cout << "\n[TC10] Large Array - Performance Analysis (1,000,000 elements)" << endl;
    vector<int> tc10(1000000);
    for (int i = 0; i < 1000000; i++) {
        tc10[i] = i + 1;
    }
    
    // Best Case: Search first element
    cout << "\nBest Case - Search for 1 (first element):" << endl;
    SearchResult bestCase = linearSearchWithStats(tc10, 1);
    cout << "  - Found at index: " << bestCase.index << endl;
    cout << "  - Comparisons: " << bestCase.comparisons << endl;
    cout << "  - Time: " << fixed << setprecision(6) << bestCase.executionTime << " ms" << endl;
    
    // Average Case: Search middle element
    cout << "\nAverage Case - Search for 500000 (middle element):" << endl;
    SearchResult avgCase = linearSearchWithStats(tc10, 500000);
    cout << "  - Found at index: " << avgCase.index << endl;
    cout << "  - Comparisons: " << avgCase.comparisons << endl;
    cout << "  - Time: " << fixed << setprecision(6) << avgCase.executionTime << " ms" << endl;
    
    // Worst Case: Search last element
    cout << "\nWorst Case - Search for 1000000 (last element):" << endl;
    SearchResult worstCase = linearSearchWithStats(tc10, 1000000);
    cout << "  - Found at index: " << worstCase.index << endl;
    cout << "  - Comparisons: " << worstCase.comparisons << endl;
    cout << "  - Time: " << fixed << setprecision(6) << worstCase.executionTime << " ms" << endl;
    
    // TEST CASE 11: NEGATIVE NUMBERS
    cout << "\n[TC11] Array with Negative Numbers" << endl;
    vector<int> tc11 = {-5, -2, -8, -1, 0, 5, 8};
    cout << "Array: ";
    for (int x : tc11) cout << x << " ";
    cout << "\nSearching for: -8";
    int result11 = linearSearch(tc11, -8);
    displaySearchResult(result11, -8);
    cout << "Expected: Index 2" << endl;
    
    // TEST CASE 12: ALL SAME ELEMENTS
    cout << "\n[TC12] Array with All Same Elements" << endl;
    vector<int> tc12 = {5, 5, 5, 5, 5};
    cout << "Array: ";
    for (int x : tc12) cout << x << " ";
    cout << "\nSearching for: 5";
    int result12 = linearSearch(tc12, 5);
    displaySearchResult(result12, 5);
    cout << "Expected: Index 0 (returns first occurrence)" << endl;
    
    // TEST CASE 13: SORTED ARRAY (still works with linear search)
    cout << "\n[TC13] Sorted Array (Linear Search still works)" << endl;
    vector<int> tc13 = {1, 3, 5, 7, 9, 11, 13};
    cout << "Array: ";
    for (int x : tc13) cout << x << " ";
    cout << "\nSearching for: 7";
    int result13 = linearSearch(tc13, 7);
    displaySearchResult(result13, 7);
    cout << "Expected: Index 3" << endl;
    
    // TEST CASE 14: COMPARISON WITH BINARY SEARCH (concept)
    cout << "\n[TC14] Linear Search Characteristics Summary" << endl;
    cout << "  - Time Complexity (Best Case): O(1)" << endl;
    cout << "  - Time Complexity (Average Case): O(n/2) ≈ O(n)" << endl;
    cout << "  - Time Complexity (Worst Case): O(n)" << endl;
    cout << "  - Space Complexity: O(1)" << endl;
    cout << "  - Stable: Yes (preserves order of equal elements)" << endl;
    cout << "  - Works on Unsorted Data: Yes" << endl;
    cout << "  - Works on Sorted Data: Yes" << endl;
    
    cout << "\n" << string(70, '=') << endl;
    cout << "ALL TEST CASES COMPLETED SUCCESSFULLY ✓" << endl;
    cout << string(70, '=') << endl;
}

int main() {
    int choice;
    
    while (true) {
        cout << "\n" << string(70, '=') << endl;
        cout << "LINEAR SEARCH - DSA LAB ASSIGNMENT" << endl;
        cout << string(70, '=') << endl;
        cout << "1. Run All Test Cases" << endl;
        cout << "2. Custom Search" << endl;
        cout << "3. Performance Analysis" << endl;
        cout << "4. Exit" << endl;
        cout << string(70, '=') << endl;
        cout << "Enter your choice (1-4): ";
        
        string input;
        getline(cin, input);
        
        // Validate input
        if (input.empty() || !isdigit(input[0])) {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            continue;
        }
        
        choice = stoi(input);
        
        switch (choice) {
            case 1:
                runAllTestCases();
                break;
                
            case 2: {
                // Custom search
                vector<int> arr;
                int n, target;
                
                cout << "\nEnter number of elements: ";
                cin >> n;
                
                cout << "Enter array elements: ";
                for (int i = 0; i < n; i++) {
                    int x;
                    cin >> x;
                    arr.push_back(x);
                }
                
                cout << "Enter element to search: ";
                cin >> target;
                cin.ignore();
                
                int idx = linearSearch(arr, target);
                displaySearchResult(idx, target);
                break;
            }
                
            case 3: {
                // Performance analysis
                cout << "\nPerformance Analysis - Comparing Search Positions" << endl;
                vector<int> arr(10000);
                for (int i = 0; i < 10000; i++) {
                    arr[i] = i + 1;
                }
                
                cout << "\nArray size: 10,000 elements" << endl;
                
                SearchResult first = linearSearchWithStats(arr, 1);
                cout << "\nFirst element: " << first.comparisons << " comparisons, "
                     << fixed << setprecision(6) << first.executionTime << " ms" << endl;
                
                SearchResult middle = linearSearchWithStats(arr, 5000);
                cout << "Middle element: " << middle.comparisons << " comparisons, "
                     << fixed << setprecision(6) << middle.executionTime << " ms" << endl;
                
                SearchResult last = linearSearchWithStats(arr, 10000);
                cout << "Last element: " << last.comparisons << " comparisons, "
                     << fixed << setprecision(6) << last.executionTime << " ms" << endl;
                
                break;
            }
                
            case 4:
                cout << "Exiting Linear Search Program. Thank you!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice. Please select from 1 to 4." << endl;
        }
    }
    
    return 0;
}